#ifndef BBL_H
#define BBL_H

#include "instruction.hpp"
#include <vector>

class Bbl {
public:
    Bbl(int bblNumber, std::vector<int> successors = {}, std::vector<Instruction> instructions = {}) : mBblNumber(bblNumber), mSuccessors(successors), mInstructions(instructions) {}

private:
    int mBblNumber;
    std::vector<int> mSuccessors;
    std::vector<Instruction> mInstructions;

};

#endif