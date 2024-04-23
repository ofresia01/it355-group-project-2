@ECHO off

REM Define the relative path to the Java source files
SET SOURCE_PATH=src\chat_room

REM Define the name of the output folder within src
SET OUTPUT_FOLDER=out

ECHO Compiling server...
javac -d %OUTPUT_FOLDER% %SOURCE_PATH%\ChatServer.java %SOURCE_PATH%\ClientHandler.java %SOURCE_PATH%\Main.java
if errorlevel 1 (
    ECHO Error: Failed to compile server.
    PAUSE
    exit /b
)
ECHO Server compiled successfully.

ECHO Compiling client...
javac -d %OUTPUT_FOLDER% %SOURCE_PATH%\ChatClient.java
if errorlevel 1 (
    ECHO Error: Failed to compile client.
    PAUSE
    exit /b
)
ECHO Client compiled successfully.

ECHO starting server...
START java -cp %CD%\%OUTPUT_FOLDER% chat_room.Main
ECHO Server started.

ECHO starting clients...
START java -cp %CD%\%OUTPUT_FOLDER% chat_room.ChatClient
START java -cp %CD%\%OUTPUT_FOLDER% chat_room.ChatClient
START java -cp %CD%\%OUTPUT_FOLDER% chat_room.ChatClient