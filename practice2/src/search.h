/**
 * @file search.h
 * @brief Объявление методов поиска спортсменов в массиве
 */

#pragma once

#include "sportsman.h"
#include <map>
#include <vector>

// ─── Линейный поиск ───────────────────────────────────────────────────────────

/**
 * @brief Линейный поиск всех вхождений target в массиве
 * @param sportsmen Исходный массив
 * @param target Искомый спортсмен
 * @return Индексы всех найденных вхождений
 */
std::vector<int> linear_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target);

// ─── Двоичное дерево поиска ───────────────────────────────────────────────────

/**
 * @struct BSTNode
 * @brief Узел двоичного дерева поиска
 */
struct BSTNode
{
    Sportsman value;   /**< Значение узла */
    int originalIndex; /**< Индекс в исходном массиве */
    BSTNode *left;     /**< Левое поддерево */
    BSTNode *right;    /**< Правое поддерево */

    BSTNode(const Sportsman &val, int idx);
};

/**
 * @struct BinarySearchTree
 * @brief Двоичное дерево поиска
 */
struct BinarySearchTree
{
    BSTNode *root;

    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &) = delete;
    BinarySearchTree &operator=(const BinarySearchTree &) = delete;
    BinarySearchTree(BinarySearchTree &&other) noexcept;
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
    ~BinarySearchTree();

    void insert(const Sportsman &value, int index);
    std::vector<int> search(const Sportsman &target) const;

private:
    BSTNode *insertRec(BSTNode *node, const Sportsman &value, int index);
    void searchRec(BSTNode *node, const Sportsman &target, std::vector<int> &indices) const;
    static void destroy(BSTNode *node);
};

/**
 * @brief Строит двоичное дерево поиска из массива спортсменов
 * @param sportsmen Исходный массив
 * @return Построенное дерево
 */
BinarySearchTree build_bst(const std::vector<Sportsman> &sportsmen);

// ─── Красно-чёрное дерево ─────────────────────────────────────────────────────

/**
 * @enum RBColor
 * @brief Цвет узла красно-чёрного дерева
 */
enum class RBColor { RED, BLACK };

/**
 * @struct RBNode
 * @brief Узел красно-чёрного дерева
 */
struct RBNode
{
    Sportsman value;   /**< Значение узла */
    int originalIndex; /**< Индекс в исходном массиве */
    RBColor color;     /**< Цвет узла */
    RBNode *left;      /**< Левое поддерево */
    RBNode *right;     /**< Правое поддерево */
    RBNode *parent;    /**< Родительский узел */

    RBNode(const Sportsman &val, int idx);
};

/**
 * @struct RedBlackTree
 * @brief Красно-чёрное дерево
 */
struct RedBlackTree
{
    RBNode *root;

    RedBlackTree();
    RedBlackTree(const RedBlackTree &) = delete;
    RedBlackTree &operator=(const RedBlackTree &) = delete;
    RedBlackTree(RedBlackTree &&other) noexcept;
    RedBlackTree &operator=(RedBlackTree &&other) noexcept;
    ~RedBlackTree();

    void insert(const Sportsman &value, int index);
    std::vector<int> search_all(const Sportsman &target) const;

private:
    void rotate_left(RBNode *x);
    void rotate_right(RBNode *y);
    void fix_insert(RBNode *z);
    void search_all_rec(RBNode *node, const Sportsman &target, std::vector<int> &result) const;
    static void destroy(RBNode *node);
};

/**
 * @brief Строит красно-чёрное дерево из массива спортсменов
 * @param sportsmen Исходный массив
 * @return Построенное дерево
 */
RedBlackTree build_rbt(const std::vector<Sportsman> &sportsmen);

// ─── Хеш-таблица ─────────────────────────────────────────────────────────────

/**
 * @struct HashTable
 * @brief Хеш-таблица с разрешением коллизий методом цепочек
 */
struct HashTable
{
    static constexpr int TABLE_SIZE = 65536;
    std::vector<std::vector<std::pair<Sportsman, int>>> buckets;
    unsigned int collisions_cnt;
    unsigned int total_insertions;

    HashTable();

    void insert(const Sportsman &value, int index);
    std::vector<int> search(const Sportsman &target) const;
};

/**
 * @brief Строит хеш-таблицу из массива спортсменов
 * @param sportsmen Исходный массив
 * @param collisions Число коллизий (выходной параметр)
 * @param total_insertions Общее число вставок (выходной параметр)
 * @return Построенная хеш-таблица
 */
HashTable build_hash_table(const std::vector<Sportsman> &sportsmen,
                            unsigned int &collisions,
                            unsigned int &total_insertions);

// ─── Ассоциативный массив ─────────────────────────────────────────────────────

using SportsmanMultimap = std::multimap<Sportsman, int>;

/**
 * @brief Строит ассоциативный массив из вектора спортсменов
 * @param sportsmen Исходный массив
 * @return Построенный ассоциативный массив
 */
SportsmanMultimap build_multimap(const std::vector<Sportsman> &sportsmen);

/**
 * @brief Поиск всех вхождений target в ассоциативном массиве
 * @param mmap Ассоциативный массив
 * @param target Искомый спортсмен
 * @return Индексы всех найденных вхождений
 */
std::vector<int> search_multimap(const SportsmanMultimap &mmap, const Sportsman &target);
