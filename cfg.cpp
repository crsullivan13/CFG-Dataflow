#include "cfg.hpp"

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