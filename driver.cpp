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
    //std::cout << "Running...\n"; //TODO: make this blocked by debug flag

    std::ifstream inFile(mInFileName);
    if ( !inFile.is_open() ) {
        std::cerr << "Failed to open input file\n";
    } else {
        std::string currLine;
        Instruction* tempInstr;
        CFG* tempCfg = nullptr;
        Bbl* tempBbl = nullptr;
        std::vector<Instruction> globList = {};
        bool didBreak = false;

        Parser myParse{};
        while ( std::getline(inFile, currLine) ) {
            tempInstr = myParse.parseLine(currLine, tempCfg ? tempCfg->getBblCount() : 0);
            InstructionType tempType = tempInstr->getType();

            //tempInstr->operate(cfg, bbl, globList); probably a cleaner way, but I'm hacking for now

            if ( didBreak && tempType == InstructionType::LABEL ) {
                int temp = tempCfg->findLabel(tempInstr->getName());
                if ( temp == -1 ) {
                    temp = tempCfg->incBblCount();
                    tempCfg->addLabel(tempInstr->getName(), temp);
                }
                tempBbl = new Bbl(temp);
                didBreak = false;
            } else if ( didBreak && tempType != InstructionType::NONE ) {
                tempBbl = new Bbl(tempCfg->getBblCount());
            }

            if ( tempType == InstructionType::DEFINE ) {
                tempCfg = new CFG(tempInstr->getName());
                tempBbl = new Bbl(0);
                tempBbl->addInstruction(tempInstr);
                didBreak = false;
            } else if ( tempType == InstructionType::CLOSING_BRACKET ) {
                if ( !didBreak ) {
                    tempCfg->insertBlock(tempBbl);
                    didBreak = false;
                }

                if ( mShouldOutputGraph ) {
                    tempCfg->outputDigraph(mOutDirName);
                }
                tempCfg->addGlobals(globList);
                mCfgs.push_back(*tempCfg);
            } else if ( tempType == InstructionType::BR || tempType == InstructionType::RET || tempType == InstructionType::CALL ) {
                didBreak = true;

                if ( tempType == InstructionType::BR ) {
                    tempBbl->addInstruction(tempInstr);
                    tempCfg->insertBlock(tempBbl);

                    std::string tgt1 = tempInstr->getTgt1();
                    int temp = tempCfg->findLabel(tempInstr->getTgt1());
                    if ( temp == -1 ) {
                        temp = tempCfg->incBblCount();
                        tempCfg->addLabel(tgt1, temp);
                    }
                    tempCfg->insertEdge(tempBbl->getBblNumber(), temp);

                    std::string tgt2 = tempInstr->getTgt2();
                    if ( !tgt2.empty() ) {
                        temp = tempCfg->findLabel(tempInstr->getTgt2());
                        if ( temp == -1 ) {
                            temp = tempCfg->incBblCount();
                            tempCfg->addLabel(tgt2, temp);
                        }
                        tempCfg->insertEdge(tempBbl->getBblNumber(), temp);
                    }
                } else if ( tempType == InstructionType::RET ) {
                    tempBbl->addInstruction(tempInstr);
                    tempCfg->insertBlock(tempBbl);
                } else if ( tempType == InstructionType::CALL ) {
                    tempBbl->addInstruction(tempInstr);
                    tempCfg->insertBlock(tempBbl);
                    tempCfg->insertEdge(tempBbl->getBblNumber(), tempCfg->incBblCount());
                }
            } else if ( tempType == InstructionType::GLOBAL ) {
                globList.push_back(*tempInstr);
            } else if ( tempType != InstructionType::NONE ) {
                didBreak = false;
                tempBbl->addInstruction(tempInstr);
            }
        }

        inFile.close();

        if ( mShouldDoDataFlow ) {
            //Do dataflow analysis
            bool leak = false;
            for ( CFG& graph : mCfgs ) {
                if ( graph.flowAnalysis() ) {
                    leak = true;
                    std::cout << "LEAK\n";
                    break;
                }
            }

            if ( !leak ) {
                std::cout << "NO LEAK\n";
            }
        }
    }
}