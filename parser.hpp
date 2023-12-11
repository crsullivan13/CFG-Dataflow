#ifndef PARSER_H
#define PARSER_H

#include "instruction.hpp"

#include <iostream>

class Parser {
public:
    Parser(){};

    Instruction* parseLine(std::string line, int num);
private:
    Instruction* parseAssign(std::string line, int num);
    std::string getFuncName(std::string line);
    std::string getRetVal(std::string line);
    std::string getDest(std::string line);
    std::vector<std::string> getParams(std::string line);
    std::vector<std::string> getArithArgs(std::string line);

};

#endif