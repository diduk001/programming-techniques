/**
 * @file prng.h
 * @brief Объявление методов для проведения тестов над случайными выборками:
 * frequencyTest, blockFrequencyTest, runsTest, longestRunTest, overlappingTemplateTest
 */
#pragma once

#include <cstdint>
#include <vector>

/**
 * @brief Проведение теста на частоту единиц в последовательности
 * @param data Вектор с данными выборки
 * @return p-значение для теста на частоту единиц
 */
long double frequencyTest(const std::vector<uint64_t> &data);

/**
 * @brief Проведение теста на частоту блоков в последовательности
 * @param data Вектор с данными выборки
 * @param block_size Размер блока для теста
 * @return p-значение для теста на частоту блоков
 */
long double blockFrequencyTest(const std::vector<uint64_t> &data, int block_size);

/**
 * @brief Проведение теста на количество серий в последовательности
 * @param data Вектор с данными выборки
 * @return p-значение для теста на количество серий
 */
long double runsTest(const std::vector<uint64_t> &data);

/**
 * @brief Проведение теста на длину самой длинной серии в последовательности
 * @param data Вектор с данными выборки
 * @return p-значение для теста на длину самой длинной серии
 */
long double longestRunTest(const std::vector<uint64_t> &data);

/**
 * @brief Проведение теста на перекрывающиеся шаблоны в последовательности
 * @param data Вектор с данными выборки
 * @param template_size Размер шаблона для теста
 * @return p-значение для теста на перекрывающиеся шаблоны
 */
long double overlappingTemplateTest(const std::vector<uint64_t> &data, int template_size);