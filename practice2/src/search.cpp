/**
 * @file search.cpp
 * @brief Реализация методов поиска спортсменов в массиве
 */

#include "search.h"
#include "sportsman.h"

#include <map>
#include <vector>

std::vector<int> linear_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target)
{
    std::vector<int> indices;
    for (size_t i = 0; i < sportsmen.size(); ++i)
    {
        if (sportsmen[i] == target)
        {
            indices.push_back(i);
        }
    }
    return indices;
}

/**
 * @struct BSTNode
 * @brief Узел двоичного дерева поиска
 */
struct BSTNode
{
    Sportsman value;   /**< Значение узла */
    int originalIndex; /**< Индекс в исходном массиве */
    BSTNode *left;     /**< Указатель на левое поддерево */
    BSTNode *right;    /**< Указатель на правое поддерево */

    /**
     * @brief Конструктор, который инициализирует узел на основе спортсмена и его индекса
     * @param[val] Спортсмен для хранения в узле
     * @param[idx] Индекс спортсмена в исходном массиве
     */
    BSTNode(const Sportsman &val, int idx) : value(val), originalIndex(idx), left(nullptr), right(nullptr) {}
};

/**
 * @struct BinarySearchTree
 * @brief Двоичное дерево поиска
 */
struct BinarySearchTree
{
    BSTNode *root; /**< Корень дерева */

    /**
     * @brief Конструктор, который инициализирует пустое дерево
     */
    BinarySearchTree() : root(nullptr) {}

    /**
     * @brief Вставляет спортсмена в дерево с сохранением индекса из исходного массива
     * @param[value] Спортсмен для вставки
     * @param[index] Индекс спортсмена в исходном массиве
     */
    void insert(const Sportsman &value, int index)
    {
        root = insertRec(root, value, index);
    }

    /**
     * @brief Рекурсивная функция для вставки спортсмена в дерево
     * @param[node] Узел дерева для вставки
     * @param[value] Спортсмен для вставки
     * @param[index] Индекс спортсмена в исходном массиве
     * @return Указатель на узел после вставки
     */
    BSTNode *insertRec(BSTNode *node, const Sportsman &value, int index)
    {
        if (node == nullptr)
        {
            return new BSTNode(value, index);
        }
        if (value < node->value)
        {
            node->left = insertRec(node->left, value, index);
        }
        else
        {
            node->right = insertRec(node->right, value, index);
        }
        return node;
    }

    /**
     * @brief Ищет спортсмена в дереве
     * @param[target] Спортсмен для поиска
     * @param[indices] Вектор для хранения индексов найденных спортсменов
     */
    void search(const Sportsman &target, std::vector<int> &indices)
    {
        searchRec(root, target, indices);
    }

    /**
     * @brief Рекурсивная функция для поиска спортсмена в дереве
     * @param[node] Узел дерева для поиска
     * @param[target] Спортсмен для поиска
     * @param[indices] Вектор для хранения индексов найденных спортсменов
     */
    void searchRec(BSTNode *node, const Sportsman &target, std::vector<int> &indices)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->value == target)
        {
            indices.push_back(node->originalIndex);
        }
        searchRec(node->left, target, indices);
        searchRec(node->right, target, indices);
    }
};

std::vector<int> binary_tree_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target)
{
    BinarySearchTree bst;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
    {
        bst.insert(sportsmen[i], i);
    }
    std::vector<int> indices;
    bst.search(target, indices);
    return indices;
}