#ifndef CFG_H
#define CFG_H

#include <iostream>
#include <map>

#include "bbl.hpp"

class CFG {
public:
    CFG(std::string funcName) : mFuncName(funcName) {};

    bool flowAnalysis();

    void insertEdge(int sourceId, int successorId);
    void insertBlock(Bbl* block);

    void printGraph();
    void outputDigraph(std::string outDir);

    int getBblCount() { return mBblCount; };
    int incBblCount() { mBblCount+=1; return mBblCount; };

    void addGlobals(std::vector<Instruction> globs) { globList = globs; };

    void addLabel(std::string name, int num) { mLabels.insert({name, num}); };
    int findLabel(std::string name) {
        if ( mLabels.find(name) != mLabels.end() ) {
            return mLabels[name];
        } else {
            return -1;
        }
    };

private:
    std::vector<Instruction> globList;
    std::string mFuncName;
    std::vector<Bbl*> mBlocks = {};
    std::map<std::string, int> mLabels = {};
    int mBblCount = 0;
    
};

#endif