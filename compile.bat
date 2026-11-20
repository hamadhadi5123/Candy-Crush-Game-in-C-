@echo off
title Fast Compile Candy Crush (SFML)
cd /d "%~dp0"
echo Compiling candy_crush.cpp (High Speed with PCH)...
"E:\Softwares\mingw64\bin\g++.exe" -include pch.h candy_crush.cpp -o candy_crush.exe -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
if %ERRORLEVEL% EQU 0 (
    copy /y candy_crush.exe CandyCrush.exe >nul
    echo Compilation Successful! candy_crush.exe and CandyCrush.exe are ready.
) else (
    echo Compilation failed.
)
pause
