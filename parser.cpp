#include "parser.hpp"

Instruction* Parser::parseLine(std::string line, int num) {
    Instruction* instr;
    
    size_t index = line.find_first_not_of(" \t");
    if ( index == std::string::npos ) {
        return new Instruction{};
    }
    std::string trimmed = line.substr(index, line.size());

    switch ( trimmed[0] )
    {
    case 'd': {
        std::string name = getFuncName(trimmed);
        instr = new Define{InstructionType::DEFINE, name, num};
        }
        break;
    case 'r': {
        std::string retVal = getRetVal(trimmed);
        instr = new Ret{InstructionType::RET, retVal, num};
        }
        break;
    case '%': {
        instr = parseAssign(trimmed, num);
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

Instruction* Parser::parseAssign(std::string line, int num) {
    Instruction* instr;

    size_t index = line.find('=') + 2;

    switch ( line[index] )
    {
    case 'c': {
        std::vector<std::string> params = getParams(line);
        instr = new Call{InstructionType::CALL, params, num};
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

std::string Parser::getRetVal(std::string line) {
    size_t index = line.find('%');
    std::string retVal;

    for (size_t i = index+1; i < line.size(); i++ ) {
        retVal += line[i];
    }

    return retVal;
}

std::vector<std::string> Parser::getParams(std::string line) {
    size_t index = line.find('(');
    std::string paramStr = line.substr(index, line.size());

    std::vector<std::string> params{};

    for ( size_t i = 0; i < paramStr.size(); i++ ) {
        if ( paramStr[i] == '%' ) {
            std::string temp;
            size_t j = 0;
            for ( j = i+1; paramStr[j] != ',' && paramStr[j] != ')'; j++) {
                temp += paramStr[j];
            }
            std::cout << temp << "\n";
            params.push_back(temp);
            i = j;
        }
    }

    return params;
}