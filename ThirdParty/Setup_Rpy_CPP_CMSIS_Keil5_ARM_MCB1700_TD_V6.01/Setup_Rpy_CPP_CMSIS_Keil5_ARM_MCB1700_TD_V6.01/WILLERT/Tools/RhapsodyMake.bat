@echo off

rem ============================================================================
rem
rem $Id: RhapsodyMake.bat 34166 2016-04-06 10:58:20Z eroemer $
rem $URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/RhapsodyMake.bat $
rem
rem Batch file that is called by Rhapsody build command
rem
rem This file belongs to the Willert Software Tools RXF Product:  
rem Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
rem Copyright (c) 2013, Willert Software Tools GmbH.
rem 
rem For detailed information about this product see release info file:
rem @WILLERT_2@/@WST_RELEASE_NAME@/ReleaseInfo.txt
rem
rem ============================================================================

call %1 %2 %3



if not "%WST_DEPLOYER_DISABLED%"=="true" (
  rem  %~dp0 will be expanded to the path which contains this batch file.
  call "%~dp0\WSTDeployer\WSTDeployer.bat" debug version deploy
)



