#include "utils.h"
#include "sportsman.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<Sportsman> from_csv_file(const std::string &filename)
{
    std::vector<Sportsman> data;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string line;
    std::getline(file, line); // Пропускаем заголовок
    while (std::getline(file, line))
    {
        data.emplace_back(line);
    }
    return data;
}

void to_csv_file(const std::vector<Sportsman> &data, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    file << "sport,last_name,first_name,middle_name,age,height_cm,weight_kg\n";
    for (const auto &rec : data)
    {
        file << rec.to_csv() << "\n";
    }
}

double measure_time_ms(std::function<std::vector<int>(std::vector<Sportsman> &)> find_func, const std::vector<Sportsman> &source)
{
    auto copy = source;
    auto start = std::chrono::high_resolution_clock::now();
    find_func(copy);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return time;
}
