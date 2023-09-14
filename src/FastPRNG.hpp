#ifndef GENALGO_FASTPRNG_HPP
#define GENALGO_FASTPRNG_HPP


#include <pcg_random.hpp>
#include <random>

class FastPRNG {
public:
    static void seed();
    static unsigned int randomNumber(unsigned int b);
    static bool randomBool();
    static bool makeChoice(double probability);
private:
    FastPRNG() = default;
    static pcg32 m_rng;
};

#endif //GENALGO_FASTPRNG_HPP
