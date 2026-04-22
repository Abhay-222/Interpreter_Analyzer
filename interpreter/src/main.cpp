#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/analyzer.h"

int main() {
    std::ifstream file("input/test.asm");

    if (!file) {
        std::cout << "Error opening file\n";
        return 1;
    }

    std::vector<Instruction> instructions;
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        instructions.push_back(parseLine(line));
    }

    // 🔥 ANALYZER STEP
    if (!analyzeProgram(instructions)) {
        std::cout << "Fix errors before execution: \n";
        return 1;
    }

    bool debugMode = true;

    executeProgram(instructions, debugMode);

    return 0;
}