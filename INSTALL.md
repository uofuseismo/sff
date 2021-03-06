# Build Instructions

This document outlines the build instructions.

## Prerequisites

The following are the required prerequisites:

   1. [CMake](https://cmake.org/) v.3.10 or greater.
   2. A fully C++17 compliant compiler.
   3. [GTest](https://github.com/google/googletest) for testing.

The following are the optional prerequisites:
 
   1. [libmseed](https://github.com/iris-edu/libmseed) for reading miniSEED files.  This library requires libmseed v3 or greater.
   2. Python3, pytest3, and [pybind11](https://github.com/pybind/pybind11) if Python bindings are required.

## Getting the Source

The source code can be downloaded with git, e.g.,

    https://github.com/uofuseismo/sff.git

## Configure 

After successfully installing the dependencies and obtaining the source code next descend into the sff directory and generate the makefile.  To do this, I prefer the use of a configuration script.

    #!/bin/bash
    export CXX=g++
    export BUILD_DIR=gcc_build
    if [ -d ${BUILD_DIR} ]; then
       rm -rf ${BUILD_DIR}
    fi
    mkdir ${BUILD_DIR}
    cd ${BUILD_DIR}
    cmake ../ \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_CXX_FLAGS="-g -Wall -Wextra" \
    -DWRAP_PYTHON=TRUE
    cd ..

If libmseed is installed in a non-standard behavior you can influence CMake's behavior by adding

    export MINISEED_ROOT=/path/to/mseed

## Building

Following a successful configuration descend into the build directory and type

    make

To verify nominal functionality of the software on your system next type

    make test


