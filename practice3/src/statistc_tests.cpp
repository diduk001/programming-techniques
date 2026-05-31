#include "statistic_tests.h"
#include <cmath>

long double mean(const std::vector<uint64_t> &data)
{
    long double sum = 0.0;
    for (const auto &value : data)
    {
        sum += value;
    }
    return sum / data.size();
}

long double stddev(const std::vector<uint64_t> &data)
{
    long double m = mean(data);
    long double sum_squared_diff = 0.0;
    for (const auto &value : data)
    {
        sum_squared_diff += (value - m) * (value - m);
    }
    return std::sqrt(sum_squared_diff / data.size());
}

long double cv(const std::vector<uint64_t> &data)
{
    long double m = mean(data);
    if (m == 0)
    {
        return 0.0; // Избегаем деления на ноль
    }
    return stddev(data) / m;
}

long double chi_square_uniformity_test(const std::vector<uint64_t> &data, int num_bins)
{
    std::vector<uint64_t> bins(num_bins, 0);
    const uint64_t bin_size = UINT64_MAX / num_bins + 1;
    for (const auto &val : data)
    {
        uint64_t bin = val / bin_size;
        if (bin >= static_cast<uint64_t>(num_bins))
            bin = num_bins - 1;
        bins[bin]++;
    }

    long double expected = static_cast<long double>(data.size()) / num_bins;
    long double chi_square = 0.0;
    for (uint64_t count : bins)
    {
        long double diff = static_cast<long double>(count) - expected;
        chi_square += (diff * diff) / expected;
    }

    return chi_square;
}

const long double chiSquareCriticalValues[] = {
    3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.928, 18.319, 19.675,
    21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.143, 31.410, 32.671, 33.924,
    35.172, 36.415, 37.652, 38.885, 40.113, 41.337, 42.557, 43.773, 44.985, 46.194, 47.400,
    48.602, 49.802, 50.998, 52.192, 53.384, 54.572, 55.758};

bool isUniform(long double chiSquare, int num_bins)
{
    long double critical_value = chiSquareCriticalValues[num_bins - 1];
    return chiSquare < critical_value;
}