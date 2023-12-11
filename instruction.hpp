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
    LABEL,
    GLOBAL,

    NONE
};

class Instruction {
public:
    Instruction();
    Instruction(InstructionType type, int bblNumber = 0) : mType{type}, mBblNumber{bblNumber} {};

    InstructionType getType() { return mType; };
    virtual std::string getName() { return ""; };
    virtual std::string getDest() { return ""; };

    virtual std::string getTgt1() { return ""; };
    virtual std::string getTgt2() { return ""; };

    int getBblNum() { return mBblNumber; };
    void setBblNum(int num) { mBblNumber = num; };

    virtual std::string getValue() { return ""; };
    virtual std::vector<std::string> getParams() { std::vector<std::string> temp{}; return temp; };
protected:
    InstructionType mType;
    bool mIsTerm;
    bool mIsLead;
    int mBblNumber;
};

class Global : public Instruction {
public:
    Global(InstructionType type, std::string name, std::string value);

    std::string getName() { return mName; };
    std::string getValue() { return mValue; };
private:
    std::string mName;
    std::string mValue;
};

class LabelInstr : public Instruction {
public:
    LabelInstr(InstructionType type, std::string name, int bblNumber);

    std::string getName() { return mName; };
private:
    std::string mName;
    int mBblNumber;
};

class Alloca : public Instruction {
public:
    Alloca(InstructionType type, std::string dest, int bblNumber) : mType{type}, mDest{dest}, mBblNumber{bblNumber} {};

    std::string getDest() { return mDest; };
private:
    Instruction mType;
    std::string mDest;
    int mBblNumber;
};

class Load : public Instruction {
public:
    Load(InstructionType type, std::string address, std::string dest, int bblNumber);

    std::string getDest() { return mDest; };
    std::string getName() { return mAddress; };
private:
    std::string mAddress;
    std::string mDest;
    int mBblNumber;
};

class Store : public Instruction {
public:
    Store(InstructionType type, std::string address, std::string value, int bblNumber);

    std::string getValue() { return mVal; };
    std::string getName() { return mAddress; };
private:
    std::string mAddress;
    std::string mVal;
    int mBblNumber;
};

class Ret : public Instruction {
public:
    Ret(InstructionType type, std::string op1, int bblNumber);

    std::string getTgt1() { return mOp1; };
private:
    std::string mOp1;
    int mBblNumber;
};

class Icmp : public Instruction {
public:
    Icmp(InstructionType type, std::string dest, int bblNumber);

    std::string getDest() { return mDest; };
private:
    std::string mDest;
    int mBblNumber;
};

class Br : public Instruction {
public:
    Br(InstructionType type, std::string target1, std::string target2, int bblNumber);

    std::string getTgt1() { return mTarget1; };
    std::string getTgt2() { return mTarget2; };
private:
    std::string mTarget1;
    std::string mTarget2;
    int mBblNumber;
};

class Arithmetic : public Instruction {
public:
    Arithmetic(InstructionType type, std::string dest, std::string op1, std::string op2, int bblNumber);

    std::string getDest() { return mDest; };
    std::string getTgt1() { return mOp1; };
    std::string getTgt2() { return mOp2; };
private:
    std::string mDest;
    std::string mOp1;
    std::string mOp2;
    int mBblNumber;
};

class Call : public Instruction {
public:
    Call(InstructionType type, std::string funcName, std::vector<std::string> params, std::string dest, int bblNumber);

    std::string getDest() { return mDest; };
    std::string getName() { return mFuncName; };
    std::vector<std::string> getParams() { return mParams; };
private:
    std::vector<std::string> mParams;
    std::string mFuncName;
    std::string mDest;
    int mBblNumber;
};

class Define : public Instruction {
public:
    Define(InstructionType type, std::string funcName, int bblNumber);

    std::string getName() { return mFuncName; };
private:
    std::string mFuncName;
    int mBblNumber;
};

#endif