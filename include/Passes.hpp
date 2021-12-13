#ifndef PASSES_HPP
#define PASSES_HPP

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace passes {
    class AllOpsProfilePass : public llvm::PassInfoMixin<AllOpsProfilePass> {
    public:
        llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &AM);
    };

    class ReplaceMultiplyPass : public llvm::PassInfoMixin<ReplaceMultiplyPass> {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

    class ReplaceSubtractPass : public llvm::PassInfoMixin<ReplaceSubtractPass> {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

    class MemoryOpCountPass : public llvm::PassInfoMixin<MemoryOpCountPass> {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

    class RemoveUnreachablePass : public llvm::PassInfoMixin<RemoveUnreachablePass> {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };

    class FunctionCallsProfilePass : public llvm::PassInfoMixin<FunctionCallsProfilePass> {
    public:
        llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &AM);
    };

    class FunctionsInfoPass : public llvm::PassInfoMixin<FunctionsInfoPass> {
    public:
        llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &AM);
    };

    class WrongOpReplacePass : public llvm::PassInfoMixin<WrongOpReplacePass> {
    public:
        llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
    };
} // end of passes namespace

#endif // PASSES_HPP
