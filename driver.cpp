#include "driver.hpp"

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


}