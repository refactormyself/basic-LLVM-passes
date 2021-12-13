#include "Passes.hpp"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Module.h"


#define DEBUG_TYPE "functioninfo" // command line flag to trigger debug for the pass

STATISTIC(ReplaceCount, "The # of functions found.");

using namespace passes;
using namespace llvm;

PreservedAnalyses FunctionsInfoPass::run(Module &M, ModuleAnalysisManager &AM)
{
    errs() << "#### MODULE NAME: " << M.getName() << "\n";
    unsigned int FunctCount = 0;
    for (Function &F : M)
    {
      FunctCount += std::distance(F.begin(), F.end());
    }

    llvm::outs() << "#### Number of Functions in " 
                << M.getName() << " is : "
                << FunctCount << "\n\n";

    for (Function &F : M)
    {
        errs() << " ### FUNCTION NAME: " << F.getName() << "\n";
        errs() << " ### NUM. OF ARGUMENTS: " << F.arg_size() << "\n";
        errs() << " ### RETRUN TYPE: " << *(F.getReturnType()) << "\n";

        unsigned int BbCount = 0;
        unsigned int InstrCount = 0;
        for (BasicBlock &Bblk : F)
        {
            ++BbCount;
            InstrCount += std::distance(Bblk.begin(), Bblk.end());
        }

        errs() << " ### NUM. OF BASIC BLOCKS: " << BbCount << "\n";
        errs() << " ### NUM. OF INSTRUCTIONS: " << InstrCount << "\n\n";
    }

    return PreservedAnalyses::all(); // run on all modules
}

bool HookModulePM(StringRef Name, ModulePassManager &ModulePM, ArrayRef<PassBuilder::PipelineElement>)
{
  if (Name == "functioninfo") // command line flag to trigger the pass
  {
    ModulePM.addPass(FunctionsInfoPass());
    return true;
  }
  return false;
}

void HookPB(PassBuilder &PB) {
  PB.registerPipelineParsingCallback(HookModulePM);
}

// Here is were we HOOK the pass we create into LLVM as a Plugin (this can lamba-ed)
llvm::PassPluginLibraryInfo getFunctionInfoPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Info on all Functions", LLVM_VERSION_STRING, HookPB};
}

// This is LLVM's core interface for pass plugins.
// With this, opt will load our plugin is we use the flag '-passes=functioninfo'
// IT is the PUBLIC entry
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getFunctionInfoPassPluginInfo();
}