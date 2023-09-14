#ifndef GENALGO_INDIVIDUAL_HPP
#define GENALGO_INDIVIDUAL_HPP

#include "Instance.hpp"
#include "evoConfig.hpp"
#include "FastPRNG.hpp"

class Individual {
public:
    Individual() = default;
    explicit Individual(const Instance * instance);
    Individual(Individual& p1, Individual& p2);
    [[nodiscard]] int getFitness() const;
    [[nodiscard]] int getTrueFitness() const;
    bool isValid();
    bool operator[](int idx);
    void mutate();
    friend std::ostream& operator<<(std::ostream& os, Individual const& m);

private:
    bool m_evaluation[maxConfig::maxVars];
    int m_fitness = 0;
    int m_trueClauses = 0;
    int m_weightFitness = 0;
    const Instance * m_instance = nullptr;
    int m_vars = 0;

    void calculateWeightFitness();
    void calculateFitness();
    void fitnessWithMult();
    void fitnessWithoutMult();
    void fitnessWithNegative();
    void calculateTrueClauses();
    void evaluate();
    void cross(Individual &p1, Individual &p2);
    void one_point_cross(Individual &p1, Individual &p2);
    void uniform_cross(Individual &p1, Individual &p2);
};


#endif //GENALGO_INDIVIDUAL_HPP
