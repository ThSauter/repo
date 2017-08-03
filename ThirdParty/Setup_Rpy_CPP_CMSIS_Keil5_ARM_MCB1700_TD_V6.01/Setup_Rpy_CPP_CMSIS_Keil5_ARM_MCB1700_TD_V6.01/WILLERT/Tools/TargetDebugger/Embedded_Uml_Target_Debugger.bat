@echo off
cd /d %~p0\bin

start Embedded_UML_Target_Debugger.exe %* 2> NUL

rem
rem Options can be specified like this: --xml "<product>\Samples\Code\GettingStarted\XMLData.xml" --communication Serial.dll --config
rem
