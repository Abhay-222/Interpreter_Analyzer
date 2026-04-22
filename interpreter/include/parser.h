#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "instruction.h"

Instruction parseLine(const std::string &line);

#endif