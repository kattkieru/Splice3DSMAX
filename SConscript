#
# Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.
#

import os, platform

Import('parentEnv', 
          'MAX_VERSION')

buildOS = platform.system()
buildArch = 'x86_64'
buildType = 'Release'

scenegraph_dir = os.environ['FABRIC_SCENE_GRAPH_DIR']
prebuilt_dir = os.path.join(scenegraph_dir, 'ThirdParty', 'PreBuilt', buildOS, buildArch, 'VS2013', 'Release')

env = parentEnv.Clone()

stageDir = env.Dir(scenegraph_dir).Dir('stage').Dir(buildOS).Dir(buildArch).Dir(buildType)

env['ENV'] = os.environ
  
qt_dir = os.path.join(prebuilt_dir, 'qt', '4.8.7')
env['ENV']['QT_DIR'] = qt_dir

qtwinmigrate_dir = os.path.join(prebuilt_dir, 'qt-solutions', 'qtwinmigrate')
env['ENV']['QTWINMIGRATE_DIR'] = qtwinmigrate_dir

# reset the Max SDK so it gets the one in our repo, just in case :)
env['ENV']['MaxSDKPath'] = ''
env['ENV']['FABRIC_DIR'] = os.environ['FABRIC_DIR']
env['ENV']['FABRIC_SCENE_GRAPH_DIR'] = scenegraph_dir


maxFiles = []
srcnodeDir = env.Dir('.').srcnode().abspath
maxBuild = env.Command(
    'build max '+ MAX_VERSION,
    [],
    [
        ['cmd.exe', '/c', os.path.join(srcnodeDir, 'build.bat'), '16', MAX_VERSION, 'x64', os.path.join(srcnodeDir, 'Fabric3dsmax.sln')],
    ]
)
maxFiles.append(maxBuild)

alias = env.Alias('splicemax_build', maxFiles)
spliceData = (alias, maxFiles)
Return('spliceData')
