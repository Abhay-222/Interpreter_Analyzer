#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

enum class InstrType {
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    PRINT,
    JMP,
    IF,
    PUSH,
    POP,
    CALL,
    RET,
    LABEL,
    UNKNOWN
};

struct Instruction {
    InstrType type;
    std::string arg1;
    std::string arg2;

    // For IF
    std::string op;
    std::string jumpLabel;
};

#endif