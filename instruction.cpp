#include "instruction.hpp"

Instruction::Instruction() {
    mType = InstructionType::NONE;
    mIsLead = false;
    mIsTerm = false;
    mBblNumber = 0;
}

Global::Global(InstructionType type, std::string name, std::string value) {
    mType = type;
    mName = name;
    mValue = value;
}

LabelInstr::LabelInstr(InstructionType type, std::string name, int bblNumber) {
    mType = type;
    mName = name;
    mBblNumber = bblNumber;
}

Load::Load(InstructionType type, std::string address, std::string dest, int bblNumber) {
    mType = type;
    mAddress = address;
    mDest = dest;
    mBblNumber = bblNumber;
}

Store::Store(InstructionType type, std::string address, std::string value, int bblNumber) {
    mType = type;
    mAddress = address;
    mBblNumber = bblNumber;
    mVal = value;
}

Ret::Ret(InstructionType type, std::string op1, int bblNumber) {
    mType = type;
    mOp1 = op1;
    mBblNumber = bblNumber;
}

Icmp::Icmp(InstructionType type, std::string dest, int bblNumber) {
    mType = type;
    mDest = dest;
    mBblNumber = bblNumber;
}

Br::Br(InstructionType type, std::string target1, std::string target2, int bblNumber) {
    mType = type;
    mTarget1 = target1;
    mTarget2 = target2;
    mBblNumber = bblNumber;
}

Arithmetic::Arithmetic(InstructionType type, std::string dest, std::string op1, std::string op2, int bblNumber) {
    mType = type;
    mDest = dest;
    mOp1 = op1;
    mOp2 = op2;
    mBblNumber = bblNumber;
}

Call::Call(InstructionType type, std::string funcName, std::vector<std::string> params, int bblNumber) {
    mType = type;
    mParams = params;
    mBblNumber = bblNumber;
    mIsTerm = true;
    mFuncName = funcName;
}

Define::Define(InstructionType type, std::string funcName, int bblNumber) {
    mType = type;
    mFuncName = funcName;
    mBblNumber = bblNumber;
}