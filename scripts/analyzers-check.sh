#!/bin/bash

LOG_FILE="./tmp/build.log"
TMP_DIR="tmp"
mkdir -p $TMP_DIR
touch $LOG_FILE
mkdir $BUILD_DIR && echo "Creating $BUILD_DIR directory"

# Installing fbinfer
#echo "START INSTALLING fbinfer"
#VERSION=1.0.0;
#curl -sSL "https://github.com/facebook/infer/releases/download/v$VERSION/infer-linux64-v$VERSION.tar.xz" | sudo tar -C /opt -xJ
#sudo ln -s "/opt/infer-linux64-v$VERSION/bin/infer" /usr/local/bin/infer


# Installing cpplint
echo "START INSTALLING cpplint"
pip -q install cpplint

# Installing scan-build
echo "START INSTALLING scan-build"
sudo apt-get -qq install clang-tools

# Installing cppcheck
echo "START INSTALLING cppcheck"
sudo apt-get -qq install cppcheck

SOURCES_DIR="project"
echo "START ANALYZE cppcheck"
cppcheck $SOURCES_DIR || ( echo "cppcheck check failed" && exit 1)

echo "START ANALYZE cpplint"
cpplint --recursive --filter=-legal/copyright $SOURCES_DIR ||( echo "cpplint check failed" && exit 1)

echo "START ANALYZE scan-build"
cd build
scan-build make parabola_builder || ( echo "scan-build check failed" && exit 1)
scan-build make parabola_solver || ( echo "scan-build check failed" && exit 1)


