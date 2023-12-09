#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <vector>

enum class InstructionType {
    ALLOCA,
    LOAD,
    STORE,
    RET,
    ICMP,
    BR,
    ADD,
    SUB,
    DIV,
    MUL,
    CALL,
    DEFINE,

    NONE
};

class Instruction {
public:
    Instruction();
    Instruction(InstructionType type, int bblNumber);

protected:
    InstructionType mType = InstructionType::NONE;
    bool mIsTerm = false;
    bool mIsLead = false;
    int mBblNumber = 0;
};

class Alloca : Instruction {
public:

private:
    bool mIsTerm = false;
};

class Load : Instruction {
public:
    Load(InstructionType type, std::string address, std::string dest, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mAddress;
    std::string mDest;
    int mBblNumber;
};

class Store : Instruction {
public:
    Store(InstructionType type, std::string address, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mAddress;
    int mVal;
    int mBblNumber;
};

class Ret : Instruction {
public:
    Ret(InstructionType type, std::string op1, int bblNumber);

private:
    bool mIsTerm = true;
    std::string mOp1;
    int mBblNumber;
};

class Icmp : Instruction {
public:
    Icmp(InstructionType type, std::string dest, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mDest;
    int mBblNumber;
};

class Br : Instruction {
public:
    Br(InstructionType type, std::string target1, std::string target2, int bblNumber);

private:
    bool mIsTerm = true;
    std::string mTarget1;
    std::string mTarget2;
    int mBblNumber;
};

class Arithmetic : Instruction {
public:
    Arithmetic(InstructionType type, std::string dest, std::string op1, std::string op2, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mDest;
    std::string mOp1;
    std::string mOp2;
    int mBblNumber;
};

class Call : Instruction {
public:
    Call(InstructionType type, std::vector<std::string> params, int bblNumber);

private:
    std::vector<std::string> mParams;
    bool mIsTerm = true;
    int mBblNumber;
};

class Define : Instruction {
public:
    Define(InstructionType type, std::string funcName, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mFuncName;
    bool mIsLead = true;
    int mBblNumber;
};

#endif