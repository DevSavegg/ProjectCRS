@echo off
REM Set the GCC compiler path if not already in PATH
set GCC=gcc

REM Define directories
set SRC_DIR=src/libraries
set OBJ_DIR=obj

REM Create the object directory if it doesn't exist
if not exist %OBJ_DIR% mkdir %OBJ_DIR%

REM Initialize a variable to hold object file names
set "OBJ_FILES="

REM Enable delayed expansion for dynamic variables
setlocal enabledelayedexpansion

REM Compile all .c files in the SRC_DIR and subdirectories
echo Compiling library files...
for /r %SRC_DIR% %%f in (*.c) do (
    echo Compiling %%f...
    %GCC% -c %%f -o %OBJ_DIR%/%%~nf.o
    set "OBJ_FILES=!OBJ_FILES! %OBJ_DIR%/%%~nf.o"
)

REM Compile and link the main file with all libraries
echo Compiling main file and linking...
%GCC% main.c !OBJ_FILES! -o main.exe

REM Clean up
echo Build complete. Output: main.exe
