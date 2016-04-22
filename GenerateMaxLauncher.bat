

@echo off

REM This file generates a launcher batch file that in turn generates a max.ini file when run for the first time
REM It then launches 3dsmax using the generated ini file. 
REM The Target dir and Max version are args passed from visual studio when the batch file is run as part of a post build step.

set TARGETDIR=%~1
set MAXVERSION=%~2
set LAUNCHER="%TARGETDIR%3dsmax%MAXVERSION%.bat"

echo Writing: %LAUNCHER%

IF NOT EXIST "%TARGETDIR%" ( MKDIR "%TARGETDIR%")
REM Clear the contents of the file if it already exists. 
@echo.>  %LAUNCHER%

@echo @echo off>> %LAUNCHER%

@echo REM This batch file is generated by the build process for the Fabric for 3dsmax plugin.>> %LAUNCHER%
@echo REM The first time this batch file it run, it generates a plugin ini file that causes 3dsmax to load the splice for max plugin.>> %LAUNCHER%
@echo REM 3dsmax is then launched using the generated plugin ini file.>> %LAUNCHER%
@echo set FABRIC3DSMAXDIR=%%~dp0>> %LAUNCHER%
@echo.>> %LAUNCHER%
@echo if NOT EXIST %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini (>> %LAUNCHER%
@echo 	REM To allow users to run this file, and load splice without installing>> %LAUNCHER%
@echo 	REM anything, we generate a new ini file and pass it to Max to override>> %LAUNCHER%
@echo 	REM its current plugin directories setting.  We recreate the default>> %LAUNCHER% 
@echo 	REM plugin ini file so hopefully nothing changes too much.  If you have a non>> %LAUNCHER%
@echo 	REM default plugin path settings, remove the -p argument to max at the end of >> %LAUNCHER%
@echo 	REM this script and add the path to the 3dsMax>> %LAUNCHER%
@echo 	echo Generating new plugin ini file.>> %LAUNCHER%
@echo.>> %LAUNCHER%
@echo 	REM add in original plugins>> %LAUNCHER%
@echo 	@echo [Directories] ^>^> %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini>> %LAUNCHER%
@echo 	@echo Additional MAX plug-ins=%%ADSK_3DSMAX_x64_%MAXVERSION%%%\PlugIns\ ^>^> %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini>> %LAUNCHER%
@echo 	@echo Fabric Plugins=%%~dp0plugin\ ^>^> %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini>> %LAUNCHER%
@echo 	@echo [Help] ^>^> %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini>> %LAUNCHER%
@echo 	@echo mental ray Help=http://www.autodesk.com/mentalray-help-2013-enu ^>^> %%FABRIC3DSMAXDIR%%Generated.Plugin.Fabric.ini>> %LAUNCHER%
@echo )>> %LAUNCHER%
@echo.>> %LAUNCHER%
@echo CALL %%FABRIC3DSMAXDIR%%..\..\environment.bat>> %LAUNCHER%
@echo REM Enable the system to find the FabricCore and Scintilla dlls>> %LAUNCHER%
@echo set PATH=%%PATH%%;%%FABRIC_DIR%%bin;%%FABRIC3DSMAXDIR%%\plugin>> %LAUNCHER%
@echo.>> %LAUNCHER%
@echo REM Launch Max>> %LAUNCHER%
@echo START "3dsMax - Fabric" "%%ADSK_3DSMAX_x64_%MAXVERSION%%%\3dsmax.exe" -vo -p "%%FABRIC3DSMAXDIR%%/Generated.Plugin.Fabric.ini">> %LAUNCHER%

