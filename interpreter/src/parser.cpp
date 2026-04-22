#include "../include/parser.h"
#include "../include/utils.h"
#include <sstream>

Instruction parseLine(const std::string &line) {
    std::stringstream ss(line);
    std::string instr;

    ss >> instr;

    Instruction inst;

    // LABEL
    if (!instr.empty() && instr.back() == ':') {
        instr.pop_back();
        inst.type = InstrType::LABEL;
        inst.arg1 = instr;
        return inst;
    }

    // IF CONDITION
    if (instr == "IF") {
        std::string a, op, b, jmp, label;

        ss >> a >> op >> b >> jmp >> label;

        inst.type = InstrType::IF;
        inst.arg1 = a;
        inst.arg2 = b;
        inst.op = op;
        inst.jumpLabel = label;

        return inst;
    }

    // NORMAL INSTRUCTIONS
    std::string a, b;
    ss >> a >> b;

    a = removeComma(a);

if (instr == "MOV") inst.type = InstrType::MOV;
else if (instr == "ADD") inst.type = InstrType::ADD;
else if (instr == "SUB") inst.type = InstrType::SUB;
else if (instr == "MUL") inst.type = InstrType::MUL;
else if (instr == "DIV") inst.type = InstrType::DIV;
else if (instr == "PRINT") inst.type = InstrType::PRINT;
else if (instr == "JMP") inst.type = InstrType::JMP;
else if (instr == "PUSH") inst.type = InstrType::PUSH;
else if (instr == "POP") inst.type = InstrType::POP;
else if (instr == "CALL") inst.type = InstrType::CALL;
else if (instr == "RET") inst.type = InstrType::RET;
else inst.type = InstrType::UNKNOWN;

    inst.arg1 = a;
    inst.arg2 = b;

    return inst;
}