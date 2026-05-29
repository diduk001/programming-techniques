#include "fib_prng.h"

uint64_t FibonacciPRNG::next()
{
    uint64_t next_value = (A * A) ^ (B * B); // Вычисляем следующее значение по формуле A^2 ^ B^2
    A = B;                                   // Обновляем A
    B = next_value;                          // Обновляем B
    return B;                                // Возвращаем новое значение B как псевдослучайное число
}