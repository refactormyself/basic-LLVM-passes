#include "Passes.hpp"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Module.h"


#define DEBUG_TYPE "countmemop" // command line flag to trigger debug for the pass

STATISTIC(MemOpCount, "The # of Memory Operations found.");

using namespace passes;
using namespace llvm;

PreservedAnalyses MemoryOpCountPass::run(Function &Funct, FunctionAnalysisManager &AM)
{
    errs() << "#### FUNCTION NAME: " << Funct.getName() << "\n";
    unsigned int MemOpCount = 0;
    for (BasicBlock &Bblk : Funct)
    {
      for (Instruction &Inst : Bblk)
      {
        auto opcode = Inst.getOpcode();
        if (opcode == Instruction::Alloca ||
            opcode == Instruction::Load ||
            opcode == Instruction::Store ||
            opcode == Instruction::Fence ||
            opcode == Instruction::AtomicCmpXchg ||
            opcode == Instruction::AtomicRMW ||
            opcode == Instruction::GetElementPtr)
        {
          ++MemOpCount;
        }
      }
    }

    llvm::outs() << "#### Number of Memory Operations in " 
                << Funct.getName() << " is : "
                << MemOpCount << "\n\n";

    return PreservedAnalyses::all(); // run on all modules
}

llvm::PassPluginLibraryInfo getCountMemOpPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Count Memory Operations", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name,
                   FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "countmemop") {
                    FPM.addPass(MemoryOpCountPass());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is LLVM's core interface for pass plugins.
// With this, opt will load our plugin is we use the flag '-passes=countmemop'
// IT is the PUBLIC entry
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getCountMemOpPassPluginInfo();
}