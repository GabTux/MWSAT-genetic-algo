#include <sstream>
#include "Clause.hpp"

Clause::Clause(const std::string& line) {
    std::istringstream iss(line);
    int i = 0;
    int var;
    while (iss >> var) {
        if (var == 0) {
            break;
        }
        variables[i++] = var;
    }
}

bool Clause::isTrue(const bool * eval) const {
    for (int i = 0; i < 3; i++) {
        int varIdx = abs(variables[i]) - 1;
        if (((eval[varIdx]) && (variables[i] > 0)) ||
            (!(eval[varIdx]) && (variables[i] < 0))) {
            return true;
        }
    }
    return false;
}
