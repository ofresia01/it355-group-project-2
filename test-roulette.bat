@ECHO off

REM Define the relative path to the Java source files
SET SOURCE_PATH=src\roulette\src

REM Define the name of the output folder within src
SET OUTPUT_FOLDER=out

ECHO Compiling Roulette...
javac -d %OUTPUT_FOLDER% %SOURCE_PATH%\App.java %SOURCE_PATH%\Game.java %SOURCE_PATH%\GetInput.java %SOURCE_PATH%\ReadFile.java %SOURCE_PATH%\ReadFile.java %SOURCE_PATH%\ReadFile.java %SOURCE_PATH%\User.java
if errorlevel 1 (
  ECHO Error: Failed to compile Roulette.
  PAUSE
  exit /b
)
ECHO Roulette compiled successfully.

ECHO starting Roulette...
java -cp %CD%\%OUTPUT_FOLDER% App

PAUSE