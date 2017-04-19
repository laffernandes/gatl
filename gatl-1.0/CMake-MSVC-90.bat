@ECHO OFF

IF (%1)==()           GOTO ALL
IF (%1)==(/cmake-all) GOTO ALL
IF (%1)==(/cmake-lib) GOTO LIB

ECHO.
ECHO.The input argument '%1' is unknown.
ECHO.
GOTO END


REM ########## ALL         #################################################
:ALL

SET LIBS=btriglib bmathlib smathlib stoolslib gridlib btoolslib lalib rgridlib galib
SET GENERATOR="Visual Studio 10"
SET BUILD_DIR=build

FOR %%l IN (%LIBS%) DO CALL %0 /cmake-lib %%l

PAUSE
GOTO END


REM ########## LIB         #################################################
:LIB

ECHO.CMake call to "%2"

IF EXIST "%2\%BUILD_DIR%" rmdir /S /Q "%2\%BUILD_DIR%"
mkdir "%2\%BUILD_DIR%"

cd "%2\%BUILD_DIR%"
cmake -G %GENERATOR% ..
cd ..\..

ECHO.

GOTO END


REM ########## END         #################################################
:END