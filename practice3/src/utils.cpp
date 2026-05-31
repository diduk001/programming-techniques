#include "utils.h"

double measure_time_ms(std::function<std::vector<uint64_t>(size_t)> gen_func, size_t size)
{
    auto start = std::chrono::high_resolution_clock::now();
    gen_func(size);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return time;
}
