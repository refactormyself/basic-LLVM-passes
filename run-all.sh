#!/usr/bin/env bash

# Build the Pass
LLVM_DIR=$1

# Just clean everything
rm -rf build
mkdir build
cd build

# now build the project
cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ..
make

LLVM_IR_FILE="../tmp/sample.ll"
SRC_CODE="../test-codes/sample_source_code_plus.cpp"

# # clean off old ll files
# rm -rf ../tmp && mkdir ../tmp

# Note that -O0 will not work: WHY?!
clang++ -emit-llvm -S -O1 $SRC_CODE -o $LLVM_IR_FILE

opt -load-pass-plugin ./libAllOpsProfile.so \
    -passes=allopsprofile \
    -debug-only=allopsprofile \
    $LLVM_IR_FILE \
    -stats -S -o ../out/allopsprofile-passed.ll

cd ..