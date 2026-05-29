#include "fib_prng.h"

uint64_t FibonacciPRNG::next()
{
    uint64_t next_value = (A * A) + ((B * B) << 17 | (B * B) >> 47);
    A = B;
    B = next_value;
    return B;
}