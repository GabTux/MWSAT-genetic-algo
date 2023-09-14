#include <sstream>
#include <utility>
#include "Instance.hpp"


Instance::Instance(fs::path inputPath) :
        m_filePath(std::move(inputPath))
{
    m_id = m_filePath.stem().string();
    m_id = m_id.substr(1);
    std::ifstream inputStream(m_filePath.string());
    readHeading(inputStream);
    readClauses(inputStream);
}

void Instance::readHeading(std::ifstream &inputStream) {
    std::string line;
    while (std::getline(inputStream, line)) {
        std::istringstream iss(line);

        char lineType;
        iss >> lineType;
        if (lineType == 'c') { // comment - skip
            continue;
        } else if (lineType == 'p') { // instance dimensions
            std::string fileExt;
            iss >> fileExt;
            iss >> m_varCount >> m_clausesCount;
        } else if (lineType == 'w') { // m_weights
            for (int i = 0; i < m_varCount; i++) {
                int w;
                iss >> w;
                m_weights[i] = w;
            }
            std::getline(inputStream, line); // skip range line
            break;
        } else { // error
            throw std::runtime_error("Bad input file");
        }
    }
    if (!inputStream.good()) {
        throw std::runtime_error("Bad input file");
    }
}

void Instance::readClauses(std::ifstream &inputStream) {
    std::string line;
    int i = 0;
    while (std::getline(inputStream, line)) {
        m_clauses[i++] = Clause(line);
    }
    if (m_clausesCount != i) {
        throw std::runtime_error("Bad input file");
    }
}

int Instance::varCount() const {
    return m_varCount;
}

const Clause* Instance::getClauses() const {
    return m_clauses;
}

const int * Instance::getWeights() const {
    return m_weights;
}

const std::string& Instance::getID() const {
    return m_id;
}

int Instance::clausesCount() const {
    return m_clausesCount;
}

const fs::path& Instance::getPath() const {
    return m_filePath;
}

