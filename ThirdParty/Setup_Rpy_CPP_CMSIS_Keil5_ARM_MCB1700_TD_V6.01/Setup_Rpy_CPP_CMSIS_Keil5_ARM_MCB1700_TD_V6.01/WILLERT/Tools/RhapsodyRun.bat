@echo off

rem ============================================================================
rem $Id: RhapsodyRun.bat 34169 2016-04-06 16:00:42Z eroemer $
rem $URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/RhapsodyRun.bat $
rem
rem Batch file that is called when "Run" or [!]-button is selected in Rhapsody.
rem
rem This file belongs to the Willert Software Tools RXF Product:  
rem Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
rem Copyright (c) 2013, Willert Software Tools GmbH.
rem 
rem For detailed information about this product see release info file:
rem @WILLERT_2@/@WST_RELEASE_NAME@/ReleaseInfo.txt
rem
rem ============================================================================

echo.
echo ===================================================================
echo.
echo Nothing to be done in Rhapsody's RUN step.
echo.
echo The BUILD step in Rhapsody has deployed generated files together
echo with the RXF files into your Keil uVision 5 project.
echo.
echo Please build and launch your software in Keil uVision 5. 
echo.
echo ===================================================================
echo.
echo.
if not exist SuppressRunMessage (
  timeout /T 10
  echo The existance of this file suppresses the console window with the Rhapsody RUN command message. > SuppressRunMessage
)
