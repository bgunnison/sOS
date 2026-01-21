@echo off
setlocal

cd /d "%~dp0"

cmake -P avr-clean.cmake
if errorlevel 1 exit /b 1

if exist "%~dp0bin" rmdir /s /q "%~dp0bin"
if exist "%~dp0obj" rmdir /s /q "%~dp0obj"

pause
endlocal
