#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>

class Driver {
public:
    Driver();
    Driver(const char* inFileName, const char* outDirName, bool shouldOutputGraph, bool shouldDoDataflow);

    void run();

private:
    const char* mInFileName;
    const char* mOutDirName;
    bool mShouldOutputGraph;
    bool mShouldDoDataFlow;

};

#endif