#ifndef LLVM_NEW_PASSES_PASSES_H
#define LLVM_NEW_PASSES_PASSES_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace replacemultiplypass
{
    class ReplaceMultiplyPass : public llvm::PassInfoMixin<ReplaceMultiplyPass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

} // end of replacemultiplypass namespace


#endif // LLVM_NEW_PASSES_PASSES_H
