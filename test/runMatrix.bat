@echo off
echo Compiling...
cd .. 
g++ -Iinclude src\Vector.cpp src\Matrix.cpp test\TestMatrix.cpp -o test\TestMatrix.exe

if %errorlevel% equ 0 (
    echo Running...
    test\TestMatrix.exe
) else (
    echo Compilation failed.
)
