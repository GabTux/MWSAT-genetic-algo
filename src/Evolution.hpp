#ifndef GENALGO_EVOLUTION_HPP
#define GENALGO_EVOLUTION_HPP

#include <random>

#include "Individual.hpp"
#include "Instance.hpp"
#include "evoConfig.hpp"

class Evolution {

public:
    explicit Evolution(Instance& instance, const evoConfig *config);
    Individual& doGenetics();

private:
    Individual m_population[maxConfig::maxPopulationSize];
    Individual m_nextPopulation[maxConfig::maxPopulationSize];
    Individual* m_p_population = m_population;
    Individual* m_p_nextPopulation = m_nextPopulation;
    Instance& m_instance;
    const int m_elitismCount = 1;
    const evoConfig* m_config;
    unsigned int m_unchangedCount = 0;
    int m_lastBestFitness = 0;
    Individual* m_p_best = nullptr;

    void initPopulation();
    void crossovers();
    void mutations();
    int tournament();
    Individual * getBest();
    void printPopulation();
    void copyElistic();
    void getProgValues(int& min, double &avg, int& max);
};


#endif //GENALGO_EVOLUTION_HPP
