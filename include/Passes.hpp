#ifndef LLVM_NEW_PASSES_PASSES_H
#define LLVM_NEW_PASSES_PASSES_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace allopsprofilepass
{
    class AllOpsProfilePass : public llvm::PassInfoMixin<AllOpsProfilePass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &AM);
    };

} // end of allopsprofilepass namespace
namespace replacemultiplypass
{
    class ReplaceMultiplyPass : public llvm::PassInfoMixin<ReplaceMultiplyPass>
} // end of replacesubtractpass namespace

namespace replacesubtractpass
{
    class ReplaceSubtractPass : public llvm::PassInfoMixin<ReplaceSubtractPass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

} // end of replacemultiplypass namespace

#endif // LLVM_NEW_PASSES_PASSES_H
