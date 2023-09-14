#ifndef GENALGO_EVOCONFIG_HPP
#define GENALGO_EVOCONFIG_HPP

#include <string>

namespace maxConfig {
    const int maxGenerations = 50000;
    const int maxPopulationSize = 1000;
    const int maxTournamentSize = maxPopulationSize;
    const int maxVars = 100;
    const int maxClauses = 430;
};

struct evoConfig {
    bool estimate;
    unsigned int generations;
    unsigned int populationSize;
    unsigned int tournamentSize;
    unsigned int runs;
    unsigned int resetAfter;
    double mutationProbability;
    double crossoverProbability;
    std::string instancesDir;
    std::string outFile;
    unsigned int threads;
    bool progress;
};

#endif //GENALGO_EVOCONFIG_HPP
