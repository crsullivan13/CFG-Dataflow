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
    PHI,

    NONE
};

class Instruction {
public:
    Instruction(InstructionType type, int bblNumber) : mType{type}, mBblNumber{bblNumber} {}
    virtual ~Instruction() {};

    InstructionType getType() { return mType; };
    virtual std::string getName() { return ""; };
    virtual std::string getDest() { return ""; };

    virtual std::string getTgt1() { return ""; };
    virtual std::string getTgt2() { return ""; };

    int getBblNum() { return mBblNumber; };
    void setBblNum(int num) { mBblNumber = num; };

    virtual std::string getValue() { return ""; };
    virtual std::vector<std::string> getParams() { std::vector<std::string> temp{}; return temp; };

    virtual bool getDeclare() {return false;};
protected:
    InstructionType mType;
    int mBblNumber;
};

class Phi : public Instruction {
public:
    Phi(InstructionType type, int bblNumber, std::string dest, std::vector<std::string> pairs) : Instruction(type, bblNumber), mDest{dest}, mPairs{pairs} {}
    ~Phi(){};

    std::string getDest() { return mDest; };
    std::vector<std::string> getParams() { return mPairs; };
private:
    std::string mDest;
    std::vector<std::string> mPairs;

};

class Global : public Instruction {
public:
    Global(InstructionType type, int bblNumber, std::string name, std::string value) : Instruction(type, bblNumber), mName{name}, mValue{value} {}
    ~Global(){};

    std::string getName() { return mName; };
    std::string getValue() { return mValue; };
private:
    std::string mName;
    std::string mValue;
};

class LabelInstr : public Instruction {
public:
    LabelInstr(InstructionType type, int bblNumber, std::string name) : Instruction(type, bblNumber), mName{name} {}
    ~LabelInstr(){};

    std::string getName() { return mName; };
private:
    std::string mName;
};

class Alloca : public Instruction {
public:
    Alloca(InstructionType type, int bblNumber, std::string dest) : Instruction(type, bblNumber), mDest{dest} {}
    ~Alloca(){};

    std::string getDest() { return mDest; };
private:
    std::string mDest;
};

class Load : public Instruction {
public:
    Load(InstructionType type, int bblNumber, std::string address, std::string dest) : Instruction(type, bblNumber), mAddress{address}, mDest{dest} {}
    ~Load(){};

    std::string getDest() { return mDest; };
    std::string getName() { return mAddress; };
private:
    std::string mAddress;
    std::string mDest;
};

class Store : public Instruction {
public:
    Store(InstructionType type, int bblNumber, std::string address, std::string value) : Instruction(type, bblNumber), mAddress{address}, mVal{value} {}
    ~Store(){}

    std::string getValue() { return mVal; };
    std::string getName() { return mAddress; };
private:
    std::string mAddress;
    std::string mVal;
};

class Ret : public Instruction {
public:
    Ret(InstructionType type, int bblNumber, std::string op1) : Instruction(type, bblNumber), mOp1{op1} {}
    ~Ret(){};

    std::string getTgt1() { return mOp1; };
private:
    std::string mOp1;
};

class Icmp : public Instruction {
public:
    Icmp(InstructionType type, int bblNumber, std::string dest, std::string op1, std::string op2) : Instruction(type, bblNumber), mDest{dest}, mOp1{op1}, mOp2{op2} {}
    ~Icmp(){};

    std::string getDest() { return mDest; };
    std::string getTgt1() { return mOp1; };
    std::string getTgt2() { return mOp2; };
private:
    std::string mDest;
    std::string mOp1;
    std::string mOp2;
};

class Br : public Instruction {
public:
    Br(InstructionType type, int bblNumber, std::string target1, std::string target2) : Instruction(type, bblNumber), mTarget1{target1}, mTarget2{target2} {}
    ~Br(){};

    std::string getTgt1() { return mTarget1; };
    std::string getTgt2() { return mTarget2; };
private:
    std::string mTarget1;
    std::string mTarget2;
};

class Arithmetic : public Instruction {
public:
    Arithmetic(InstructionType type, int bblNumber, std::string dest, std::string op1, std::string op2) : Instruction(type, bblNumber), mDest{dest}, mOp1{op1}, mOp2{op2} {}
    ~Arithmetic(){};

    std::string getDest() { return mDest; };
    std::string getTgt1() { return mOp1; };
    std::string getTgt2() { return mOp2; };
private:
    std::string mDest;
    std::string mOp1;
    std::string mOp2;
};

class Call : public Instruction {
public:
    Call(InstructionType type, int bblNumber, std::string funcName, std::vector<std::string> params, std::string dest) : Instruction(type, bblNumber), mFuncName{funcName}, mParams{params}, mDest{dest} {}
    ~Call(){};

    std::string getDest() { return mDest; };
    std::string getName() { return mFuncName; };
    std::vector<std::string> getParams() { return mParams; };
private:
    std::string mFuncName;
    std::vector<std::string> mParams;
    std::string mDest;
};

class Define : public Instruction {
public:
    Define(InstructionType type, int bblNumber, std::string funcName, bool isDeclare) : Instruction(type, bblNumber), mFuncName{funcName}, mIsDeclare(isDeclare) {}
    ~Define(){};

    std::string getName() { return mFuncName; };
    bool getDeclare() { return mIsDeclare; };
private:
    std::string mFuncName;
    bool mIsDeclare;
};

#endif