#ifndef GENALGO_INSTANCE_HPP
#define GENALGO_INSTANCE_HPP

#include <string>
#include <fstream>
#include "Clause.hpp"
#include <filesystem>
#include "evoConfig.hpp"

namespace fs = std::filesystem;

class Instance {

public:
    explicit Instance(fs::path inputPath);
    [[nodiscard]] int varCount() const;
    [[nodiscard]] int clausesCount() const;
    [[nodiscard]] const Clause * getClauses() const;
    [[nodiscard]] const int * getWeights() const;
    [[nodiscard]] const std::string& getID() const;
    [[nodiscard]] const fs::path& getPath() const;

private:
    fs::path m_filePath;
    std::string m_id;
    int m_varCount{};
    int m_clausesCount{};
    Clause m_clauses[maxConfig::maxClauses];
    int m_weights[maxConfig::maxVars];

    void readHeading(std::ifstream& inputStream);
    void readClauses(std::ifstream& inputStream);
};


#endif //GENALGO_INSTANCE_HPP
