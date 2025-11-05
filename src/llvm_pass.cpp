#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace {
  struct CountPass : public ModulePass {
    static char ID;
    CountPass() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
      unsigned int functions = 0;
      unsigned int blocks = 0;
      for (Function &F : M) {
        if (!F.isDeclaration()) {
          functions ++;
          for (BasicBlock &BB : F) {
            blocks ++;
          }
        }
      }
      errs() << "The program has " << functions << " and " << blocks << " blocks\n";
      return false;
    }
  };
}

char CountPass::ID = 0;
static RegisterPass<CountPass> X("countpass", "Count Functions and Blocks pass");