/**
 * @file utils.h
 * @brief Вспомогательные функции
 */

#pragma once

#include "sportsman.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Прочитать вектор спортсменов из CSV файла
 * @param filename Путь к входному файлу
 * @return Вектор Sportsman
 */
std::vector<Sportsman> from_csv_file(const std::string &filename);

/**
 * @brief Записать вектор спортсменов в CSV-файл
 * @param data Вектор Sportsman
 * @param filename Путь к выходному файлу
 */
void to_csv_file(const std::vector<Sportsman> &data, const std::string &filename);

/**
 * @brief Измерение времени сортировки
 * @param sort_func Функция сортировки (void(std::vector<Sportsman>&))
 * @param source Вектор спортсменов для сортировки
 * @return Время сортировки (в миллисекундах)
 */
double measure_time_ms(std::function<void(std::vector<Sportsman> &)> sort_func, const std::vector<Sportsman> &source);