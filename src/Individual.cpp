#include "Individual.hpp"
#include "FastPRNG.hpp"

Individual::Individual(const Instance * instance) :
    m_instance(instance),
    m_vars(m_instance->varCount())
{
    for (int i = 0; i < m_vars; i++) {
        m_evaluation[i] = FastPRNG::randomBool();
    }
    evaluate();
}


Individual::Individual(Individual &p1, Individual &p2) :
    m_instance(p1.m_instance),
    m_vars(m_instance->varCount())
{
    cross(p1, p2);
    evaluate();
}

void Individual::calculateTrueClauses() {
    m_trueClauses = 0;
    const Clause * clauses = m_instance->getClauses();
    for (int i = 0; i < m_instance->clausesCount(); i++) {
        if (clauses[i].isTrue(m_evaluation)) {
            m_trueClauses++;
        }
    }
}

int Individual::getFitness() const {
    return m_fitness;
}

void Individual::calculateFitness() {
    fitnessWithMult();
}

bool Individual::operator[](int idx) {
    return m_evaluation[idx];
}

void Individual::calculateWeightFitness() {
    m_weightFitness = 0;
    for (int i = 0; i < m_vars; i++) {
        if (m_evaluation[i]) {
            m_weightFitness += m_instance->getWeights()[i];
        }
    }
}

void Individual::mutate() {
    int rIdx = static_cast<int>(FastPRNG::randomNumber(m_vars));
    m_evaluation[rIdx] = !m_evaluation[rIdx];
    evaluate();
}

bool Individual::isValid() {
    return m_trueClauses == m_instance->clausesCount();
}

std::ostream &operator<<(std::ostream &os, const Individual &m) {
    for (int i = 0; i < m.m_vars; i++) {
        if (m.m_evaluation[i]) {
            os << i+1 << " ";
        } else {
            os << -(i+1) << " ";
        }
    }
    return os;
}

void Individual::evaluate() {
    calculateTrueClauses();
    calculateFitness();
}

void Individual::cross(Individual &p1, Individual &p2) {
    uniform_cross(p1, p2);
}

void Individual::one_point_cross(Individual &p1, Individual &p2) {
    int splitIdx = static_cast<int>(FastPRNG::randomNumber(m_vars));
    for (int i = 0; i < splitIdx; i++) {
        m_evaluation[i] = p1.m_evaluation[i];
    }
    for (int i = splitIdx; i < m_vars; i++) {
        m_evaluation[i] = p2.m_evaluation[i];
    }
}

void Individual::uniform_cross(Individual &p1, Individual &p2) {
    for (int i = 0; i < m_vars; i++) {
        if (FastPRNG::randomBool()) {
            m_evaluation[i] = p1.m_evaluation[i];
        } else {
            m_evaluation[i] = p2.m_evaluation[i];
        }
    }
}

int Individual::getTrueFitness() const {
    return m_weightFitness;
}

void Individual::fitnessWithMult() {
    m_fitness = 0;
    if (isValid()) {
        calculateWeightFitness();
        m_fitness = 31 * m_weightFitness;
    } else {
        m_fitness = m_trueClauses;
    }
}

void Individual::fitnessWithoutMult() {
    m_fitness = 0;
    if (isValid()) {
        calculateWeightFitness();
        m_fitness = m_weightFitness;
    } else {
        m_fitness = m_trueClauses;
    }
}

void Individual::fitnessWithNegative() {
    m_fitness = 0;
    if (isValid()) {
        calculateWeightFitness();
        m_fitness = m_weightFitness;
    } else {
        m_fitness = -(m_instance->clausesCount() - m_trueClauses);
    }
}
