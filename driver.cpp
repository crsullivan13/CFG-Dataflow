#include "driver.hpp"
#include "cfg.hpp"

#include <fstream>

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
        CFG myCfg("main");

        Bbl myBlock(0);
        myCfg.insertBlock(myBlock);
        Bbl myBlock1(1);
        myCfg.insertBlock(myBlock1);
        myCfg.insertEdge(0, 1);
        myCfg.printGraph();

        inFile.close();
    }
}