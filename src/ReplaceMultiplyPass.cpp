#include "Passes.hpp"

#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#define DEBUG_TYPE "replace-multiply"

STATISTIC(ReplaceCount, "The # of substituted instructions");

using namespace replacemultiplypass;
using namespace llvm;

bool RemoveSubtraction(Function &Funct)
{
    bool Changed = false;

    for (auto &Bblock : Funct)
    {
        for (auto Inst = Bblock.begin(), IE = Bblock.end(); Inst != IE; ++Inst)
        {
            // Insert at the point where the instruction `op` appears.
            auto *Op = dyn_cast<BinaryOperator>(Inst);
            if (!Op)
                continue;

            IRBuilder<> builder(Op);
            Instruction *NewInst = nullptr;

            // we want to (A * B) ===> (A + A + A + .... + A)

            if (Op->getOpcode() == Instruction::Mul)
            {
                auto RHS = Op->getOperand(1);
                auto NegatedRHS = builder.CreateFNeg(RHS);  // negate the RHS

                // create a new instruction iin the form A + (-B)
                NewInst = BinaryOperator::CreateFAdd(Op->getOperand(0), NegatedRHS, "my-op");
            }
            
            if (Op->getOpcode() == Instruction::Sub)
            {
                auto floatType = Type::getFloatTy(Funct.getContext());
                auto RHS = builder.CreateUIToFP(Op->getOperand(1), floatType);
                auto NegatedRHS = builder.CreateFNeg(RHS);  // negate the RHS
                RHS = builder.CreateFPToUI(NegatedRHS, Op->getOperand(1)->getType()); // convert back

                // create a new instruction iin the form A + (-B)
                NewInst = BinaryOperator::CreateAdd(Op->getOperand(0), RHS, "my-op");
            }

            if (NewInst)
            {
                LLVM_DEBUG(dbgs() << "###  " << *Op << " ===> " << *NewInst << "\n");
                ReplaceInstWithInst(Bblock.getInstList(), Inst, NewInst);
                Changed = true;
                ++ReplaceCount;
            }
        }
    }
    return Changed;
}

PreservedAnalyses ReplaceMultiplyPass::run(Function &Funct,
                                           FunctionAnalysisManager &AM)
{
    bool Changed = RemoveSubtraction(Funct);
    return (Changed ? llvm::PreservedAnalyses::none()
                    : llvm::PreservedAnalyses::all());
}

llvm::PassPluginLibraryInfo getRemoveSubstractionPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "Remove Substraction Operation", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name,
                       FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "replace-multiply")
                        {
                            FPM.addPass(ReplaceMultiplyPass());
                            return true;
                        }
                        return false;
                    });
            }};
}

// register the  pass
// command line, i.e. via '-passes=replace-multiply'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getRemoveSubstractionPluginInfo();
}
