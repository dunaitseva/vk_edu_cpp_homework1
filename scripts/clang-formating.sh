#!/bin/bash


TMP_DIR="./tmp"
LOG_FILE="./tmp/clang-formating.log"
TMP_FORM_FILE="./tmp/formated-file"
mkdir -p $TMP_DIR
touch $LOG_FILE
touch $TMP_FORM_FILE

#sudo apt install clang-format >> $LOG_FILE

STYLE="Google"
FORMATING_FILES=("./project/main.c" "./project/src/solver.c" \
                 "./project/include/solver.h" "project/include/point.h" \
                 "project/src/point.c" "./tests/core/SolverTests.cpp")
for file in ${FORMATING_FILES[*]}
do
    echo $file
    clang-format -style=$STYLE $file > $TMP_FORM_FILE || (echo "Error, check $LOG_FILE")
    diff $file $TMP_FORM_FILE
done