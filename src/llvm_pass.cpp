#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include <map>
#include <fstream>
#include <cstdlib>

using namespace llvm;

namespace {
  struct CountPass : public ModulePass {
    static char ID;
    CountPass() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
      unsigned int functions = 0;
      unsigned int blocks = 0;
      std::map<unsigned, unsigned> histogram;

      for (Function &F : M) {
        if (!F.isDeclaration()) {
          functions ++;
          for (BasicBlock &BB : F) {
            blocks ++;
            unsigned instCount = BB.size();
            histogram[instCount]++;
          }
        }
      }

      errs() << "The program has " << functions << " and " << blocks << " blocks\n";

      errs() << "\nBasic Block Instruction Histogram:\n";
      for (const auto &entry : histogram) {
        errs() << entry.first << ": " << entry.second << "\n";
      }

      /* Added GnuPlot code via the help of Generative AI */
      std::ofstream dataFile("histogram_data.txt");
      for (const auto &entry : histogram) {
        dataFile << entry.first << " " << entry.second << "\n";
      }
      dataFile.close();

      // Generate GnuPlot script
      std::ofstream gnuplotScript("histogram.gnuplot");
      gnuplotScript << "set terminal pdf\n";
      gnuplotScript << "set output 'histogram.pdf'\n";
      gnuplotScript << "set style fill solid\n";
      gnuplotScript << "set boxwidth 0.5\n";
      gnuplotScript << "set xlabel 'Number of Instructions'\n";
      gnuplotScript << "set ylabel 'Frequency'\n";
      gnuplotScript << "set title 'Basic Block Instruction Histogram'\n";
      gnuplotScript << "plot 'histogram_data.txt' with boxes notitle\n";
      gnuplotScript.close();

      // Execute GnuPlot
      int result = system("gnuplot histogram.gnuplot");
      if (result == 0) {
        errs() << "\nHistogram PDF generated: histogram.pdf\n";
      } else {
        errs() << "\nWarning: Failed to generate PDF. Make sure gnuplot is installed.\n";
      }

      return false;
    }
  };
}

char CountPass::ID = 0;
static RegisterPass<CountPass> X("countpass", "Count Functions and Blocks pass");