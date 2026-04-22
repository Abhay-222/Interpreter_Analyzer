#include "../include/analyzer.h"
#include <iostream>
#include <set>

bool analyzeProgram(const std::vector<Instruction> &instructions) {

    std::set<std::string> labels;
    bool hasError = false;

    // 🔥 Collect labels
    for (const auto &inst : instructions) {
        if (inst.type == InstrType::LABEL) {
            labels.insert(inst.arg1);
        }
    }

    // 🔥 Validate instructions
    for (int i = 0; i < instructions.size(); i++) {
        const auto &inst = instructions[i];

        // UNKNOWN instruction
        if (inst.type == InstrType::UNKNOWN) {
            std::cout << "Error at line " << i << ": Unknown instruction\n";
            hasError = true;
        }

        // JMP validation
        if (inst.type == InstrType::JMP) {
            if (!labels.count(inst.arg1)) {
                std::cout << "Error at line " << i << ": Undefined label " << inst.arg1 << "\n";
                hasError = true;
            }
        }

        // IF validation
        if (inst.type == InstrType::IF) {
            if (!labels.count(inst.jumpLabel)) {
                std::cout << "Error at line " << i << ": Undefined label " << inst.jumpLabel << "\n";
                hasError = true;
            }

            if (inst.op.empty()) {
                std::cout << "Error at line " << i << ": Invalid IF condition\n";
                hasError = true;
            }
        }

        // DIV static check (basic)
        if (inst.type == InstrType::DIV) {
            if (inst.arg2 == "0") {
                std::cout << "Warning at line " << i << ": Division by zero possible\n";
            }
        }
    }

    if (!hasError) {
        std::cout << "Analysis Passed ✅\n";
    }

    return !hasError;
}