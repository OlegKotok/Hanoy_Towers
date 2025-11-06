#!/bin/bash

# Detect OS
OS=$(uname -s)
BUILD_DIR="build"

echo "Detected OS: $OS"

# Clean and create build directory
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR

case $OS in
    "Darwin")
        echo "Building for Windows (cross-compile with MinGW-w64)..."
        cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-w64-toolchain.cmake ..
        cmake --build .
        echo "Executable: HanoyTowers.exe"
        ;;
    "MINGW"*|"MSYS"*|"CYGWIN"*)
        echo "Building for Windows (native)..."
        cmake ..
        cmake --build . --config Release
        echo "Executable: Release/HanoyTowers.exe"
        ;;
    "Linux")
        echo "Error: This is a Win32 application and cannot run on Linux"
        echo "Use Wine or cross-compile for Windows target"
        exit 1
        ;;
    *)
        echo "Unsupported OS: $OS"
        exit 1
        ;;
esac

echo "Build completed!"
