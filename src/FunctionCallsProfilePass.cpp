#include "Passes.hpp"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Module.h"
#include <map>


#define DEBUG_TYPE "functioncalls" // command line flag to trigger debug for the pass

// STATISTIC(InstCount, "The # of instruction used.");

using namespace functioncallspass;
using namespace llvm;

PreservedAnalyses FunctionCallsProfilePass::run(Module &M, ModuleAnalysisManager &AM)
{
    unsigned int cntIntrinsic = 0, cntFunc = 0, cntInDirectCalls = 0, cntDirectCalls = 0;
    std::map<StringRef, int> AllFunCalls;
    for (Function &Func : M)
    {
        ++cntFunc;
        unsigned int cntFuncCalls = 0;
        if (Func.isIntrinsic()) // function HasLLVMReservedName; don't profile llvm code
        {
            cntIntrinsic++;
            continue;
        }

        for (BasicBlock &Bblk : Func)
        {
            for (Instruction &Instr : Bblk)
            {
                // is this a function call ?
                // if (CallInst *callInst = dyn_cast<CallInst>(&Instr))
                if (CallBase *callInst = dyn_cast<CallBase>(&Instr))
                { 
                    if (Function *calledFunction = callInst->getCalledFunction())
                    {
                        ++cntFuncCalls;
                        auto funcName = calledFunction->getName();
                        if (AllFunCalls.count(funcName))
                            ++AllFunCalls[funcName];
                        else
                            AllFunCalls[funcName] = 1;

                        if (!callInst->isIndirectCall())
                        {
                            ++cntDirectCalls;
                            continue;
                        }

                        ++cntInDirectCalls;
                        // Lets try to get debug data
                        if (MDNode *dbgNode = Instr.getMetadata("dbg"))
                        {
                            DILocation *Loc = cast<DILocation>(dbgNode);
                            errs() << "/*-*-*/ Indirect call to " << funcName 
                                   << " in  file " << Loc->getFilename() 
                                   << " at  line " << Loc->getLine() << "\n";
                        }
                    }
                }
            }
        }
        llvm::outs() << "#### Number of Function calls inside the function " 
                     << Func.getName() << " is " << cntFuncCalls << "\n";
    }

    llvm::outs() << "#### The module " << M.getName() << " contains " << cntFunc << "functions.\n";
    llvm::outs() << "#### Total number of *Intrinsic* functions calls is " << cntIntrinsic << ".\n";

    llvm::outs() << "#### Total number of functions that were called is " << AllFunCalls.size() << "\n";
    llvm::outs() << "#### " << cntDirectCalls << " Direct Calls and " << cntInDirectCalls << " Indirect Calls.\n";

    // for (const auto &[inst, count] : AllFunCalls) { // :( not until C++17 only ugly syntax make it first
    for (std::pair<StringRef, int> elem : AllFunCalls)
    {
        llvm::outs() << "Function `" << elem.first << "` was called "
                     << elem.second << " times.\n";
    }
    return PreservedAnalyses::all(); // run on all modules
}

llvm::PassPluginLibraryInfo getFunctionCallsProfilePassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Profile all Operation", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name,
                   ModulePassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "functioncalls") {
                    FPM.addPass(FunctionCallsProfilePass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getFunctionCallsProfilePassPluginInfo();
}