#!/usr/bin/env bash


DEBUG_ONLY="" #  -debug-only is ONLY available if you build llvm with '-DCMAKE_BUILD_TYPE=Debug'

# allopsprofile
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=allopsprofile"
fi
"$LLVM_DIR"/bin/opt \
    -load-pass-plugin ./libAllOpsProfile.so \
    -passes=allopsprofile \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./allopsprofile-pass-output.ll

# replace-multiply
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=replace-multiply"
fi
opt -load-pass-plugin ./libReplaceMultiply.so \
    -passes=replace-multiply \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./replace-multiply-pass-output.ll

# replace-subtract
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=replace-subtract"
fi
opt -load-pass-plugin ./libReplaceSubtract.so \
    -passes=replace-subtract \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./replace-subtract-pass-output.ll

# wrongreplace
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=wrongreplace"
fi
opt -load-pass-plugin ./libWrongOpReplace.so \
    -passes=wrongreplace \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./wrongreplace-pass-output.ll

# functioncalls
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=functioncalls"
fi
opt -load-pass-plugin ./libFunctionCallsProf.so \
    -passes=functioncalls \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./functioncalls-pass-output.ll

# countmemop
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=countmemop"
fi
opt -load-pass-plugin ./libCountMemoryOp.so \
    -passes=countmemop \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./countmemop-pass-output.ll

# functioninfo
if [  "/usr" != "$LLVM_DIR"  ]; then
    DEBUG_ONLY="-debug-only=functioninfo"
fi
opt -load-pass-plugin ./libFunctionInfo.so \
    -passes=functioninfo \
    $DEBUG_ONLY \
    $LLVM_IR_FILE \
    -stats -S -o ./functioninfo-pass-output.ll

## removeunreables
#opt -load-pass-plugin ./libRemoveUnreacheables.so \
#    -passes=removeunreables \
#    -debug-only=removeunreables \
#    $LLVM_IR_FILE \
#    -stats -S -o ./removeunreables-pass-output.ll