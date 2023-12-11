#include "parser.hpp"

#include <sstream>

Instruction* Parser::parseLine(std::string line, int num) {
    Instruction* instr;
    
    size_t index = line.find_first_not_of(" \t");
    if ( index == std::string::npos ) {
        return new Instruction{};
    }
    std::string trimmed = line.substr(index, line.size());

    if ( trimmed.find(':') != std::string::npos ) {
        instr = parseLabel(trimmed, num);
        return instr;
    }

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
    case 's': {
        std::vector<std::string> args = getStoreArgs(trimmed);
        instr = new Store{InstructionType::STORE, args[1], args[0], num};
        }
        break;
    case 'b': {
        std::vector<std::string> dests = getBranchDests(trimmed);
        instr = new Br{InstructionType::BR, dests[0], dests[1], num};
        }
        break;
    case 'c': {
        std::vector<std::string> params = getParams(trimmed);
        std::string name = getFuncName(trimmed);
        instr = new Call{InstructionType::CALL, name, params, "", num};
        }
        break;
    case '@': {
        std::vector<std::string> args = parseGlob(trimmed);
        instr = new Global{InstructionType::GLOBAL, args[0], args[1]};
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
        std::string name = getFuncName(line);
        std::string dest = getAllocDest(line); //spahget1
        instr = new Call{InstructionType::CALL, name, params, dest, num};
        }
        break;
    case 'a': {
            if ( line[index+1] == 'd' ) {
                std::vector<std::string> args = getArithArgs(line);
                instr = new Arithmetic{InstructionType::ADD, args[0], args[1], args[2], num};
            } else if ( line[index+1] == 'l' ) {
                std::string dest = getAllocDest(line);
                instr = new Alloca{InstructionType::ALLOCA, dest, num};
            }
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
        //std::cout << dest << "\n";
        instr = new Icmp{InstructionType::ICMP, dest, num};
        }
        break;
    case 'l': {
        std::vector<std::string> args = getLoadArgs(line);
        instr = new Load{InstructionType::LOAD, args[1], args[0], num};
        }
        break;
    default: {
        instr = new Instruction{};
        }
        break;
    }

    return instr;
}


std::vector<std::string> Parser::parseGlob(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> args;

    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    args.push_back(tokens[0].substr(1, tokens[0].size()));

    if ( tokens[4][0] == '%' ) {
        args.push_back(tokens[4].substr(1, tokens[4].size()-2));
    } else {
        args.push_back(tokens[4].substr(0, tokens[4].size()-1));
    }
    
    return args;
}

Instruction* Parser::parseLabel(std::string line, int num) {
    Instruction* instr;
    std::string temp;

    for ( char c : line ) {
        if ( c != ':' ) {
            temp += c;
        }
    }

    instr = new LabelInstr{InstructionType::LABEL, temp, num};
    return instr;
}


std::vector<std::string> Parser::getBranchDests(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> dests;

    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    if ( tokens.size() == 3 ) {
        dests.push_back(tokens[2].substr(1, tokens[2].size()));
        dests.push_back("");
        //std::cout << dests[0] << "\n";
    } else if ( tokens.size() == 7 ) {
        dests.push_back(tokens[4].substr(1, tokens[4].size()-2));
        dests.push_back(tokens[6].substr(1, tokens[6].size()));
        //std::cout << dests[0] << " " << dests[1] << "\n";
    }

    return dests;
}

std::string Parser::getAllocDest(std::string line) {
    std::string dest;

    for ( size_t i = 1; line[i] != ' '; i++ ) {
        dest += line[i];
    }

    //std::cout << dest << "\n";
    return dest; 
}

std::vector<std::string> Parser::getStoreArgs(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> args;

    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    if ( tokens[2][0] == '%' ) {
        tokens[2] = tokens[2].substr(1, tokens[2].size()-2);
    } else {
        tokens[2] = tokens[2].substr(0, tokens[2].size()-1);
    }
    args.push_back(tokens[2]);
    args.push_back(tokens[4].substr(1, tokens[4].size()-2));

    //std::cout << args[0] << " " << args[1] <<"\n";
    return args;
}

std::vector<std::string> Parser::getLoadArgs(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> args;

    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    args.push_back(tokens[0].substr(1, tokens[0].size()));
    args.push_back(tokens[5].substr(1, tokens[5].size()-2));

    //std::cout << args[0] << " " << args[1] << "\n";
    return args;
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

    for (size_t i = index+1; line[i] != '(' && line[i] != ' '; i++) {
        name += line[i];
    }

    //std::cout << name << "\n";
    return name;
}

std::string Parser::getRetVal(std::string line) {
    std::vector<std::string> tokens;
    std::vector<std::string> args;
    std::string temp;

    std::stringstream stream(line);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    temp = tokens[2][0] == '%' ? tokens[2].substr(1, tokens[2].size()) : tokens[2];

    //std::cout << temp << "\n";
    return temp;
}

std::vector<std::string> Parser::getParams(std::string line) {
    size_t index = line.find('(');
    std::string paramStr = line.substr(index, line.size());

    std::vector<std::string> tokens;
    std::vector<std::string> params{};
    std::string temp;

    std::stringstream stream(paramStr);

    while ( std::getline(stream, temp, ' ') ) {
        tokens.push_back(temp);
    }

    if ( tokens.size() > 0 ) {
        for ( size_t i = 1; i < tokens.size(); i+=2 ) {
            if ( tokens[i][0] == '%' ) {
                params.push_back(tokens[i].substr(1, tokens[i].size()-2));
            } else {
                params.push_back(tokens[i].substr(0, tokens[i].size()-1));
            }
        }
    }

    if ( params.size() != 0 ) {
        for ( size_t i = 0; i < params.size(); i++ ) {
            //std::cout << params[i] << " ";
        }
        //std::cout << "\n";
    } else {
        //std::cout << "No args\n";
    }

    return params;
}