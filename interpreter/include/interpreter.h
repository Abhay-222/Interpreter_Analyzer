#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <set>
#include "instruction.h"

void executeProgram(std::vector<Instruction> &instructions, bool debugMode);

#endif