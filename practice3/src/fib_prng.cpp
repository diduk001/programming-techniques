#include "fib_prng.h"

#include <vector>

uint64_t FibonacciPRNG::next()
{
    uint64_t next_value = (A * A) + ((B * B) << 17 | (B * B) >> 47);
    A = B;
    B = next_value;
    return B;
}

std::vector<uint64_t> generate_fib_sample(uint64_t seed, size_t num_samples)
{
    std::vector<uint64_t> sample(num_samples);
    FibonacciPRNG prng(seed);
    for (size_t i = 0; i < num_samples; i++)
    {
        sample[i] = prng.next();
    }
    return sample;
}