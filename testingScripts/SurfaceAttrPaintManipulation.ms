resetMaxFile #noPrompt
thisfile = getThisScriptFilename()
bunnypath =  (getFilenamePath thisfile) + "testfiles/bunny.obj"
ImportFile bunnypath #noPrompt
bunny = $
scale bunny [100, 100, 100]
max tool zoomextents all
clearNodeSelection()
resetxform bunny

m = FabricMesh()

-- Create the graph
$.DFGInstPreset "Fabric.Exts.Manipulation.ManipHandle.EmptyManipHandle" [433.000000,161.000000]   execPath:""
$.DFGSetExtDeps #("Get")    execPath:""
$.DFGInstPreset "Fabric.Exts.Manipulation.ManipHandle.GetDrawingHandle" [379.000000,78.000000]   execPath:""
$.DFGMoveNodes #("EmptyManipHandle") #([112.000000,85.000000])   execPath:""
$.DFGInstPreset "Fabric.Exts.Manipulation.ManipHandle.AddSurfacePaintManip" [421.000000,183.000000]   execPath:""
$.DFGMoveNodes #("AddSurfacePaintManip") #([700.000000,96.000000])   execPath:""
$.DFGMoveNodes #("GetDrawingHandle") #([319.000000,207.000000])   execPath:""
$.DFGConnect "EmptyManipHandle.value" "GetDrawingHandle.this"   execPath:""
$.DFGConnect "EmptyManipHandle.value" "AddSurfacePaintManip.this"   execPath:""
$.DFGInstPreset "Fabric.Exts.Manipulation.Weightmap.EmptyWeightmap" [388.000000,183.000000]   execPath:""
$.DFGMoveNodes #("EmptyWeightmap") #([475.000000,143.000000])   execPath:""
$.DFGConnect "EmptyWeightmap.value" "AddSurfacePaintManip.weightmap"   execPath:""
$.DFGInstPreset "Fabric.Exts.InlineDrawing.DrawingHandle.DrawPolygonMesh" [471.000000,183.000000]   execPath:""
$.DFGMoveNodes #("DrawPolygonMesh") #([509.000000,251.000000])   execPath:""
$.DFGAddPort "mesh" 0 "PolygonMesh" portToConnect:"DrawPolygonMesh.mesh" extDep:"" metaData:"" execPath:""
$.DFGAddPort "transform" 0 "Xfo" portToConnect:"DrawPolygonMesh.transform" extDep:"" metaData:"" execPath:""
$.DFGConnect "GetDrawingHandle.result" "DrawPolygonMesh.this"   execPath:""
$.DFGConnect "DrawPolygonMesh.instance" "AddSurfacePaintManip.instance"   execPath:""
$.DFGAddPort "this" 2 "ManipHandle" portToConnect:"AddSurfacePaintManip.this" extDep:"" metaData:"" execPath:""

-- Add a link to a scene node - pass in both the mesh and the trnasform
m.AddInputPort "mesh0" "PolygonMesh" 17
m.AddInputPort "mesh0Transform" "Mat44" 17

-- Connect the ports up to the teapot
m.mesh0 = bunny
m.mesh0Transform = bunny
entryPt = "paintOp"
klCode = "
require Math;
require PolygonMesh;
require Manipulation;

operator paintOp(io PolygonMesh mesh0, in Mat44 mesh0Transform) {
  InlineDrawing drawing = OGLInlineDrawing_GetInstance();
  mesh0.recomputePointNormals();
  // Add the weightmap to the mesh. 
  Ref<GeometryAttribute> weightMap = mesh0.getOrCreateAttribute('weightMap', ScalarAttribute);
  Ref<EventDispatcher> eventDispatcher = EventDispatcher_GetInstance();
  if(eventDispatcher.activeManipulator() != 'SurfaceAttributePaintManipulator')
  {
      SurfaceAttributePaintManipulator paintManipulator();
	    paintManipulator.attributeName = 'weightMap';
      eventDispatcher.registerManipulator(paintManipulator);

      // activate the manipulator
      eventDispatcher.pushManipulator('SurfaceAttributePaintManipulator');
     
      InlineShader overlayShader = drawing.registerShader(OGLSurfaceOverlayShader());
      InlineMaterial overlayMaterial = overlayShader.getOrCreateMaterial(\"weightMap\");
      
      // create a shape for the mesh0
      InlineMeshShape shape = InlineMeshShape('mesh0', mesh0);
      drawing.registerShape(shape);

      InlineTransform transform = StaticInlineTransform('mesh0Transform', Xfo(mesh0Transform));
      drawing.getRoot().addChild(transform);

      InlineInstance instance = SimpleInlineInstance('bunny', transform, shape);
      instance.setInstanceUniform(InlineUniform('u_diffuseColor', Color(1.0, 0.0, 0.0)));

      instance.addMaterial(overlayMaterial); 

      if(paintManipulator)
        paintManipulator.addTargetGeometry(instance);
    
  }
}

"

m.SetKLCode entryPt klCode

Fabric.Rendering = true
Fabric.Manipulation = true 
