#include "Passes.hpp"

#include "llvm/IR/Verifier.h"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#define DEBUG_TYPE "wrongreplace"

STATISTIC(ReplaceCount, "The # of replaced instructions");

using namespace wrongreplacepass;
using namespace llvm;

bool InfectWithMultiply(Function &Funct){
  bool Changed = false;

  for (auto &Bblk : Funct)
  {
    for (auto &Instr : Bblk)
    {
      if (auto *Op = dyn_cast<BinaryOperator>(&Instr))
      {
        IRBuilder<> builder(Op);
        
        Value *MyMul = builder.CreateMul(Op->getOperand(0), Op->getOperand(1), "mymul");

        // Perhaps we could use 'Op.setOperand()' directly
        // Also the original Instruction, Op is not deleted
        // This is better done with 'ReplaceInstWithInst()'
        for (auto &OpUse : Op->uses())
        {
          User *OpUser = OpUse.getUser(); 
          OpUser->setOperand(OpUse.getOperandNo(), MyMul); // replacement is done here
          LLVM_DEBUG(dbgs() << *Op << " ==> " << *MyMul << "\n");

          Changed = true;
          ++ReplaceCount;
        }
      }
    }
  }

 return Changed;
}

PreservedAnalyses WrongOpReplacePass::run(Function &Funct,
                                      FunctionAnalysisManager &AM)
{
    bool Changed = InfectWithMultiply(Funct);
    verifyFunction(Funct, &outs());
    return (Changed ? PreservedAnalyses::none()
                    : PreservedAnalyses::all());
}

llvm::PassPluginLibraryInfo getWrongOpReplacePluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Infect all BinOperations with Multiply",
           LLVM_VERSION_STRING, [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name,
                   FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "wrongreplace") {
                    FPM.addPass(WrongOpReplacePass());
                    return true;
                  }
                  return false;
                });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getWrongOpReplacePluginInfo();
}
