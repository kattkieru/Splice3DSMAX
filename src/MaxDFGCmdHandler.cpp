#include "StdAfx.h"
#include "MaxDFGCmdHandler.h"

#include <macrorec.h>
#include <QString>
#include <iostream>
#include <FabricUI/Commands/KLCommandManager.h>

//////////////////////////////////////////////////////////////////////////
// defines

const MSTR s_PortTypeEnumOUT = _M("DFGPortOUT");
const MSTR s_PortTypeEnumIO = _M("DFGPortIO");
const MSTR s_PortTypeEnumIN = _M("DFGPortIN");

//////////////////////////////////////////////////////////////////////////

MaxDFGCmdHandler::MaxDFGCmdHandler(FabricTranslationFPInterface* pTranslation)
	: DFGUICmdHandler_QUndo(GetQtUndoStack())
	, m_pTranslationLayer(pTranslation)
{

}

MaxDFGCmdHandler::~MaxDFGCmdHandler()
{

}

#pragma region <T> -> MSTR converters

MSTR ToMSTR(const QString& v) {
	MSTR r;
	r.printf(_M("\"%s\""), v.data());
	return r;
}

MSTR ToMSTR(const Point2& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.x, v.y);
	return r;
}

MSTR ToMSTR(const QPointF& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.x(), v.y());
	return r;
}
MSTR ToMSTR(const QSizeF& v) {
	MSTR r;
	r.printf(_M("[%f,%f]"), v.width(), v.height());
	return r;
}

MSTR ToMSTR(const FabricCore::RTVal& v) {
	FabricCore::RTVal cjson = v.getJSON();
	return  MSTR::FromACP(cjson.getStringCString());
}

MSTR ToMSTR(unsigned int v) {
	MSTR s;
	s.printf(_M("%i"), v);
	return s;
}

MSTR ToMSTR( FabricCore::DFGPortType portType )
{
	MSTR portTypeEnum = _M( "#" );
	switch (portType)
	{
		case FabricCore::DFGPortType_Out:
			portTypeEnum.Append( s_PortTypeEnumOUT );
			break;
		case FabricCore::DFGPortType_In:
			portTypeEnum.Append( s_PortTypeEnumIN );
			break;
		case FabricCore::DFGPortType_IO:
			portTypeEnum.Append( s_PortTypeEnumIO );
			break;
	}
	return portTypeEnum;
}

MSTR ToMSTR(const QStringList& v) {
	MSTR r;
	MSTR contents;
	for (int i = 0; i < v.size(); i++) {
		MSTR comma = _M("");
		if (i > 0)
			comma = _M(", ");
		MSTR item = comma + ToMSTR(v[i]);
		contents += item;
	}
	r.printf(_M("#(%s)"), contents.data());
	return r;
}

template<typename T>
MSTR ToMSTR(const QList<T>& v) {
	MSTR r;
	MSTR contents;
	for (int i = 0; i < v.size(); i++) {
		MSTR comma = _M("");
		if (i > 0)
			comma = _M(", ");
		MSTR item = comma + ToMSTR(v[i]);
		contents += item;
	}
	r.printf(_M("#(%s)"), contents.data());
	return r;
}

template<typename T>
MSTR ToMSTR(const std::vector<T>& v) {
	MSTR r;
	MSTR contents;
	for (int i = 0; i < v.size(); i++) {
		MSTR comma = _M("");
		if (i > 0)
			comma = _M(", ");
		MSTR item = comma + ToMSTR(v[i]);
		contents += item;
	}
	r.printf(_M("#(%s)"), contents.data());
	return r;
}

// This template overload returns empty string for non-existant parameters
class nothing {};
MSTR ToMSTR(const nothing& v) {
	return MSTR();
}

// Quickly convert FTL::CStrRef to MCHAR*
#define TO_MCHAR(x) ToMSTR(x).data()

template<typename T1, typename T2, typename T3, typename T4>
void doEmit(const MCHAR* fn, const T1& t1, const T2& t2, const T3& t3, const T4& t4, QString & execPath)
{
	// No need to do anything if the user won't see it
	if (!macroRecorder->Enabled())
		return;

	MSTR cmd;
	cmd.printf(_M("$.%s %s %s %s %s execPath:%s"), fn, TO_MCHAR(t1), TO_MCHAR(t2), TO_MCHAR(t3), TO_MCHAR(t4), TO_MCHAR(execPath));
	macroRecorder->ScriptString(cmd.data());
	macroRecorder->EmitScript();
}

#define EMIT1(fn, t1, path) doEmit(fn, t1, nothing(), nothing(), nothing(), execPath)
#define EMIT2(fn, t1, t2, path) doEmit(fn, t1, t2, nothing(), nothing(), execPath)
#define EMIT3(fn, t1, t2, t3, path) doEmit(fn, t1, t2, t3, nothing(), execPath)
#define EMIT4(fn, t1, t2, t3, t4, path) doEmit(fn, t1, t2, t3, t4, execPath)

#pragma endregion

void MaxDFGCmdHandler::dfgDoRemoveNodes(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList nodeNames)
{
	EMIT1(_M("DFGRemoveNodes"), nodeNames, execPath);
	DFGHoldActions hold(_M("DFG Remove Nodes"));
	__super::dfgDoRemoveNodes(binding, execPath, exec, nodeNames);
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoConnect(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList srcPortPaths, QStringList dstPortPaths)
{
	EMIT2(_M("DFGConnect"), srcPortPaths, dstPortPaths, execPath);
	DFGHoldActions hold(_M("DFG Connect"));
	__super::dfgDoConnect(binding, execPath, exec, srcPortPaths, dstPortPaths);
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoDisconnect( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList srcPaths, QStringList dstPaths)
{
	EMIT2( _M( "DFGDisconnect" ), srcPaths, dstPaths, execPath );
	DFGHoldActions hold( _M( "DFG Disconnect" ) );
	__super::dfgDoDisconnect( binding, execPath, exec, srcPaths, dstPaths );
	m_pTranslationLayer->InvalidateAll();
}

QString MaxDFGCmdHandler::dfgDoAddGraph(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString title, QPointF pos)
{
	EMIT2(_M("DFGAddGraph"), title, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Graph"));
	return __super::dfgDoAddGraph(binding, execPath, exec, title, pos);
}

QString MaxDFGCmdHandler::dfgDoAddFunc(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString title, QString initialCode, QPointF pos)
{
	EMIT3(_M("DFGAddFunc"), title, initialCode, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Function"));
	return __super::dfgDoAddFunc(binding, execPath, exec, title, initialCode, pos);
}

QString MaxDFGCmdHandler::dfgDoInstPreset(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString presetPath, QPointF pos)
{
	EMIT2(_M("DFGInstPreset"), presetPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Load Preset"));
	return __super::dfgDoInstPreset(binding, execPath, exec, presetPath, pos);
}

QString MaxDFGCmdHandler::dfgDoAddVar(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredNodeName, QString dataType, QString extDep, QPointF pos)
{
	EMIT4(_M("DFGAddVar"), desiredNodeName, dataType, extDep, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Var"));
	return __super::dfgDoAddVar(binding, execPath, exec, desiredNodeName, dataType, extDep, pos);
}

QString MaxDFGCmdHandler::dfgDoAddGet(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredNodeName, QString varPath, QPointF pos)
{
	EMIT3(_M("DFGAddGet"), desiredNodeName, varPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Get"));
	return __super::dfgDoAddGet(binding, execPath, exec, desiredNodeName, varPath, pos);
}

QString MaxDFGCmdHandler::dfgDoAddSet(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredNodeName, QString varPath, QPointF pos)
{
	EMIT3(_M("DFGAddSet"), desiredNodeName, varPath, pos, execPath);
	DFGHoldActions hold(_M("DFG Add Set"));
	return __super::dfgDoAddSet(binding, execPath, exec, desiredNodeName, varPath, pos);
}

QString MaxDFGCmdHandler::dfgDoAddPort(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredPortName, FabricCore::DFGPortType portType, QString typeSpec, QString portToConnect, QString extDep, QString metaData)
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		MSTR portTypeEnum = ToMSTR( portType );
		cmd.printf( _M( "$.%s %s %s %s portToConnect:%s extDep:%s metaData:%s execPath:%s" ),
					_M( "DFGAddPort" ),
					desiredPortName.data(),
					portTypeEnum.data(),
					typeSpec.data(),
					portToConnect.data(),
					extDep.data(),
					metaData.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}

	DFGHoldActions hold(_M("DFG Add Port"));

	bool isPossibleMaxPort = portType != FabricCore::DFGPortType_Out && execPath.isEmpty();

	QString res = __super::dfgDoAddPort(binding, execPath, exec, desiredPortName, portType, typeSpec, portToConnect, extDep, metaData);
	// I think that the issue with the boolean input is located here. I'm not sure what it is exactly...
	if (isPossibleMaxPort)
	{
		// It appears that the result will be NULL if called from MxS, and non-NULL
		// if called from the UI.  It's very difficult to tell what the reason for this
		// difference is, so here we just detect if the call returned the new ports name
		// If we have add a new 'in' port, by default we create a matching 3ds max port.
		m_pTranslationLayer->SyncMetaDataFromPortToParam(res.isEmpty() ? desiredPortName.toStdString().c_str() : res.toStdString().c_str());
	}
	return res;
}

QString MaxDFGCmdHandler::dfgDoEditPort(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString oldPortName, QString desiredNewPortName, FabricCore::DFGPortType portMode, QString typeSpec, QString extDep, QString uiMetadata)
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		MSTR portModeStr = ToMSTR( portMode );
		cmd.printf( _M( "$.%s %s desiredNewPortName:%s portType:%s typeSpec:%s extDep:%s metadata:%s execPath:%s" ),
					_M( "DFGEditPort" ),
					oldPortName.data(),
					desiredNewPortName.data(),
					portModeStr.data(),
					typeSpec.data(),
					extDep.data(),
					uiMetadata.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}

	DFGHoldActions hold(_M("DFG Edit Port"));
	QString res = __super::dfgDoEditPort(binding, execPath, exec, oldPortName, desiredNewPortName, portMode, typeSpec, extDep, uiMetadata);

	
	bool isPossibleMaxPort = portMode != FabricCore::DFGPortType_Out && execPath.isEmpty();
	if (isPossibleMaxPort)
	{
		// If we have add a new 'in' port, by default we create a matching 3ds max port.
		m_pTranslationLayer->SyncMetaDataFromPortToParam(res.toStdString().c_str());
	}
	return res;
}

void MaxDFGCmdHandler::dfgDoRemovePort(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList portNames)
{
	EMIT1(_M("DFGRemovePort"), portNames, execPath);
	DFGHoldActions hold(_M("DFG Remove Port"));
	if (!theHold.RestoreOrRedoing())
	{
		for (QStringList::iterator it = portNames.begin(); it != portNames.end(); ++it) 
		{
			QString portName = *it;
			int pid = GetPortParamID(exec, portName.toStdString().c_str());
			if (pid >= 0)
			{
				m_pTranslationLayer->SetMaxTypeForArg(ToMstr(portName), -1);
			}			
		}		
	}
	__super::dfgDoRemovePort(binding, execPath, exec, portNames);
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoResizeBackDrop(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString backDropNodeName, QPointF newTopLeftPos, QSizeF newSize)
{
	EMIT3(_M("DFGResizeBackDrop"), backDropNodeName, newTopLeftPos, newSize, execPath);
	DFGHoldActions hold(_M("DFG Resize Back Drop"));
	return __super::dfgDoResizeBackDrop(binding, execPath, exec, backDropNodeName, newTopLeftPos, newSize);
}

void MaxDFGCmdHandler::dfgDoMoveNodes(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList nodeNames, QList<QPointF> newTopLeftPoss)
{
	EMIT2(_M("DFGMoveNodes"), nodeNames, newTopLeftPoss, execPath);
	DFGHoldActions hold(_M("DFG Move Nodes"));
	return __super::dfgDoMoveNodes(binding, execPath, exec, nodeNames, newTopLeftPoss);
}

QString MaxDFGCmdHandler::dfgDoImplodeNodes(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList nodeNames, QString desiredNodeName)
{
	EMIT2(_M("DFGImplodeNodes"), nodeNames, desiredNodeName, execPath);
	DFGHoldActions hold(_M("DFG Implode Nodes"));
	return __super::dfgDoImplodeNodes(binding, execPath, exec, nodeNames, desiredNodeName);
}

QStringList MaxDFGCmdHandler::dfgDoExplodeNode(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString nodeName)
{
	EMIT1(_M("DFGExplodeNode"), nodeName, execPath);
	DFGHoldActions hold(_M("DFG Explode Nodes"));
	return __super::dfgDoExplodeNode(binding, execPath, exec, nodeName);
}

QString MaxDFGCmdHandler::dfgDoAddBackDrop(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString title, QPointF pos)
{
	EMIT2(_M("DFGAddBackDrop"), title, pos, execPath);
	DFGHoldActions hold(_M("DFG Add BackDrop"));
	return __super::dfgDoAddBackDrop(binding, execPath, exec, title, pos);
}

void MaxDFGCmdHandler::dfgDoSetNodeComment( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString nodeName, QString comment)
{
	EMIT2(_M("DFGSetNodeComment"), nodeName, comment, execPath);
	DFGHoldActions hold(_M("DFG Set Node Comment"));
	__super::dfgDoSetNodeComment(binding, execPath, exec, nodeName, comment);
}

void MaxDFGCmdHandler::dfgDoSetCode(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString code)
{
	EMIT1(_M("DFGSetCode"), code, execPath);
	DFGHoldActions hold(_M("DFG Set Code"));
	__super::dfgDoSetCode(binding, execPath, exec, code);
	m_pTranslationLayer->InvalidateAll();
}

QString MaxDFGCmdHandler::dfgDoRenamePort(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString portPath, QString desiredNewPortName)
{
	EMIT2(_M("DFGRenamePort"), portPath, desiredNewPortName, execPath);
	DFGHoldActions hold(_M("DFG Rename Port"));
	QString res = __super::dfgDoRenamePort(binding, execPath, exec, portPath, desiredNewPortName);
	m_pTranslationLayer->SyncMetaDataFromPortToParam(res.toStdString().c_str());
	return res;
}

QStringList MaxDFGCmdHandler::dfgDoPaste(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString json, QPointF cursorPos)
{
	EMIT2(_M("DFGPaste"), json, cursorPos, execPath);
	DFGHoldActions hold(_M("DFG Paste"));
	return __super::dfgDoPaste(binding, execPath, exec, json, cursorPos);
}

void MaxDFGCmdHandler::dfgDoSetArgValue(FabricCore::DFGBinding const &binding, QString argName, FabricCore::RTVal const &value)
{
	macroRecorder->FunctionCall(_M("$.DFGSetArgValue"), 2, 0,
		mr_string, argName.data(),
		mr_string, TO_MCHAR(value)
		);

	DFGHoldActions hold(_M("DFG Set Arg Value"));

	__super::dfgDoSetArgValue(binding, argName, value);

	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoSetPortDefaultValue(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString portOrPinPath, FabricCore::RTVal const &value)
{
	EMIT2(_M("DFGSetPortDefaultValue"), portOrPinPath, value, execPath);
	DFGHoldActions hold(_M("DFG Set Def Value"));
	__super::dfgDoSetPortDefaultValue(binding, execPath, exec, portOrPinPath, value);

	// If we have a period '.' in our port name, or our execPath is non-empty, then
	// the port is not a max parameter, and there is no need to sync
	if (!(portOrPinPath.contains('.') || execPath.size() > 1))
		m_pTranslationLayer->SyncMetaDataFromPortToParam(portOrPinPath.toStdString().c_str());

	// Whatever happens though, we need to re-evaluate
	m_pTranslationLayer->InvalidateAll();
}

void MaxDFGCmdHandler::dfgDoSetRefVarPath(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString refName, QString varPath)
{
	EMIT2(_M("DFGSetRefVarPath"), refName, varPath, execPath);
	DFGHoldActions hold(_M("DFG Set Ref Path"));
	return __super::dfgDoSetRefVarPath(binding, execPath, exec, refName, varPath);
}

void MaxDFGCmdHandler::dfgDoReorderPorts(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString itemPath, QList<int> indices)
{
	EMIT2(_M("DFGReorderPorts"), itemPath, indices, execPath);
	DFGHoldActions hold(_M("DFG Re-order Ports"));
	return __super::dfgDoReorderPorts(binding, execPath, exec, itemPath, indices);
}

void MaxDFGCmdHandler::dfgDoSetExtDeps(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QStringList extDeps)
{
	EMIT1(_M("DFGSetExtDeps"), extDeps, execPath);
	DFGHoldActions hold(_M("DFG Set External Dependencies"));
	return __super::dfgDoSetExtDeps(binding, execPath, exec, extDeps);
}

void MaxDFGCmdHandler::dfgDoSplitFromPreset(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec)
{
	doEmit(_M("DFGSplitFromPreset"), nothing(), nothing(), nothing(), nothing(), execPath);
	DFGHoldActions hold(_M("DFG Split From Preset"));
	return __super::dfgDoSplitFromPreset(binding, execPath, exec);
}

QString MaxDFGCmdHandler::dfgDoCreatePreset( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString nodeName, QString presetDirPath, QString presetName, bool updateOrigPreset )
{
	EMIT3( _M( "DFGDoCreatePreset" ), nodeName, presetDirPath, presetName, execPath );
	DFGHoldActions hold( _M( "DFG Do Create Preset" ) );
	return __super::dfgDoCreatePreset( binding, execPath, exec, nodeName, presetDirPath, presetName, updateOrigPreset );
}

QString MaxDFGCmdHandler::dfgDoEditNode( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString oldNodeName, QString desiredNewNodeName, QString nodeMetadata, QString execMetadata )
{
	//EMIT4( _M( "DFGDoEditNode" ), oldNodeName, desiredNewNodeName, nodeMetadata, execMetadata, execPath );

	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		cmd.printf( _M( "$.DFGDoEditNode \"%s\" desiredNewNodeName:\"%s\" nodeMetadata:\"%s\" execMetadata:\"%s\" execPath:\"%s\"" ),
					oldNodeName.data(),
					desiredNewNodeName.data(),
					nodeMetadata.data(),
					execMetadata.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}


	DFGHoldActions hold( _M( "DFG Do Edit Node" ) );
	return __super::dfgDoEditNode( binding, execPath, exec, oldNodeName, desiredNewNodeName, nodeMetadata, execMetadata );
}

void MaxDFGCmdHandler::dfgDoDismissLoadDiags( FabricCore::DFGBinding const &binding, QList<int> diagIndices )
{
	
	if (macroRecorder->Enabled())
	{
		MSTR listAsString = ToMSTR( diagIndices );
		MSTR cmd;
		cmd.printf( _M( "$.DFGDoDismissLoadDiags %s" ), listAsString.data());
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}
	DFGHoldActions hold( _M( "DFG Dismiss Load Dialogs" ) );
	return __super::dfgDoDismissLoadDiags( binding, diagIndices );
}


QString MaxDFGCmdHandler::dfgDoAddInstPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString instName, QString desiredPortName, FabricCore::DFGPortType portType, QString typeSpec, QString pathToConnect, FabricCore::DFGPortType connectType, QString extDep, QString metaData )
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		MSTR portTypeStr = ToMSTR( portType );
		MSTR connectTypeStr = ToMSTR( connectType );

		cmd.printf( _M( "$.DFGDoAddInstPort \"%s\" \"%s\" %s typeSpec:\"%s\" pathToConnect:\"%s\" connectType:%s extDep:\"%s\" metaData:\"%s\" execPath:\"%s\"" ),
					instName.data(),
					desiredPortName.data(),
					portTypeStr.data(),
					typeSpec.data(),
					pathToConnect.data(),
					connectTypeStr.data(),
					extDep.data(),
					metaData.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}

	DFGHoldActions hold( _M( "DFG Do Add Inst Port" ) );
	return __super::dfgDoAddInstPort( binding, execPath, exec, instName, desiredPortName, portType, typeSpec, pathToConnect, connectType, extDep, metaData );
}

QString MaxDFGCmdHandler::dfgDoAddInstBlockPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString instName, QString blockName, QString desiredPortName, QString typeSpec, QString pathToConnect, QString extDep, QString metaData )
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;


		cmd.printf( _M( "$.DFGDoAddInstBlockPort \"%s\" \"%s\" \"%s\" typeSpec:\"%s\" pathToConnect:\"%s\" extDep:\"%s\" metaData:\"%s\" execPath:\"%s\"" ),
					instName.data(),
					blockName.data(),
					desiredPortName.data(),
					typeSpec.data(),
					pathToConnect.data(),
					extDep.data(),
					metaData.data(),
					execPath.data());
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}
	DFGHoldActions hold( _M( "DFG Add Inst Block Port" ) );
	return __super::dfgDoAddInstBlockPort( binding, execPath, exec, instName, blockName, desiredPortName, typeSpec, pathToConnect, extDep, metaData );
}

QString MaxDFGCmdHandler::dfgDoAddBlock( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredName, QPointF pos )
{
	EMIT2( _M("DFGDoAddBlock"), desiredName, pos, execPath );
	DFGHoldActions hold( _M( "DFG Add Block" ) );
	return __super::dfgDoAddBlock( binding, execPath, exec, desiredName, pos );
}

QString MaxDFGCmdHandler::dfgDoAddBlockPort( FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString blockName, QString desiredPortName, FabricCore::DFGPortType portType, QString typeSpec, QString pathToConnect, FabricCore::DFGPortType connectType, QString extDep, QString metaData )
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		MSTR portTypeStr = ToMSTR( portType );
		MSTR connectTypeStr = ToMSTR( connectType );
		cmd.printf( _M( "$.DFGDoAddBlockPort \"%s\" \"%s\" %s typeSpec:\"%s\" pathToConnect:\"%s\" connectType:%s extDep:\"%s\" metaData:\"%s\" execPath:\"%s\"" ),
					blockName.data(),
					desiredPortName.data(),
					portTypeStr.data(),
					typeSpec.data(),
					pathToConnect.data(),
					connectTypeStr.data(),
					extDep.data(),
					metaData.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}
	DFGHoldActions hold( _M( "DFG Add Block Port" ) );
	return __super::dfgDoAddBlockPort( binding, execPath, exec, blockName, desiredPortName, portType, typeSpec, pathToConnect, connectType, extDep, metaData );
}

QString MaxDFGCmdHandler::dfgDoAddNLSPort(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString desiredPortName, QString typeSpec, QString portToConnect, QString extDep, QString metaData)
{
	if (macroRecorder->Enabled())
	{
		MSTR cmd;
		cmd.printf( _M( "$.%s %s %s portToConnect:%s extDep:%s metaData:%s execPath:%s" ),
					_M( "DFGAddLocal" ),
					desiredPortName.data(),
					typeSpec.data(),
					portToConnect.data(),
					extDep.data(),
					metaData.data(),
					execPath.data() );
		macroRecorder->ScriptString( cmd.data() );
		macroRecorder->EmitScript();
	}

	DFGHoldActions hold(_M("DFG Add Local"));

	return __super::dfgDoAddNLSPort(binding, execPath, exec, desiredPortName, typeSpec, portToConnect, extDep, metaData);
}

void MaxDFGCmdHandler::dfgDoReorderNLSPorts(FabricCore::DFGBinding const &binding, QString execPath, FabricCore::DFGExec const &exec, QString itemPath, QList<int> indices)
{
	EMIT2(_M("DFGReorderLocals"), itemPath, indices, execPath);
	DFGHoldActions hold(_M("DFG Re-order Locals"));
	return __super::dfgDoReorderNLSPorts(binding, execPath, exec, itemPath, indices);
}

void MaxDFGCmdHandler::fabricCommand(
	QString cmdName,     
	QMap<QString, QString> cmdArgs, 
	bool doCmd,
	bool canUndo)
{ 
  MAXSPLICE_CATCH_BEGIN;

	if(!doCmd)  
	{
		// No need to do anything if the user won't see it
		if (macroRecorder->Enabled())
	 	{
			QString cmdQStr = "FabricCommand " + cmdName;
			
			if(cmdArgs.size() > 0)
			{
				cmdQStr += " #(";
				int count = 0;
				
				QMap<QString, QString>::iterator i;
				for (i = cmdArgs.begin(); i != cmdArgs.end(); ++i)
				{
					cmdQStr += "'" + i.key() + ":" + i.value() + "'";
					if(count < (cmdArgs.size() -1))
					{
						count ++;
						cmdQStr += ",";
					}
				}

				cmdQStr += ")";
			}
 
			MSTR cmd;
			cmd.printf(_M("$.%s"), cmdQStr.data());
	 		macroRecorder->ScriptString(cmd.data());
			macroRecorder->EmitScript();
	 	}

		if(canUndo)
		{
			MSTR r;
			r.printf(_M("%s"), cmdName.data());
			FabricHoldActions hold(r);
		}
	}

	else
		FabricUI::Commands::CommandManager::getCommandManager()->createCommand(
			cmdName, 
			cmdArgs);

  MAXSPLICE_CATCH_END;
}
