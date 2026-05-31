/**
 * @file statistic_tests.h
 * @brief Объявление методов для проведения статистических тестов над случайными выборками:
 * среднее, отклонение, коэффициент вариации, тест на равномерность и случайность с помощью критерия
 * Хи-квадрат
 */
#pragma once

#include <cstdint>
#include <vector>

/**
 * @brief Вычисление среднего значения выборки
 * @param data Вектор с данными выборки
 * @return Среднее значение выборки
 */
long double mean(const std::vector<uint64_t> &data);

/**
 * @brief Вычисление стандартного отклонения выборки
 * @param data Вектор с данными выборки
 * @return Стандартное отклонение выборки
 */
long double stddev(const std::vector<uint64_t> &data);

/**
 * @brief Вычисление коэффициента вариации выборки
 * @param data Вектор с данными выборки
 * @return Коэффициент вариации выборки
 */
long double cv(const std::vector<uint64_t> &data);

/**
 * @brief Проведение теста на равномерность выборки с помощью критерия Хи-квадрат
 * @param data Вектор с данными выборки
 * @param num_bins Количество интервалов (корзин) для разбиения данных
 * @return Значение статистики Хи-квадрат для теста на равномерность
 */
long double chi_square_uniformity_test(const std::vector<uint64_t> &data, int num_bins);

/**
 * @brief Проверить, соответствует ли выборка распределению, близкому к равномерному
 * @param chiSquare Значение статистики Хи-квадрат
 * @param num_bins Количество интервалов (корзин) для разбиения данных
 * @return true, если выборка соответствует равномерному распределению, иначе false
 */
bool isUniform(long double chiSquare, int num_bins);