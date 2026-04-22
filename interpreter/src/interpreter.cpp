#include "../include/interpreter.h"
#include "../include/utils.h"
#include <iostream>
#include <map>
#include <set>

std::map<std::string, int> reg;
std::map<std::string, int> labelMap;
std::vector<int> stack;

// 🔥 Breakpoints (hardcoded for now)
std::set<int> breakpoints = {2}; // stops at instruction index 2

bool continueMode = false;

// Print instruction
void printInstruction(const Instruction &inst) {
    std::cout << "Executing: ";

    if (inst.type == InstrType::MOV) std::cout << "MOV ";
    else if (inst.type == InstrType::ADD) std::cout << "ADD ";
    else if (inst.type == InstrType::SUB) std::cout << "SUB ";
    else if (inst.type == InstrType::MUL) std::cout << "MUL ";
    else if (inst.type == InstrType::DIV) std::cout << "DIV ";
    else if (inst.type == InstrType::PRINT) std::cout << "PRINT ";
    else if (inst.type == InstrType::JMP) std::cout << "JMP ";
    else if (inst.type == InstrType::IF) std::cout << "IF ";
    else if (inst.type == InstrType::PUSH) std::cout << "PUSH ";
    else if (inst.type == InstrType::POP) std::cout << "POP ";
    else if (inst.type == InstrType::CALL) std::cout << "CALL ";
    else if (inst.type == InstrType::RET) std::cout << "RET ";
    else if (inst.type == InstrType::LABEL) std::cout << "LABEL ";

    std::cout << inst.arg1 << " " << inst.arg2 << std::endl;
}

void printRegisters() {
    std::cout << "Registers: ";
    for (auto &p : reg) {
        std::cout << p.first << "=" << p.second << " ";
    }
    std::cout << std::endl;
}

void printStack() {
    std::cout << "Stack: ";
    for (int x : stack) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void executeProgram(std::vector<Instruction> &instructions, bool debugMode) {

    // Build label map
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i].type == InstrType::LABEL) {
            labelMap[instructions[i].arg1] = i;
        }
    }

    int ip = 0;

    while (ip < instructions.size()) {
        Instruction &inst = instructions[ip];

        // 🔥 Debugger logic
        if (debugMode && (!continueMode || breakpoints.count(ip))) {

            std::cout << "\nIP: " << ip << std::endl;
            printInstruction(inst);
            printRegisters();
            printStack();

            std::cout << "[Enter] Step | [c] Continue | [q] Quit : ";

            std::string input;
            std::getline(std::cin, input);

            if (input == "c") {
                continueMode = true;
            } else if (input == "q") {
                return;
            }
        }

        // Execution
        if (inst.type == InstrType::MOV) {
            if (isNumber(inst.arg2))
                reg[inst.arg1] = std::stoi(inst.arg2);
            else
                reg[inst.arg1] = reg[inst.arg2];
        }
        else if (inst.type == InstrType::ADD) {
            reg[inst.arg1] += reg[inst.arg2];
        }
        else if (inst.type == InstrType::SUB) {
            reg[inst.arg1] -= reg[inst.arg2];
        }
        else if (inst.type == InstrType::MUL) {
            reg[inst.arg1] *= reg[inst.arg2];
        }
        else if (inst.type == InstrType::DIV) {
            if (reg[inst.arg2] == 0) {
                std::cout << "Division by zero\n";
                return;
            }
            reg[inst.arg1] /= reg[inst.arg2];
        }
        else if (inst.type == InstrType::PRINT) {
            std::cout << "OUTPUT: " << reg[inst.arg1] << std::endl;
        }
        else if (inst.type == InstrType::JMP) {
            if (labelMap.find(inst.arg1) != labelMap.end()) {
                ip = labelMap[inst.arg1];
                continue;
            }
        }
        else if (inst.type == InstrType::IF) {

            int left = isNumber(inst.arg1) ? std::stoi(inst.arg1) : reg[inst.arg1];
            int right = isNumber(inst.arg2) ? std::stoi(inst.arg2) : reg[inst.arg2];

            bool condition = false;

            if (inst.op == ">") condition = left > right;
            else if (inst.op == "<") condition = left < right;
            else if (inst.op == "==") condition = left == right;
            else if (inst.op == "!=") condition = left != right;
            else if (inst.op == ">=") condition = left >= right;
            else if (inst.op == "<=") condition = left <= right;

            if (condition) {
                if (labelMap.find(inst.jumpLabel) != labelMap.end()) {
                    ip = labelMap[inst.jumpLabel];
                    continue;
                }
            }
        }
        else if (inst.type == InstrType::PUSH) {
            stack.push_back(reg[inst.arg1]);
        }
        else if (inst.type == InstrType::POP) {
            if (!stack.empty()) {
                reg[inst.arg1] = stack.back();
                stack.pop_back();
            }
        }
        else if (inst.type == InstrType::CALL) {
            if (labelMap.find(inst.arg1) != labelMap.end()) {
                stack.push_back(ip + 1);
                ip = labelMap[inst.arg1];
                continue;
            }
        }
        else if (inst.type == InstrType::RET) {
            if (!stack.empty()) {
                ip = stack.back();
                stack.pop_back();
                continue;
            }
        }

        ip++;
    }
}


