#include "parser.hpp"

Instruction* Parser::parseLine(std::string line, int num) {
    Instruction* instr;
    
    switch ( line[0] )
    {
    case 'd': {
        std::string name = getFuncName(line);
        instr = new Define{InstructionType::DEFINE, name, num};
        }
        break;
    case '}': {
        instr = new Instruction{InstructionType::CLOSING_BRACKET};
        }
        break;
    default: {
        instr = new Instruction{};
    }
        break;
    }

    return instr;
}

std::string Parser::getFuncName(std::string line) {
    size_t index = line.find('@');
    std::string name;

    for (size_t i = index+1; line[i] != '('; i++) {
        name += line[i];
    }

    return name;
}