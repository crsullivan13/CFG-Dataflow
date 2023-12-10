#include "driver.hpp"
#include "cfg.hpp"

#include <fstream>

#include "parser.hpp"

Driver::Driver() {
    mInFileName = "\0";
    mOutDirName = "out";
    mShouldDoDataFlow = false;
    mShouldOutputGraph = false;
}

Driver::Driver(const char* inFileName, const char* outDirName, bool shouldOutputGraph, bool shouldDoDataflow) {
    mInFileName = inFileName;
    mOutDirName = outDirName;
    mShouldOutputGraph = shouldOutputGraph;
    mShouldDoDataFlow = shouldDoDataflow;
}

void Driver::run() {
    std::cout << "Running...\n"; //TODO: make this blocked by debug flag

    std::ifstream inFile(mInFileName);
    if ( !inFile.is_open() ) {
        std::cerr << "Failed to open input file\n";
    } else {
        std::string currLine;
        Instruction* tempInstr;
        CFG* tempCfg = nullptr;
        Bbl* tempBbl = nullptr;

        Parser myParse{};
        while ( std::getline(inFile, currLine) ) {
            tempInstr = myParse.parseLine(currLine, tempCfg ? tempCfg->getBblCount() : 0);

            //tempInstr->operate(cfg, bbl, globList);
            //if is define -> start new CFG
            if ( tempInstr->getType() == InstructionType::DEFINE ) {
                tempCfg = new CFG(tempInstr->getFuncName());
                tempBbl = new Bbl(0);
                tempBbl->addInstruction(*tempInstr);
            } else if ( tempInstr->getType() == InstructionType::CLOSING_BRACKET ) {
                tempCfg->insertBlock(*tempBbl);
                tempCfg->outputDigraph(mOutDirName);
            }
            //if global, add to glob list
            //if term, break block, set didBreak, extract destination(s), add Bbl to graph
            //if didBreak is set, start new Bbl
            //otherwise just add instruction to Bbl list
            //if } -> end CFG, add last Bbl to graph
        }

        inFile.close();
    }
}