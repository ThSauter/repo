@echo off
rem
rem  Batch file to start up the WST-Deployer
rem 
rem  Copyright (c) 2016, Willert Software Tools GmbH
rem  $Id: WSTDeployer.bat 34109 2016-03-21 13:41:07Z mspieker $
rem  $URL: https://svn.willert.de/V6/trunk/Component/Shared/Tools/WSTDeployer/WSTDeployer.bat $
rem 
rem To set the path to a specific version of java, please set the following variable.
rem Per default it is preset to the JRE delivered with IBM Rational Rhapsody.
rem 
rem Attention:
rem               -> The path must NOT to end with a BACKSLASH \
rem               -> Please do not remove the "QUOTES"
rem               =============================================================
SET WST_JAVA_PATH="@RPYPROG_1@\jre\bin"
rem               =============================================================


set OLDDIR=%CD%
cd /D %~dp0

rem If the WST_JAVA_PATH was modified and you experience problems with the deployer, please
rem remove the "rem" of the following two line to perform a Java 32/64 Bit compatilbilty check.
rem call Check32-vs-64Bit.bat
rem if not %errorlevel%==0 pause && exit /B 1

echo Start deployer

"%WST_JAVA_PATH:"=%\java" -classpath bin;WSTDeployer.jar;log4j-1.2.14.jar;jdom.jar;"@RPY_1@\Share\JavaAPI\rhapsody.jar" -Djava.library.path="@RPY_1@\Share\JavaAPI" wst.launcher.WSTDeployerLauncher %1 %2 %3 %4 %5 %6 >>WSTDeployerCallLog.txt 2>&1
if not %errorlevel%==0 echo ---------------------------------------------- && echo The WSTDeployer reported a warning or problem: && type WSTDeployerCallLog.txt && echo ---------------------------------------------- && pause

cd /D %OLDDIR%
