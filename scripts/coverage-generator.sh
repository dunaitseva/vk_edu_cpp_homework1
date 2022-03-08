#!/bin/bash

BUILD_DIRECTORY="build"

pip install gcovr

./scripts/build.sh -c -t

cd $BUILD_DIRECTORY || (echo "Error. $BUILD_DIRECTORY not created." && exit 1)
ctest
cd ..
EXCLUDING_FILES=".*_deps.*|.*tests.*"
#EXCLUDING_FILES=".*_deps.*"
REPORT_FILE_NAME="coverage.xml"
gcovr -r . ./build -e $EXCLUDING_FILES -o $REPORT_FILE_NAME --xml
