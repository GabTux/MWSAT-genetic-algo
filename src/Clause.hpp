#ifndef GENALGO_CLAUSE_HPP
#define GENALGO_CLAUSE_HPP

#include <string>
#include "evoConfig.hpp"

class Clause {
public:
    Clause() = default;
    explicit Clause(const std::string& line);
    bool isTrue(const bool * eval) const;

private:
    int variables[maxConfig::maxVars];
};


#endif //GENALGO_CLAUSE_HPP
