#include "sorting.h"
#include "sportsman.h"

#include <vector>

void insertion_sort(std::vector<Sportsman> &vec)
{
    for (size_t i = 1; i < vec.size(); ++i)
    {
        Sportsman key = vec[i];
        int j = i - 1;
        while (j >= 0 && key < vec[j])
        {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void heapify(std::vector<Sportsman> &vec, size_t n, size_t i)
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && vec[left] > vec[largest])
    {
        largest = left;
    }
    if (right < n && vec[right] > vec[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        std::swap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}

void heap_sort(std::vector<Sportsman> &vec)
{
    size_t n = vec.size();
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(vec, n, i);
    }
    for (int i = n - 1; i > 0; --i)
    {
        std::swap(vec[0], vec[i]);
        heapify(vec, i, 0);
    }
}

void quick_sort(std::vector<Sportsman> &vec)
{
    if (vec.size() <= 1)
    {
        return;
    }
    Sportsman pivot = vec[vec.size() / 2];
    std::vector<Sportsman> left, right;
    for (const auto &item : vec)
    {
        if (item < pivot)
        {
            left.push_back(item);
        }
        else if (pivot < item)
        {
            right.push_back(item);
        }
    }
    quick_sort(left);
    quick_sort(right);
    vec = left;
    vec.push_back(pivot);
    vec.insert(vec.end(), right.begin(), right.end());
}