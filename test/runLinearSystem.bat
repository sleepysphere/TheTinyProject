@echo off
echo Compiling...
cd .. 
g++ -Iinclude src\Vector.cpp src\Matrix.cpp src\LinearSystem.cpp test\TestLinearSystem.cpp -o test\TestLinearSystem.exe

if %errorlevel% equ 0 (
    echo Running...
    test\TestLinearSystem.exe
) else (
    echo Compilation failed.
)
