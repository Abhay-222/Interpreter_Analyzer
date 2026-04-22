#include "../include/utils.h"
#include <cctype>

bool isNumber(const std::string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

std::string removeComma(std::string s) {
    if (!s.empty() && s.back() == ',') {
        s.pop_back();
    }
    return s;
}