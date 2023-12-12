#include "cfg.hpp"

#include <fstream>

CFG::~CFG() {
    for ( auto& block : mBlocks ) {
        delete block;
    }
}

bool CFG::analyzeBbl(Bbl* block) {
    bool didLeak = false;
    for ( auto instr : block->getInstructions() ) {
        if ( didLeak ) { break; };

        InstructionType tempType = instr->getType();
        if ( tempType != InstructionType::DEFINE ) {
            if ( tempType == InstructionType::ADD || tempType == InstructionType::DIV || tempType == InstructionType::MUL || tempType == InstructionType::SUB ) {
                std::string op1 = instr->getTgt1();
                std::string op2 = instr->getTgt2();

                DataState temp = block->mInSet.getFact(op1);
                if ( temp != DataState::NONE ) { //If its a literal it won't be in the fact set
                    block->mInSet.updateSet(instr->getDest(), temp);
                } else {
                    block->mInSet.updateSet(instr->getDest(), DataState::NOT_SECRET);
                }

                temp = block->mInSet.getFact(op2);
                if ( temp != DataState::NONE ) {
                    //temp = block.mInSet.updateSet(op2, temp);
                    block->mInSet.updateSet(instr->getDest(), temp);
                }
            } else if ( tempType == InstructionType::CALL ) {
                std::vector<std::string> params = instr->getParams();
                std::string name = instr->getName();
                std::string dest = instr->getDest();

                for ( std::string str : params ) {
                    DataState temp = block->mInSet.getFact(str);
                    if ( temp == DataState::SECRET ) { didLeak = true; break; };
                }

                if ( name == "SOURCE" && dest != "" ) {
                    block->mInSet.updateSet(dest, DataState::SECRET);
                }

                block->mOutSet.mergeSets(block->mInSet);
                std::vector<int> temp = block->getSuccesors();

                for ( auto innerBlock : mBlocks ) {
                    if ( temp[0] == innerBlock->getBblNumber() ) {
                        innerBlock->mInSet.mergeSets(block->mOutSet);
                        break;
                    }
                }
            } else if ( tempType == InstructionType::RET ) {
                std::string op1 = instr->getTgt1();

                if ( block->mInSet.getFact(op1) == DataState::SECRET ) {
                    didLeak = true;
                }
            } else if ( tempType == InstructionType::ALLOCA ) {
                block->mInSet.updateSet(instr->getDest(), DataState::NOT_SECRET);
            } else if ( tempType == InstructionType::ICMP ) {
                std::string dest = instr->getDest();
                std::string op1 = instr->getTgt1();
                std::string op2 = instr->getTgt2();

                DataState temp = block->mInSet.getFact(op1);
                if ( temp != DataState::NONE ) {
                    block->mInSet.updateSet(instr->getDest(), temp);   
                } else {
                    block->mInSet.updateSet(instr->getDest(), DataState::NOT_SECRET);
                }

                temp = block->mInSet.getFact(op2);
                if ( temp != DataState::NONE ) {
                    block->mInSet.updateSet(instr->getDest(), temp);   
                }
            } else if ( tempType == InstructionType::BR ) {
                block->mOutSet.mergeSets(block->mInSet);
                std::vector<int> temp = block->getSuccesors();

                for ( auto succ : temp ) {
                    for (auto innerBlock : mBlocks ) { //realizing too late that mBlocks should probably be a set, \O/
                        if ( succ == innerBlock->getBblNumber() ) {
                            innerBlock->mInSet.mergeSets(block->mOutSet);
                            analyzeBbl(innerBlock);
                            break;
                        }
                    }
                }
            } else if ( tempType == InstructionType::LOAD ) {
                std::string name = instr->getName();
                std::string dest = instr->getDest();

                block->mInSet.updateSet(dest, mMemory.getFact(name));
            } else if ( tempType == InstructionType::STORE ) {
                std::string name = instr->getName();
                std::string value = instr->getValue();

                DataState temp = block->mInSet.getFact(value);
                if ( temp == DataState::SECRET ) {
                    mMemory.updateSet(name, temp);
                } else {
                    mMemory.updateSet(name, DataState::NOT_SECRET);
                }
            }
        }
    }
    return didLeak;
}

bool CFG::flowAnalysis() {
    bool didLeak = false;

    for ( auto glob : globList ) {
       mBlocks[0]->mInSet.updateSet(glob.getName(), DataState::NOT_SECRET); 
    }

    for ( Bbl* block : mBlocks ) {
        didLeak = analyzeBbl(block);

        if ( didLeak ) {
            break;
        }
    }

    return didLeak;
}

void CFG::insertEdge(int sourceId, int successorId) {
    for ( Bbl* block : mBlocks ) {
        if ( block->getBblNumber() == sourceId ) {
            block->addSuccessor(successorId);
            break;
        }
    }
}

void CFG::insertBlock(Bbl* block) {
    mBlocks.push_back(block);
}

void CFG::printGraph() {
    for ( Bbl* block : mBlocks ) {
        std::cout << "Block " << block->getBblNumber() << " -> ";
        for ( int successor : block->getSuccesors() ) {
            std::cout << successor << ",";
        }
        std::cout << "\n";
    }
}

void CFG::outputDigraph(std::string outDir) {
    std::string outPath = outDir + "/" + mFuncName + ".dot";
    std::ofstream outFile(outPath);

    if ( outFile.is_open() ) {
        outFile << "digraph {\n";
        for ( Bbl* block : mBlocks ) {
            int successorCount = 1;
            std::string nodeName = "Node" + std::to_string(block->getBblNumber());
            outFile << "\t" << nodeName << " [shape=record,label=\"\"]\n";
            for ( int successor : block->getSuccesors() ) {
                outFile << "\t" << nodeName << " -> " << "Node" << successor << " [label=" << successorCount <<"];\n";
                successorCount += 1;
            }
        }
        outFile << "}";

        outFile.close();
    } else {
        std::cout << "Failed to open " << outPath << " no graph output\n";
    }
}