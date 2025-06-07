@echo off
echo Compiling...
cd .. 
g++ -Iinclude src\Vector.cpp test\TestVector.cpp -o test\TestVector.exe

if %errorlevel% equ 0 (
    echo Running...
    test\TestVector.exe
) else (
    echo Compilation failed.
)
