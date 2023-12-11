#include "parser.hpp"

#include <sstream>

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
    case 'a': {
        std::vector<std::string> args = getArithArgs(line);
        instr = new Arithmetic{InstructionType::ADD, args[0], args[1], args[2], num};
        }
        break;
    case 'm': {
        std::vector<std::string> args = getArithArgs(line);
        instr = new Arithmetic{InstructionType::MUL, args[0], args[1], args[2], num};
        }
        break;
    case 's': {
            if ( line[index+1] == 'u' ) {
                std::vector<std::string> args = getArithArgs(line);
                instr = new Arithmetic{InstructionType::SUB, args[0], args[1], args[2], num};
            } else if ( line[index+1] == 'd' ) {
                std::vector<std::string> args = getArithArgs(line);
                instr = new Arithmetic{InstructionType::DIV, args[0], args[1], args[2], num};
            }
        }
        break;
    case 'u': {
        std::vector<std::string> args = getArithArgs(line);
        instr = new Arithmetic{InstructionType::DIV, args[0], args[1], args[2], num};
        }
        break;
    case 'i': {
        std::string dest = getDest(line);
        std::cout << dest << "\n";
        instr = new Icmp{InstructionType::ICMP, dest, num};
        }
        break;
    default: {
        instr = new Instruction{};
        }
        break;
    }

    return instr;
}

std::string Parser::getDest(std::string line) {
    std::vector<std::string> tokens;
    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);        
    }

    return tokens[0].substr(1, tokens[0].size());
}

std::vector<std::string> Parser::getArithArgs(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> args;
    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    args.push_back(tokens[0].substr(1, tokens[0].size()));

    if ( tokens[4][0] == '%' ) {
        tokens[4] = tokens[4].substr(1, tokens[4].size()-2);
    } else {
        tokens[4] = tokens[4].substr(0, tokens[4].size()-1);
    }
    args.push_back(tokens[4]);

    if ( tokens[5][0] == '%' ) {
        tokens[5] = tokens[5].substr(1, tokens[5].size());
    }
    args.push_back(tokens[5]);

    //std::cout << args[0] << " " << args[1] << " " << args[2] << " " << "\n";
    return args;
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
    if ( index == std::string::npos ) {
        return "";
    }
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