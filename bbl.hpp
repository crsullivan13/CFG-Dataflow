#ifndef BBL_H
#define BBL_H

#include "instruction.hpp"
#include <vector>

class Bbl {
public:
    //Just learned about these initializer lists, also braced initalization, crazy stuff
    Bbl(int bblNumber, std::vector<int> successors = {}, std::vector<Instruction> instructions = {}) : mBblNumber(bblNumber), mSuccessors(successors), mInstructions(instructions) {}

    void addSuccessor(int id) { mSuccessors.emplace_back(id); };
    const std::vector<int> getSuccesors() { return mSuccessors; };
    void addInstruction(Instruction instruction) { mInstructions.emplace_back(instruction); };
    const std::vector<Instruction> getInstructions() { return mInstructions; };
    const int getBblNumber() { return mBblNumber; }

private:
    int mBblNumber;
    std::vector<int> mSuccessors;
    std::vector<Instruction> mInstructions;

};

#endif