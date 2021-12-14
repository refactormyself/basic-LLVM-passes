#ifndef LLVM_NEW_PASSES_PASSES_H
#define LLVM_NEW_PASSES_PASSES_H
#ifndef LLVM_SIMPLE_PASSES_H
#define LLVM_SIMPLE_PASSES_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace allopsprofilepass
{
    class AllOpsProfilePass : public llvm::PassInfoMixin<AllOpsProfilePass>

} // end of allopsprofilepass namespace
namespace replacemultiplypass
{
    class ReplaceMultiplyPass : public llvm::PassInfoMixin<ReplaceMultiplyPass>
} // end of replacemultiplypass namespace

namespace replacesubtractpass
{
    class ReplaceSubtractPass : public llvm::PassInfoMixin<ReplaceSubtractPass>
} // end of replacesubtractpass namespace

namespace memoryopcountpass
{
    class MemoryOpCountPass : public llvm::PassInfoMixin<MemoryOpCountPass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Function &M, llvm::FunctionAnalysisManager &AM);
    };
} // end of memoryopcountpass namespace

namespace removeunreablespass
{
    class RemoveUnreacheablesPass : public llvm::PassInfoMixin<RemoveUnreacheablesPass>

} // end of removeunreablespass namespace

namespace wrongreplacepass
{
    class WrongOpReplacePass : public llvm::PassInfoMixin<WrongOpReplacePass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
    };
} // end of wrongreplacepass namespace
namespace functioncallspass
{
    class FunctionCallsProfilePass : public llvm::PassInfoMixin<FunctionCallsProfilePass>
    {
    public:
        llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &AM);
    };

} // end of functioncallspass namespace

#endif // LLVM_NEW_PASSES_PASSES_H

#endif // LLVM_SIMPLE_PASSES_H
