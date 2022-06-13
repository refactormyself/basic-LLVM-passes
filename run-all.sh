#!/usr/bin/env bash

HERE=$PWD

if [ "" = "$1" ]; then
    echo "Install location of llvm is not supplied. Trying out '/usr'"
    LLVM_DIR="/usr"
else
    LLVM_DIR=$1
fi

if [ "" = "$2" ]; then
    echo "ERROR: Path to the lit binary to supplied"
    echo "The script needs 2 arguments: 'PATH TO LLVM INSTALL' and 'PATH TO LIT (usually in the build folder)'"
    exit
else
    LLVM_EXTERNAL_LIT=$2
fi

echo  "#----> LLVM_DIR = $LLVM_DIR"
echo  "#----> LLVM_EXTERNAL_LIT = $LLVM_EXTERNAL_LIT"

# Just clean everything
#rm -rf build
mkdir build
cd build || exit

# Build the project, we get our passes as shared object artefacts that we'll later load into 'opt'
cmake -DLLVM_DIR="$LLVM_DIR" -DLLVM_EXTERNAL_LIT="$LLVM_EXTERNAL_LIT" ..
cmake --build . --target check-llvmpasses #\
#  RemoveUnreachable ReplaceSubtract ReplaceMultiply AllOpsProfile \
#  WrongOpReplace FunctionCallsProf CountMemoryOp FunctionInfo

make
# exit

SRC_CODE_TO_TEST="$HERE/test/sample-test/sample_source_code.cpp"
LLVM_IR_FILE="./input_IR_from_code.ll"

# Generate the IR from the inputs source code. FIXME: Note that -O0 will not work: WHY?!
"$LLVM_DIR"/bin/clang++ -emit-llvm -S -O1 "$SRC_CODE_TO_TEST" -o $LLVM_IR_FILE

# Use the LLVM 'opt' tool to run the passes, we are loading them as shared objects and activating the pass
#. "$HERE"/run-passes.sh

cd "$HERE" || exit
