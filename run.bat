@echo off
cd /d "%~dp0"

echo Building Digital Evidence Chain System...
g++ -std=c++11 -Wall -Wextra -Wpedantic -Iinclude src\*.cpp -o DigitalEvidenceChain.exe

if errorlevel 1 (
    echo.
    echo Build failed. Make sure g++ is installed and the application is not already running.
    pause
    exit /b 1
)

echo Build successful.
echo Starting application...
echo.

DigitalEvidenceChain.exe

echo.
pause
