/**
 * @file search.cpp
 * @brief Реализация методов поиска спортсменов в массиве
 */

#include "search.h"
#include "sportsman.h"

#include <vector>

// ─── Линейный поиск ───────────────────────────────────────────────────────────

std::vector<int> linear_search(const std::vector<Sportsman> &sportsmen, const Sportsman &target)
{
    std::vector<int> indices;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
    {
        if (sportsmen[i] == target)
            indices.push_back(i);
    }
    return indices;
}

// ─── Двоичное дерево поиска ───────────────────────────────────────────────────

BSTNode::BSTNode(const Sportsman &val, int idx)
    : value(val), originalIndex(idx), left(nullptr), right(nullptr) {}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept : root(other.root)
{
    other.root = nullptr;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept
{
    if (this != &other)
    {
        destroy(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

BinarySearchTree::~BinarySearchTree()
{
    destroy(root);
}

void BinarySearchTree::destroy(BSTNode *node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

BSTNode *BinarySearchTree::insertRec(BSTNode *node, const Sportsman &value, int index)
{
    if (!node)
        return new BSTNode(value, index);
    if (value < node->value)
        node->left = insertRec(node->left, value, index);
    else
        node->right = insertRec(node->right, value, index);
    return node;
}

void BinarySearchTree::insert(const Sportsman &value, int index)
{
    root = insertRec(root, value, index);
}

void BinarySearchTree::searchRec(BSTNode *node, const Sportsman &target, std::vector<int> &indices) const
{
    if (!node)
        return;
    if (node->value == target)
    {
        indices.push_back(node->originalIndex);
    }
    else if (node->value > target)
    {
        searchRec(node->left, target, indices);
    }
    else
    {
        searchRec(node->right, target, indices);
    }
}

std::vector<int> BinarySearchTree::search(const Sportsman &target) const
{
    std::vector<int> indices;
    searchRec(root, target, indices);
    return indices;
}

BinarySearchTree build_bst(const std::vector<Sportsman> &sportsmen)
{
    BinarySearchTree bst;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
        bst.insert(sportsmen[i], i);
    return bst;
}

// ─── Красно-чёрное дерево ─────────────────────────────────────────────────────

RBNode::RBNode(const Sportsman &val, int idx)
    : value(val), originalIndex(idx), color(RBColor::RED), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::RedBlackTree(RedBlackTree &&other) noexcept : root(other.root)
{
    other.root = nullptr;
}

RedBlackTree &RedBlackTree::operator=(RedBlackTree &&other) noexcept
{
    if (this != &other)
    {
        destroy(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

RedBlackTree::~RedBlackTree()
{
    destroy(root);
}

void RedBlackTree::destroy(RBNode *node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void RedBlackTree::rotate_left(RBNode *x)
{
    if (!x || !x->right)
        return;
    RBNode *y = x->right;
    x->right = y->left;
    if (x->right)
        x->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotate_right(RBNode *y)
{
    if (!y || !y->left)
        return;
    RBNode *x = y->left;
    y->left = x->right;
    if (y->left)
        y->left->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void RedBlackTree::fix_insert(RBNode *z)
{
    while (z != root && z->parent->color == RBColor::RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode *y = z->parent->parent->right;
            if (y && y->color == RBColor::RED)
            {
                z->parent->color = RBColor::BLACK;
                y->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotate_left(z);
                }
                z->parent->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                rotate_right(z->parent->parent);
            }
        }
        else
        {
            RBNode *y = z->parent->parent->left;
            if (y && y->color == RBColor::RED)
            {
                z->parent->color = RBColor::BLACK;
                y->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotate_right(z);
                }
                z->parent->color = RBColor::BLACK;
                z->parent->parent->color = RBColor::RED;
                rotate_left(z->parent->parent);
            }
        }
    }
    root->color = RBColor::BLACK;
}

void RedBlackTree::insert(const Sportsman &value, int index)
{
    RBNode *z = new RBNode(value, index);
    RBNode *y = nullptr;
    RBNode *x = root;

    while (x)
    {
        y = x;
        if (value < x->value)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (value < y->value)
        y->left = z;
    else
        y->right = z;

    fix_insert(z);
}

void RedBlackTree::search_all_rec(RBNode *node, const Sportsman &target, std::vector<int> &result) const
{
    if (!node)
        return;
    if (node->value == target)
    {
        result.push_back(node->originalIndex);
        search_all_rec(node->right, target, result);
    }
    else if (target < node->value)
        search_all_rec(node->left, target, result);
    else
        search_all_rec(node->right, target, result);
}

std::vector<int> RedBlackTree::search_all(const Sportsman &target) const
{
    std::vector<int> result;
    search_all_rec(root, target, result);
    return result;
}

RedBlackTree build_rbt(const std::vector<Sportsman> &sportsmen)
{
    RedBlackTree rbt;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
        rbt.insert(sportsmen[i], i);
    return rbt;
}

// ─── Хеш-таблица ─────────────────────────────────────────────────────────────

static unsigned short hash_sportsman(const Sportsman &value)
{
    unsigned short result = 0;
    for (char c : value.full_name.first_name)
        result = result * 31 + c;
    for (char c : value.full_name.last_name)
        result = result * 35 + c;
    for (char c : value.full_name.middle_name)
        result = result * 39 + c;
    return result;
}

HashTable::HashTable() : buckets(TABLE_SIZE), collisions_cnt(0), total_insertions(0) {}

void HashTable::insert(const Sportsman &value, int index)
{
    unsigned int hash_value = hash_sportsman(value);
    auto &bucket = buckets[hash_value];
    bucket.emplace_back(value, index);
    total_insertions++;
    for (int i = 0; i < (int)bucket.size() - 1; ++i)
    {
        if (bucket[i].first != value)
        {
            collisions_cnt++;
            break;
        }
    }
}

std::vector<int> HashTable::search(const Sportsman &target) const
{
    std::vector<int> result;
    for (const auto &entry : buckets[hash_sportsman(target)])
    {
        if (entry.first == target)
            result.push_back(entry.second);
    }
    return result;
}

HashTable build_hash_table(const std::vector<Sportsman> &sportsmen,
                           unsigned int &collisions,
                           unsigned int &total_insertions)
{
    HashTable ht;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
        ht.insert(sportsmen[i], i);
    collisions = ht.collisions_cnt;
    total_insertions = ht.total_insertions;
    return ht;
}

// ─── Ассоциативный массив ─────────────────────────────────────────────────────

SportsmanMultimap build_multimap(const std::vector<Sportsman> &sportsmen)
{
    SportsmanMultimap mmap;
    for (int i = 0; i < (int)sportsmen.size(); ++i)
        mmap.insert({sportsmen[i], i});
    return mmap;
}

std::vector<int> search_multimap(const SportsmanMultimap &mmap, const Sportsman &target)
{
    std::vector<int> indices;
    auto range = mmap.equal_range(target);
    for (auto it = range.first; it != range.second; ++it)
        indices.push_back(it->second);
    return indices;
}
