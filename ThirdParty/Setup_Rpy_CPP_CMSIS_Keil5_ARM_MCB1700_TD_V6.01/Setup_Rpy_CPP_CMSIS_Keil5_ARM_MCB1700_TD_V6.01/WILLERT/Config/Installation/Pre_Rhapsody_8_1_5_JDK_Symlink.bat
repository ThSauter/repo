if exist "@RPYPROG_1@\jdk\jre" echo Rhapsody jdk\jre folder found. > "%~dp0\Pre_Rhapsody_8_1_5_JDK_Symlink_Log.txt"

if not exist "@RPYPROG_1@\jdk\jre" (
  echo Rhapsody seems older than 8.1.5, creating symlink from jdk\jre to jre folder... > "%~dp0\Pre_Rhapsody_8_1_5_JDK_Symlink_Log.txt"
  md "@RPYPROG_1@\jdk" >> "%~dp0\Pre_Rhapsody_8_1_5_JDK_Symlink_Log.txt"
  mklink /d "@RPYPROG_1@\jdk\jre" "@RPYPROG_1@\jre" >> "%~dp0\Pre_Rhapsody_8_1_5_JDK_Symlink_Log.txt"
)
