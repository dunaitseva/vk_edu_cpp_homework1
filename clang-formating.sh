#!/bin/bash


TMP_DIR="./tmp"
LOG_FILE="./tmp/clang-formating.log"
mkdir -p $TMP_DIR
touch $LOG_FILE

sudo apt install clang-format >> $LOG_FILE

STYLE="Google"
FORMATING_FILES=("./project/main.c" "./project/src/solver.c" "./project/include/solver.h")
for file in ${FORMATING_FILES[*]}
do
    echo $file
    clang-format -style=$STYLE -i $file >> $LOG_FILE || (echo "Error, check $LOG_FILE")
done