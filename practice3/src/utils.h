/**
 * @file utils.h
 * @brief Вспомогательные функции
 */

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

/**
 * @brief Измерение времени генерации выборки псевдослучайных чисел
 * @param gen_func Функция-генератор, принимающая размер выборки и возвращающая её
 * @param size Размер выборки
 * @return Время генерации (в миллисекундах)
 */
double measure_time_ms(std::function<std::vector<uint64_t>(size_t)> gen_func, size_t size);
