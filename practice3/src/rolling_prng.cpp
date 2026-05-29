#include "rolling_prng.h"

#include <vector>

RollingPRNG::RollingPRNG(const uint8_t seed[8])
{
    for (int i = 0; i < 8; i++)
    {
        state[i] ^= seed[i];
    }
}

uint64_t RollingPRNG::next()
{
    uint64_t X = 0;
    uint64_t p = 1;
    for (int i = 0; i < 8; i++)
    {
        X += state[i] * p;
        p *= P;
    }

    // Сдвигаем состояние
    for (int i = 7; i > 0; i--)
    {
        state[i] = state[i - 1];
    }
    state[0] = X % 256;

    return X;
}

std::vector<uint64_t> generate_rolling_sample(const uint8_t seed[8], size_t num_samples)
{
    std::vector<uint64_t> sample(num_samples);
    RollingPRNG prng(seed);
    for (size_t i = 0; i < num_samples; i++)
    {
        sample[i] = prng.next();
    }
    return sample;
}