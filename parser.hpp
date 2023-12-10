#ifndef PARSER_H
#define PARSER_H

#include "instruction.hpp"

#include <iostream>

class Parser {
public:
    Parser(){};

    Instruction* parseLine(std::string line, int num);
private:
    std::string getFuncName(std::string line);

};

#endif