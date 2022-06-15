## Basic LLVM Passes
This project demonstrates how to write passes in LLVM. Both analysis and transformation passes
are demonstration, however these passes are trivial.

### TO RUN
`sh ./run-all.sh $PATH_TO_LLVM_INSTALL_DIR $PATH_TO_LLVM_BUILD_DIR`


### Concepts donmstrated in this project
- Using the LLVM Pass Manager
- Using the *IRBuilder* for LLVM IR code generation
- Constant Folding
- Compiling an LLVM IR code
- Testing with LLVM tools: LIT, FileCheck
