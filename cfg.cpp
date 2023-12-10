#include "cfg.hpp"

#include <fstream>

void CFG::insertEdge(int successorId, int sourceId) {
    mBlocks[successorId].addSuccessor(sourceId);
}

void CFG::insertBlock(Bbl block) {
    mBlocks.push_back(block);
}

void CFG::printGraph() {
    for ( Bbl block : mBlocks ) {
        std::cout << "Block " << block.getBblNumber() << " -> ";
        for ( int successor : block.getSuccesors() ) {
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
        for ( Bbl block : mBlocks ) {
            std::string nodeName = "Node" + std::to_string(block.getBblNumber());
            outFile << "\t" << nodeName << " [shape=record,label=\"\"]\n";
            for ( int successor : block.getSuccesors() ) {
                outFile << "\t" << nodeName << " -> " << "Node" << successor << "[label=" << successor <<"];\n";
            }
        }
        outFile << "}\n";

        outFile.close();
    } else {
        std::cout << "Failed to open " << outPath << " no graph output\n";
    }
}