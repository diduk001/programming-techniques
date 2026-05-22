/**
 * @file search.h
 * @brief Объявление методов поиска спортсменов в массиве
 */

#pragma once

#include "sportsman.h"
#include <vector>

std::vector<int> linear_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target);

std::vector<int> binary_tree_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target);

std::vector<int> red_black_tree_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target);

std::vector<int> hash_table_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target, unsigned int &collisions, unsigned int &total_insertions);

std::vector<int> multimap_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target);
