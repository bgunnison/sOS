@echo off
setlocal

cd /d "%~dp0"

cmake --preset avr-debug
if errorlevel 1 exit /b 1

cmake --build --preset avr-debug
if errorlevel 1 exit /b 1

pause
endlocal
