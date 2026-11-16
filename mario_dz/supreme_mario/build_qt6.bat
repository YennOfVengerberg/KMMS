@echo off

setlocal
cd /d "%~dp0"

set BUILD_TYPE=Ninja
set BUILD_FOLDER=build_qt6
set SOURCE_FOLDER=src
set GAME_TYPE=Qt6

chcp 65001 >nul

if not defined QT_PREFIX set QT_PREFIX=D:\mingw\ucrt64

cmake -S "%SOURCE_FOLDER%" -B "%BUILD_FOLDER%" ^
	-G "%BUILD_TYPE%" ^
	-DGAME_TYPE="%GAME_TYPE%" ^
	-DCMAKE_PREFIX_PATH="%QT_PREFIX%"
if errorlevel 1 goto :error

cmake --build "%BUILD_FOLDER%"
if errorlevel 1 goto :error

"%BUILD_FOLDER%\super_mario.exe"
goto :end

:error
echo.
echo Qt6 build failed.
pause

:end
endlocal
