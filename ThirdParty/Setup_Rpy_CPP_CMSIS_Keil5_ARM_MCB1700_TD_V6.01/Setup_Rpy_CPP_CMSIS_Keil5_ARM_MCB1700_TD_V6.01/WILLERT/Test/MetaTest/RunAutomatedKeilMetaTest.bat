@rem $URL: https://svn.willert.de/V6/trunk/Component/CompilerAndTarget/Keil5_ARM/Test/MetaTest/RunAutomatedKeilMetaTest.bat $

@set InstalledProductPath=@WILLERT_1@\@WST_RELEASE_NAME@

cd "@RPYPROG_1@"
RhapsodyCL.exe -verbose -dev_ed -lang=CPP -cmd=open "%InstalledProductPath%\Test\MetaTest\MetaTest.rpy" -cmd=generate -cmd=syncmake
@if ERRORLEVEL 2 (
	echo Errorlevel of RhapsodyCL: %errorlevel%
	echo   List of error level codes from Rhapsody help:
	echo   100: failed to open the project file  105: errors were found in check model
	echo   101: license not found                106: unresolved elements in scope
	echo   102: code generation failed           107: comp. or configuration name error
	echo   103: failed to load the project       108: build failed
	echo   104: failed to create or write to the code generation folder
	exit /b %errorlevel%
)


cd /d "%InstalledProductPath%\Tools\WSTDeployer"
"@RPYPROG_1@\jdk\jre\bin\java" -classpath bin;WSTDeployer.jar;log4j-1.2.14.jar;jdom.jar;"@RPY_1@\Share\JavaAPI\rhapsody.jar" -Djava.library.path="@RPY_1@\Share\JavaAPI" wst.WSTDeployer debug version "setSourceDir(%InstalledProductPath%/Test/MetaTest/TargetComponent/Release)" "setDestProj(%InstalledProductPath%/Test/MetaTest/GettingStartedMetaTest/GettingStarted.uvprojx)" version deploy
@if ERRORLEVEL 1 ( echo Errorlevel of Deployer Java call: %errorlevel% & exit /b %errorlevel% )





cd /d "%InstalledProductPath%\Test\MetaTest\GettingStartedMetaTest"
@echo ### Building MetaTest in uVisison ####
"@KEIL_1@\UV4\Uv4.exe" -r "GettingStarted.uvprojx" -o BuildLog.txt
@echo ######## MetaTest Build Log ##########
@type BuildLog.txt






@echo ### Executing MetaTest in uVisison ###
"@KEIL_1@\UV4\Uv4.exe" -D "GettingStarted.uvprojx"
@echo off
"@RPYPROG_1@\jdk\jre\bin\java" -cp "%InstalledProductPath%\NotForRelease\Tools" RemoveNonDisplayableAscii SoftwareExecutionLog.txt
echo ########### Debugger Log #############
type DebuggerExecutionLog.txt
echo ######## Test Execution Log ##########
type SoftwareExecutionLog.txt

>nul find "All tests passed." SoftwareExecutionLog.txt && (
  echo MetaTest execution was succesfull, all tests passed.
) || (
  echo ERROR: MetaTest did not execute correctly or reported test failures during execution!
  exit /b 1
)



rem Go back to default test execution directory.
cd /d "%InstalledProductPath%"
