#ifndef CFG_H
#define CFG_H

#include <iostream>
#include <map>

#include "bbl.hpp"

struct Label {
    std::string name;
    int bblNumber;
};

class CFG {
public:
    CFG(std::string funcName) : mFuncName(funcName) {};

    void insertEdge(int sourceId, int successorId);
    void insertBlock(Bbl block);

    void printGraph();
    void outputDigraph(std::string outDir);

    int getBblCount() { return mBblCount; };
    int incBblCount() { return ++mBblCount; };

private:
    std::string mFuncName;
    std::vector<Bbl> mBlocks = {};
    std::map<std::string, int> mLabels = {};
    int mBblCount = 0;
    
};

#endif