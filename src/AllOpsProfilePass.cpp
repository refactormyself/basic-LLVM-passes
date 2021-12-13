#include "Passes.hpp"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Module.h"
#include <map>


#define DEBUG_TYPE "allopsprofile" // command line flag to trigger debug for the pass

// STATISTIC(InstCount, "The # of instruction used.");

using namespace passes;
using namespace llvm;

PreservedAnalyses AllOpsProfilePass::run(Module &M, ModuleAnalysisManager &AM)
{
  std::map<StringRef, int> AllInstr;
  for (Function &Func : M)
  {
    // std::map<StringRef, int> AllInstr;
    for(BasicBlock &Bblk : Func) {
      for(Instruction &Instr : Bblk)
      {          
        auto opName = Instr.getOpcodeName();
        if (AllInstr.count(opName))
          ++AllInstr[opName];
        else
          AllInstr[opName] = 1;
      }
    }
  }

  llvm::outs() << "#### Number of Instructions used is " << AllInstr.size() << "\n";
  // for (const auto &[inst, count] : AllInstr) { // :( not until C++17 only ugly syntax make it first
  for (std::pair<StringRef, int> elem : AllInstr) {
    llvm::outs() << elem.second << " calls to the instruction '"
                 << (elem.first.empty() ? "Unknown Op" : elem.first) << "'\n";
  }
  return PreservedAnalyses::all(); // run on all modules
}

llvm::PassPluginLibraryInfo getAllOpsProfilePassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Profile all Operation", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name,
                   ModulePassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "allopsprofile") {
                    FPM.addPass(AllOpsProfilePass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getAllOpsProfilePassPluginInfo();
}