#include "FastPRNG.hpp"
#include <random>

pcg32 FastPRNG::m_rng;

void FastPRNG::seed() {
    m_rng.seed(pcg_extras::seed_seq_from<std::random_device>());
}

unsigned int FastPRNG::randomNumber(unsigned int b) {
    return m_rng(b);
}

bool FastPRNG::randomBool() {
    return m_rng(2);
}

bool FastPRNG::makeChoice(double probability) {
    return probability*100 > m_rng(100);
}
