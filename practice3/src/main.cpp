#include "aes_prng.h"
#include "fib_prng.h"
#include "rolling_prng.h"

#include "statistic_tests.h"
#include "prng_tests.h"

#include <cstdio>
#include <iostream>
#include <vector>

const int NUM_SAMPLES = 20000; // Количество сгенерированных чисел для статистических тестов
const int NUM_BINS = 20;      // Количество корзин для тестов Хи-квадрат

const uint8_t seed_16[16] = {
    0xd5,
    0x14,
    0xe8,
    0x4b,
    0xaf,
    0x10,
    0x48,
    0x64,
    0x28,
    0xb2,
    0x88,
    0x40,
    0x6f,
    0xb3,
    0xb4,
    0x6d,
}; //!< Изначальное значение (seed) для генераторов

const uint64_t uint64_t_seed = 0xd514e84baf104864; //!< Изначальное значение (seed) для генератора Фибоначчи

const uint8_t seed_8[8] = {0xd5, 0x14, 0xe8, 0x4b, 0xaf, 0x10, 0x48, 0x64}; //!< Изначальное значение (seed) для генератора Rolling

int main()
{
    std::cout << std::fixed;

    std::vector<uint64_t> aes_sample = generate_aes_sample(seed_16, NUM_SAMPLES);

    std::cout << "AES PRNG Sample Statistics:" << std::endl;
    std::cout << "\tMean: " << mean(aes_sample) << std::endl;
    std::cout << "\tStandard Deviation: " << stddev(aes_sample) << std::endl;
    std::cout << "\tCoefficient of Variation: " << cv(aes_sample) << std::endl;
    std::cout << "\tChi-Square Uniformity Test: " << chi_square_uniformity_test(aes_sample, NUM_BINS) << std::endl;
    std::cout << "\tChi-Square Randomness Test: " << isUniform(chi_square_uniformity_test(aes_sample, NUM_BINS), NUM_BINS) << std::endl;

    std::cout << "p-value for NIST tests: " << std::endl;
    std::cout << "\tFrequency Test: " << frequencyTest(aes_sample) << std::endl;
    std::cout << "\tBlock Frequency Test: " << blockFrequencyTest(aes_sample, 100) << std::endl;
    std::cout << "\tRuns Test: " << runsTest(aes_sample) << std::endl;
    std::cout << "\tLongest Run Test: " << longestRunTest(aes_sample) << std::endl;
    std::cout << std::endl;

    std::vector<uint64_t> fib_sample = generate_fib_sample(uint64_t_seed, NUM_SAMPLES);

    std::cout << "Fibonacci PRNG Sample Statistics:" << std::endl;
    std::cout << "\tMean: " << mean(fib_sample) << std::endl;
    std::cout << "\tStandard Deviation: " << stddev(fib_sample) << std::endl;
    std::cout << "\tCoefficient of Variation: " << cv(fib_sample) << std::endl;
    std::cout << "\tChi-Square Uniformity Test: " << chi_square_uniformity_test(fib_sample, NUM_BINS) << std::endl;
    std::cout << "\tChi-Square Randomness Test: " << isUniform(chi_square_uniformity_test(fib_sample, NUM_BINS), NUM_BINS) << std::endl;

    std::cout << "p-value for NIST tests: " << std::endl;
    std::cout << "\tFrequency Test: " << frequencyTest(fib_sample) << std::endl;
    std::cout << "\tBlock Frequency Test: " << blockFrequencyTest(fib_sample, 100) << std::endl;
    std::cout << "\tRuns Test: " << runsTest(fib_sample) << std::endl;
    std::cout << "\tLongest Run Test: " << longestRunTest(fib_sample) << std::endl;
    std::cout << std::endl;

    std::vector<uint64_t> rolling_sample = generate_rolling_sample(seed_8, NUM_SAMPLES);

    std::cout << "Rolling PRNG Sample Statistics:" << std::endl;
    std::cout << "\tMean: " << mean(rolling_sample) << std::endl;
    std::cout << "\tStandard Deviation: " << stddev(rolling_sample) << std::endl;
    std::cout << "\tCoefficient of Variation: " << cv(rolling_sample) << std::endl;
    std::cout << "\tChi-Square Uniformity Test: " << chi_square_uniformity_test(rolling_sample, NUM_BINS) << std::endl;
    std::cout << "\tChi-Square Randomness Test: " << isUniform(chi_square_uniformity_test(rolling_sample, NUM_BINS), NUM_BINS) << std::endl;

    std::cout << "p-value for NIST tests: " << std::endl;
    std::cout << "\tFrequency Test: " << frequencyTest(rolling_sample) << std::endl;
    std::cout << "\tBlock Frequency Test: " << blockFrequencyTest(rolling_sample, 100) << std::endl;
    std::cout << "\tRuns Test: " << runsTest(rolling_sample) << std::endl;
    std::cout << "\tLongest Run Test: " << longestRunTest(rolling_sample) << std::endl;
    std::cout << std::endl;

    return 0;
}