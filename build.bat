@echo off
setlocal enabledelayedexpansion

:: Compiler and flags
set COMPILER=g++
set INCLUDES=-Iinclude

:: Manually build a list of all .cpp files in src
set SOURCES=
for %%f in (src\*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

:: Loop over test files and compile each with sources
for %%t in (test\*.cpp) do (
    set TEST=%%t
    call :compileTest %%t
)

echo All test files built.
goto :eof

:compileTest
set FILE=%1
for %%n in (%FILE%) do set NAME=%%~n
echo Compiling %FILE% -> test\%NAME%.exe ...
%COMPILER% %INCLUDES% %SOURCES% %FILE% -o test\%NAME%.exe
goto :eof
