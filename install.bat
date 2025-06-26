@echo off
setlocal enabledelayedexpansion

rem Check if the script is run as administrator
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo This script requires administrative privileges. Please run as administrator.
    pause
    exit /b 1
)

rem Define base path to Windows SDK includes
set "base_path=C:\Program Files (x86)\Windows Kits\10\Include"

rem Find latest version folder under base_path
set version=
for /d %%i in ("%base_path%\*") do (
    set "version=%%~nxi"
)

if "%version%"=="" (
    echo Could not find Windows SDK version folder under "%base_path%".
    pause
    exit /b 1
)

set "include_path=%base_path%\%version%\ucrt"

rem Verify src\peroxide.h exists
if not exist "%~dp0src\peroxide.h" (
    echo Source file src\peroxide.h not found.
    pause
    exit /b 1
)

rem Move peroxide.h to the include directory
echo Moving "%~dp0src\peroxide.h" to "%include_path%"
move /Y "%~dp0src\peroxide.h" "%include_path%\"

if errorlevel 1 (
    echo Failed to move peroxide.h.
    pause
    exit /b 1
)

echo peroxide.h installed successfully.
pause
