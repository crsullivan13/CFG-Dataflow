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
    CLOSING_BRACKET,

    NONE
};

class Instruction {
public:
    Instruction();
    Instruction(InstructionType type, int bblNumber = 0) : mType{type}, mBblNumber{bblNumber} {};

    InstructionType getType() { return mType; };
    virtual std::string getFuncName() { return "NA"; };
    virtual bool isTerm() { return false; };
protected:
    InstructionType mType;
    bool mIsTerm;
    bool mIsLead;
    int mBblNumber;
};

class Alloca : public Instruction {
public:
    Alloca(InstructionType type, std::string dest, int bblNumber) : mType{type}, mDest{dest}, mBblNumber{bblNumber} {};

private:
    Instruction mType;
    std::string mDest;
    bool mIsTerm = false;
    int mBblNumber;
};

class Load : public Instruction {
public:
    Load(InstructionType type, std::string address, std::string dest, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mAddress;
    std::string mDest;
    int mBblNumber;
};

class Store : public Instruction {
public:
    Store(InstructionType type, std::string address, std::string value, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mAddress;
    std::string mVal;
    int mBblNumber;
};

class Ret : public Instruction {
public:
    Ret(InstructionType type, std::string op1, int bblNumber);

private:
    bool mIsTerm = true;
    std::string mOp1;
    int mBblNumber;
};

class Icmp : public Instruction {
public:
    Icmp(InstructionType type, std::string dest, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mDest;
    int mBblNumber;
};

class Br : public Instruction {
public:
    Br(InstructionType type, std::string target1, std::string target2, int bblNumber);

private:
    bool mIsTerm = true;
    std::string mTarget1;
    std::string mTarget2;
    int mBblNumber;
};

class Arithmetic : public Instruction {
public:
    Arithmetic(InstructionType type, std::string dest, std::string op1, std::string op2, int bblNumber);

private:
    bool mIsTerm = false;
    std::string mDest;
    std::string mOp1;
    std::string mOp2;
    int mBblNumber;
};

class Call : public Instruction {
public:
    Call(InstructionType type, std::string funcName, std::vector<std::string> params, int bblNumber);

private:
    std::vector<std::string> mParams;
    std::string mFuncName;
    bool mIsTerm;
    int mBblNumber;
};

class Define : public Instruction {
public:
    Define(InstructionType type, std::string funcName, int bblNumber);

    std::string getFuncName() { return mFuncName; };
private:
    bool mIsTerm = false;
    std::string mFuncName;
    bool mIsLead = true;
    int mBblNumber;
};

#endif