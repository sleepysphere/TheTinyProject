@echo off
echo 🔨 Compiling...
g++ -Iinclude src\vector.cpp src\Matrix.cpp src\LinearSystem.cpp src\PosSymLinSystem.cpp src\main.cpp -o test\main.exe

if %errorlevel% equ 0 (
    echo 🚀 Running...
    test\main.exe
) else (
    echo ❌ Compilation failed.
)
