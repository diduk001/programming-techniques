#include "prng_tests.h"

#include <cmath>
#include <cstdint>
#include <vector>

// Распаковка вектора uint64_t в последовательность бит (старший бит первым).
// NIST-тесты определены над битовыми последовательностями, поэтому каждое
// 64-битное число PRNG раскладывается на 64 бита.
static std::vector<uint8_t> toBits(const std::vector<uint64_t> &data)
{
    std::vector<uint8_t> bits;
    bits.reserve(data.size() * 64);
    for (uint64_t v : data)
    {
        for (int i = 63; i >= 0; --i)
        {
            bits.push_back(static_cast<uint8_t>((v >> i) & 1ULL));
        }
    }
    return bits;
}

// Регуляризованная верхняя неполная гамма-функция Q(a, x) = 1 - P(a, x).
// Реализация по Numerical Recipes: ряд при x < a+1, цепная дробь (Lentz) иначе.
static long double igamc(long double a, long double x)
{
    if (x < 0.0L || a <= 0.0L)
        return 0.0L;
    if (x == 0.0L)
        return 1.0L;

    const long double eps = 1e-15L;
    const long double tiny = 1e-300L;
    const long double gln = std::lgammal(a);

    if (x < a + 1.0L)
    {
        long double ap = a;
        long double sum = 1.0L / a;
        long double del = sum;
        for (int n = 1; n <= 1000; ++n)
        {
            ap += 1.0L;
            del *= x / ap;
            sum += del;
            if (std::fabsl(del) < std::fabsl(sum) * eps)
                break;
        }
        long double P = sum * std::expl(-x + a * std::logl(x) - gln);
        return 1.0L - P;
    }

    long double b = x + 1.0L - a;
    long double c = 1.0L / tiny;
    long double d = 1.0L / b;
    long double h = d;
    for (int i = 1; i <= 1000; ++i)
    {
        long double an = -static_cast<long double>(i) * (static_cast<long double>(i) - a);
        b += 2.0L;
        d = an * d + b;
        if (std::fabsl(d) < tiny)
            d = tiny;
        c = b + an / c;
        if (std::fabsl(c) < tiny)
            c = tiny;
        d = 1.0L / d;
        long double del = d * c;
        h *= del;
        if (std::fabsl(del - 1.0L) < eps)
            break;
    }
    return std::expl(-x + a * std::logl(x) - gln) * h;
}

long double frequencyTest(const std::vector<uint64_t> &data)
{
    std::vector<uint8_t> bits = toBits(data);
    long double n = static_cast<long double>(bits.size());
    long double sum = 0.0L;
    for (uint8_t b : bits)
        sum += (b ? 1.0L : -1.0L);
    long double sObs = std::fabsl(sum) / std::sqrtl(n);
    return std::erfcl(sObs / std::sqrtl(2.0L));
}

long double blockFrequencyTest(const std::vector<uint64_t> &data, int block_size)
{
    std::vector<uint8_t> bits = toBits(data);
    int n = static_cast<int>(bits.size());
    int N = n / block_size;
    if (N < 1)
        return 0.0L;

    long double sumSq = 0.0L;
    for (int b = 0; b < N; ++b)
    {
        int ones = 0;
        for (int i = 0; i < block_size; ++i)
            ones += bits[b * block_size + i];
        long double pi = static_cast<long double>(ones) / block_size;
        long double diff = pi - 0.5L;
        sumSq += diff * diff;
    }
    long double chiSquare = 4.0L * block_size * sumSq;
    return igamc(static_cast<long double>(N) / 2.0L, chiSquare / 2.0L);
}

long double runsTest(const std::vector<uint64_t> &data)
{
    std::vector<uint8_t> bits = toBits(data);
    int n = static_cast<int>(bits.size());
    int ones = 0;
    for (uint8_t b : bits)
        ones += b;
    long double pi = static_cast<long double>(ones) / n;

    // Предварительный тест: если доля единиц сильно отклонена, выходим.
    long double tau = 2.0L / std::sqrtl(static_cast<long double>(n));
    if (std::fabsl(pi - 0.5L) >= tau)
        return 0.0L;

    int V = 1;
    for (int i = 1; i < n; ++i)
    {
        if (bits[i] != bits[i - 1])
            ++V;
    }

    long double num = std::fabsl(static_cast<long double>(V) - 2.0L * n * pi * (1.0L - pi));
    long double den = 2.0L * std::sqrtl(2.0L * n) * pi * (1.0L - pi);
    return std::erfcl(num / den);
}

long double longestRunTest(const std::vector<uint64_t> &data)
{
    std::vector<uint8_t> bits = toBits(data);
    int n = static_cast<int>(bits.size());

    const int M = 128;
    int N = n / M;
    if (N < 49)
        return 0.0L;

    // NIST SP 800-22, таблица для M=128: корзины v≤4, =5, =6, =7, =8, ≥9.
    const long double piExp[6] = {0.1174L, 0.2430L, 0.2493L, 0.1752L, 0.1027L, 0.1124L};
    int counts[6] = {0};

    for (int b = 0; b < N; ++b)
    {
        int curr = 0;
        int maxRun = 0;
        for (int i = 0; i < M; ++i)
        {
            if (bits[b * M + i])
            {
                ++curr;
                if (curr > maxRun)
                    maxRun = curr;
            }
            else
            {
                curr = 0;
            }
        }
        int bucket;
        if (maxRun <= 4)
            bucket = 0;
        else if (maxRun == 5)
            bucket = 1;
        else if (maxRun == 6)
            bucket = 2;
        else if (maxRun == 7)
            bucket = 3;
        else if (maxRun == 8)
            bucket = 4;
        else
            bucket = 5;
        ++counts[bucket];
    }

    long double chiSquare = 0.0L;
    for (int i = 0; i < 6; ++i)
    {
        long double expected = N * piExp[i];
        long double diff = counts[i] - expected;
        chiSquare += (diff * diff) / expected;
    }
    return std::exp(-chiSquare / 2.0);
}

long double overlappingTemplateTest(const std::vector<uint64_t> &data, int template_size)
{
    std::vector<uint8_t> bits = toBits(data);
    int n = static_cast<int>(bits.size());

    // NIST-параметры: M=1032 бит на блок, K=5 степеней свободы.
    // Таблица piExp откалибрована под m=9 (стандартный размер шаблона по NIST).
    const int M = 1032;
    int N = n / M;
    if (N < 1 || template_size <= 0 || template_size > 63)
        return 0.0L;

    const long double piExp[6] = {0.367879L, 0.183940L, 0.137955L, 0.099634L, 0.069935L, 0.140657L};
    int counts[6] = {0};

    const uint64_t mask = (template_size == 64) ? ~0ULL : ((1ULL << template_size) - 1ULL);
    const uint64_t pattern = mask; // шаблон из template_size единиц

    for (int b = 0; b < N; ++b)
    {
        uint64_t window = 0;
        for (int i = 0; i < template_size; ++i)
            window = (window << 1) | bits[b * M + i];

        int matches = 0;
        if (window == pattern)
            ++matches;
        for (int i = template_size; i < M; ++i)
        {
            window = ((window << 1) | bits[b * M + i]) & mask;
            if (window == pattern)
                ++matches;
        }

        int bucket = matches < 5 ? matches : 5;
        ++counts[bucket];
    }

    long double chiSquare = 0.0L;
    for (int i = 0; i < 6; ++i)
    {
        long double expected = N * piExp[i];
        long double diff = counts[i] - expected;
        chiSquare += (diff * diff) / expected;
    }

    return std::erfc(std::sqrt(chiSquare / (2.0 * N)));
}