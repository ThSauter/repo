@echo off

rem Determine JRE architecture
set WST_JAVA_ARCH=NOT_IN_PATH
rem Inspired by:
rem http://stackoverflow.com/questions/15283660/windows-bat-file-determining-if-java-install-is-32-bit-or-64-bit
"%WST_JAVA_PATH:"=%java" -d64 -version >nul 2>&1
if errorlevel 1 goto maybe32bit
set WST_JAVA_ARCH=64
goto RpyCheck
:maybe32bit
if "%WST_JAVA_PATH:"=%"=="" (
	echo WST_JAVA_PATH is not explicitely set yet.
	where java >nul 2>&1
	if errorlevel 1 goto RpyCheck
	set WST_JAVA_ARCH=32
) else (
	echo WST_JAVA_PATH is set to %WST_JAVA_PATH%
	"%WST_JAVA_PATH:"=%java" -version >nul 2>&1
	if errorlevel 1 goto RpyCheck
	set WST_JAVA_ARCH=32
)

:RpyCheck
rem Determine Rhapsody architecture (if there is a WIN32 subfolder, it IS 64 bit)
if exist "@RPY_1@\Share\JavaAPI\WIN32" (
  set WST_RPY_ARCH=64
) else (
  set WST_RPY_ARCH=32
)

if %WST_JAVA_ARCH%==NOT_IN_PATH (
	echo ========================================================================
  echo ERROR: Could not find any Java version.
  goto ExitError
) else (
  echo Your system has %WST_JAVA_ARCH%-Bit Java in the PATH and Rhapsody %WST_RPY_ARCH%-Bit installed.
)

rem Check combination
if %WST_JAVA_ARCH%==64 (
	if %WST_RPY_ARCH%==64 (
    echo Your setup should work properly, as it is a clean 64-Bit setup.
    goto ExitOk
  )
)
if %WST_JAVA_ARCH%==32 (
	if %WST_RPY_ARCH%==32 (
    echo Your setup should work properly, as it is a clean 32-Bit setup.
    goto ExitOk
  )
)
echo ========================================================================
echo ERROR: Java and Rhapsody both need to be 32- or 64-Bit versions to work
echo        together properly. 

:ExitError
echo ------------------------------------------------------------------------
echo Please edit the file
echo @WILLERT_1@\@WST_RELEASE_NAME@\Tools\WSTDeployer\WSTDeployer.bat
echo and set JAVAPATH to the absolute path of your java %WST_RPY_ARCH%-Bit bin directory.
echo Attention: If specified, the path needs to end with a BACKSLASH \ !
echo Do not add quotes or blank spaces.
echo Afterwards please retry to deploy.
echo ========================================================================
start notepad WSTDeployer.bat
exit /B 1

:ExitOk
exit /B 0
