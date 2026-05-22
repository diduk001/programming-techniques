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

/*
 * @enum Color
 * @brief Цвет узла в красно-черном дереве
 */
enum Color
{
    RED,  /**< Красный цвет узла */
    BLACK /**< Черный цвет узла */
};

/**
 * @struct RBNode
 * @brief Узел красно-черного дерева
 */
struct RBNode
{
    Sportsman value;   /**< Значение узла */
    int originalIndex; /**< Индекс спортсмена в исходном массиве */
    Color color;       /**< Цвет узла */
    RBNode *left;      /**< Указатель на левое поддерево */
    RBNode *right;     /**< Указатель на правое поддерево */
    RBNode *parent;    /**< Указатель на родителя */

    /**
     * @brief Конструктор, который инициализирует узел на основе спортсмена
     * @param[val] Спортсмен для хранения в узле
     */
    RBNode(const Sportsman &val, int idx)
        : value(val), originalIndex(idx), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

/**
 * @class RedBlackTree
 * @brief Красно-черное дерево
 */
struct RedBlackTree
{
    RBNode *root; /**< Корень дерева */

    /**
     * @brief Конструктор, который инициализирует пустое дерево
     */
    RedBlackTree() : root(nullptr) {}

    /**
     * @brief Вставляет спортсмена в красно-черное дерево
     * @param[value] Спортсмен для вставки
     */
    void insert(const Sportsman &value, int index)
    {
        RBNode *z = new RBNode(value, index);
        RBNode *y = nullptr;
        RBNode *x = root;

        while (x)
        {
            y = x;
            if (value < x->value)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;
        if (!y)
        {
            root = z;
        }
        else if (value < y->value)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        fix_insert(z);
    }

    /**
     * @brief Поворачивает узел влево
     * @param[x] Узел для поворота
     */
    void rotate_left(RBNode *x)
    {
        if (!x || !x->right)
            return;
        RBNode *y = x->right;
        x->right = y->left;
        if (x->right)
            x->right->parent = x;
        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    /**
     * @brief Поворачивает узел вправо
     * @param[y] Узел для поворота
     */
    void rotate_right(RBNode *y)
    {
        if (!y || !y->left)
            return;
        RBNode *x = y->left;
        y->left = x->right;
        if (y->left)
            y->left->parent = y;
        x->parent = y->parent;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    /**
     * @brief Исправляет дерево после вставки узла
     * @param[z] Вставленный узел, который может нарушать свойства красно-черного дерева
     */
    void fix_insert(RBNode *z)
    {
        while (z != root && z->parent->color == Color::RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode *y = z->parent->parent->right;
                if (y && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotate_right(z->parent->parent);
                }
            }
            else
            {
                RBNode *y = z->parent->parent->left;
                if (y && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    /**
     * @brief Ищет спортсмена в поддереве, начиная с данного узла
     * @param[target] Спортсмен для поиска
     * @param[result] Вектор индексов найденных спортсменов, равных target
     */
    void search_all(RBNode *node, const Sportsman &target, std::vector<int> &result) const
    {
        if (!node)
            return;

        if (node->value == target)
        {
            result.push_back(node->originalIndex);
            search_all(node->right, target, result);
        }
        else if (target < node->value)
        {
            search_all(node->left, target, result);
        }
        else
        {
            search_all(node->right, target, result);
        }
    }
};

std::vector<int> red_black_tree_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target)
{
    RedBlackTree rbt;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
    {
        rbt.insert(sportsmen[i], i);
    }
    std::vector<int> indices;
    rbt.search_all(rbt.root, target, indices);
    return indices;
}