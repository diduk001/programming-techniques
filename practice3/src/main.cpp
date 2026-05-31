#include "aes_prng.h"
#include "fib_prng.h"
#include "rolling_prng.h"

#include "statistic_tests.h"
#include "prng_tests.h"
#include "utils.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
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

const std::vector<size_t> TIMING_SIZES = {
    1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000,
}; //!< Логарифмически распределённые размеры выборок для замера времени генерации

std::vector<uint64_t> generate_mt19937_sample(uint64_t seed, size_t num_samples)
{
    std::mt19937_64 prng(seed);
    std::vector<uint64_t> sample(num_samples);
    for (size_t i = 0; i < num_samples; ++i)
    {
        sample[i] = prng();
    }
    return sample;
}

int main(int argc, char *argv[])
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

    const std::string csv_path = (argc > 1) ? argv[1] : "tests/results/results.csv";
    std::ofstream csv(csv_path);
    if (!csv.is_open())
    {
        std::cerr << "Failed to open " << csv_path << " for writing" << std::endl;
        return 1;
    }
    csv << std::fixed;
    csv << "size,aes_time,fib_time,rolling_time,std_time\n";

    std::cout << "Timing tests (ms):" << std::endl;
    std::cout << "\tsize\tAES\tFib\tRolling\tstd::mt19937_64" << std::endl;
    for (size_t size : TIMING_SIZES)
    {
        double aes_time = measure_time_ms(
            [](size_t s) { return generate_aes_sample(seed_16, s); }, size);
        double fib_time = measure_time_ms(
            [](size_t s) { return generate_fib_sample(uint64_t_seed, s); }, size);
        double rolling_time = measure_time_ms(
            [](size_t s) { return generate_rolling_sample(seed_8, s); }, size);
        double std_time = measure_time_ms(
            [](size_t s) { return generate_mt19937_sample(uint64_t_seed, s); }, size);

        std::cout << "\t" << size
                  << "\t" << aes_time
                  << "\t" << fib_time
                  << "\t" << rolling_time
                  << "\t" << std_time << std::endl;
        csv << size << ","
            << aes_time << ","
            << fib_time << ","
            << rolling_time << ","
            << std_time << "\n";
    }
    std::cout << "Timing results written to " << csv_path << std::endl;

    return 0;
}