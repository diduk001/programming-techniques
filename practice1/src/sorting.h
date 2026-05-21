/**
 * @file sorting.h
 * @brief Объявления алгоритмов сортировки
 */

#pragma once

#include "sportsman.h"
#include <vector>

/**
 * @brief Сортировка простыми вставками
 * @param vec Ссылка на вектор для сортировки
 */
void insertion_sort(std::vector<Sportsman>& vec);

/**
 * @brief Пирамидальная сортировка
 * @param vec Ссылка на вектор для сортировки
 */
void heap_sort(std::vector<Sportsman>& vec);

/**
 * @brief Быстрая сортировка
 * @param vec Ссылка на вектор для сортировки
 */
void quick_sort(std::vector<Sportsman>& vec);
