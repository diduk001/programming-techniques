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
    for (const auto &val : data) {
        uint64_t bin = val / bin_size;
        if (bin >= static_cast<uint64_t>(num_bins)) bin = num_bins - 1;
        bins[bin]++;
    }

    long double expected = static_cast<long double>(data.size()) / num_bins;
    long double chi_square = 0.0;
    for (uint64_t count : bins) {
        long double diff = static_cast<long double>(count) - expected;
        chi_square += (diff * diff) / expected;
    }

    return chi_square;
}

long double chi_square_randomness_test(const std::vector<uint64_t> &data, int num_bins)
{
    if (data.size() < 2) return 0.0;

    std::vector<uint64_t> bins(num_bins, 0);
    const uint64_t total = data.size() - 1;
    const uint64_t bin_size = UINT64_MAX / num_bins + 1;

    for (size_t i = 0; i + 1 < data.size(); ++i)
    {
        // Объединяем верхние 32 бита двух соседних значений в одно 64-битное число
        uint64_t pair_value = (data[i] & 0xFFFFFFFF00000000ULL) | (data[i + 1] >> 32);
        uint64_t bin = pair_value / bin_size;
        if (bin >= static_cast<uint64_t>(num_bins)) bin = num_bins - 1;
        bins[bin]++;
    }

    long double expected = static_cast<long double>(total) / num_bins;
    long double chi_square_statistic = 0.0;

    for (int i = 0; i < num_bins; ++i)
    {
        long double diff = static_cast<long double>(bins[i]) - expected;
        chi_square_statistic += (diff * diff) / expected;
    }

    return chi_square_statistic;
}
