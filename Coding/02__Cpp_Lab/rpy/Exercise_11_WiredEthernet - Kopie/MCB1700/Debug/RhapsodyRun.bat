@rem The InvokeExecutable property does not support to extract macros, 
@rem so we generate this batch file as a workaround. 
@if not exist CurrentFileList.txt copy NUL CurrentFileList.txt 
@copy CurrentFileList.txt PreviousFileList.txt 
@dir /s /on /b *.cpp *.c *.h > CurrentFileList.txt 
@call "C:\Users\Hochschule Ulm\Willert\RXF-Eval_Rpy-Cpp-ARM_V6.01\Tools\RhapsodyRun.bat" 
