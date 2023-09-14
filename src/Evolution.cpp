#include "Evolution.hpp"
#include "FastPRNG.hpp"
#include <ranges>
#include <set>
#include <iostream>

Evolution::Evolution(Instance &instance, const evoConfig *config) :
    m_instance(instance),
    m_config(config)
{
}

Individual& Evolution::doGenetics() {
    initPopulation();
    std::ofstream progFile;
    if (m_config->progress) {
        fs::path progFilePath = m_instance.getPath();
        progFilePath.replace_extension(".prog");
        progFile.open(progFilePath);
    }
    for (unsigned int i = 0; i < m_config->generations; i++) {
        m_p_best = getBest();
        if (m_config->progress) {
            int min, max;
            double avg;
            getProgValues(min, avg, max);
            progFile << i << ". GEN: " << min << " "
            << avg << " " << max << std::endl;
            //printPopulation();
        }

        if (m_p_best->getFitness() == m_lastBestFitness) {
            m_unchangedCount++;
        } else {
            m_lastBestFitness = m_p_best->getFitness();
            m_unchangedCount = 0;
        }

        if (m_unchangedCount >= m_config->resetAfter) {
            m_unchangedCount = 0;
            if (!m_p_best->isValid()) {
                // stuck without valid solution --> reset all
                initPopulation();
            } else {
                // stuck with valid but maybe not optimal
                // --> copy m_p_best and reset rest
                Individual best = *m_p_best;
                initPopulation();
                m_p_population[0] = best;
            }
        }

        copyElistic();
        crossovers();
        mutations();
        std::swap(m_p_population, m_p_nextPopulation);
    }
    return *m_p_best;
}

void Evolution::initPopulation() {
    for (int i = 0; i < m_config->populationSize; i++) {
        m_p_population[i] = Individual(&m_instance);
    }
}

void Evolution::crossovers() {
    for (unsigned int i = m_elitismCount; i < m_config->populationSize; i++) {
        if (FastPRNG::makeChoice(m_config->crossoverProbability)) {
            int p1 = tournament();
            int p2 = tournament();
            m_p_nextPopulation[i] = Individual(m_p_population[p1], m_p_population[p2]);
        } else {
            m_p_nextPopulation[i] = m_p_population[tournament()];
        }
    }
}

void Evolution::mutations() {
    for (unsigned int i = m_elitismCount; i < m_config->populationSize; i++) {
        if (FastPRNG::makeChoice(m_config->mutationProbability)) {
            m_p_nextPopulation[i].mutate();
        }
    }
}

int Evolution::tournament() {
    int maxFitness = 0;
    int bestIdx = 0;
    for (unsigned int i = 0; i < m_config->tournamentSize; i++) {
        int randIdx = static_cast<int>(FastPRNG::randomNumber(m_config->populationSize));
        if (m_p_population[randIdx].getFitness() > maxFitness) {
            maxFitness = m_p_population[randIdx].getFitness();
            bestIdx = randIdx;
        }
    }
    return bestIdx;
}

Individual* Evolution::getBest() {
    int maxFitness = m_p_population[0].getFitness();
    int bestIdx = 0;
    for (int i = 0; i < m_config->populationSize; i++) {
        if (m_p_population[i].getFitness() > maxFitness) {
            maxFitness = m_p_population[i].getFitness();
            bestIdx = i;
        }
    }
    return &(m_p_population[bestIdx]);
}

void Evolution::printPopulation() {
    for (unsigned int i = 0; i < m_config->populationSize; i++) {
        std::cout << m_p_population[i] << ": " << m_p_population[i].getFitness() << std::endl;
    }
}

void Evolution::copyElistic() {
    m_p_nextPopulation[0] = *m_p_best;
}

void Evolution::getProgValues(int &min, double &avg, int &max) {
    int maxFitness = m_p_population[0].getFitness();
    int minFitness = m_p_population[0].getFitness();
    unsigned int sumFitness = 0;
    for (int i = 0; i < m_config->populationSize; i++) {
        sumFitness += m_p_population[i].getFitness();
        if (m_p_population[i].getFitness() > maxFitness) {
            maxFitness = m_p_population[i].getFitness();
        }
        if (m_p_population[i].getFitness() < minFitness) {
            minFitness = m_p_population[i].getFitness();
        }
    }
    min = minFitness;
    avg = sumFitness / static_cast<double>(m_config->populationSize);
    max = maxFitness;
}
