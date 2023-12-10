#ifndef CFG_H
#define CFG_H

#include <iostream>

#include "bbl.hpp"

class CFG {
public:
    CFG(std::string funcName) : mFuncName(funcName) {};

    void insertEdge(int sourceId, int successorId);
    void insertBlock(Bbl block);

    void printGraph();

private:
    std::string mFuncName;
    std::vector<Bbl> mBlocks;
    
};

#endif