#include "sorting.h"
#include "sportsman.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::vector<Sportsman> sportsmen = from_csv_file(argv[1]);

    std::vector<Sportsman> sportsmen_insertion_sort = sportsmen;
    double insertion_sort_time = measure_time_ms(insertion_sort, sportsmen_insertion_sort);

    std::vector<Sportsman> sportsmen_heap_sort = sportsmen;
    double heap_sort_time = measure_time_ms(heap_sort, sportsmen_heap_sort);

    std::vector<Sportsman> sportsmen_quick_sort = sportsmen;
    double quick_sort_time = measure_time_ms(quick_sort, sportsmen_quick_sort);

    std::vector<Sportsman> sportsmen_std_sort = sportsmen;
    double std_sort_time = measure_time_ms([](std::vector<Sportsman> &vec)
                                           { std::sort(vec.begin(), vec.end()); }, sportsmen_std_sort);

    for (int i = 0; i < sportsmen.size(); ++i)
    {
        if (sportsmen_insertion_sort[i] != sportsmen_heap_sort[i] ||
            sportsmen_insertion_sort[i] != sportsmen_quick_sort[i] ||
            sportsmen_insertion_sort[i] != sportsmen_std_sort[i])
        {
            std::cerr << "Sorting algorithms produced different results!" << std::endl;
            return 1;
        }
    }

    std::cout << "Insertion Sort Time (ms): " << insertion_sort_time << std::endl;
    std::cout << "Heap Sort Time (ms): " << heap_sort_time << std::endl;
    std::cout << "Quick Sort Time (ms): " << quick_sort_time << std::endl;
    std::cout << "std::sort Time (ms): " << std_sort_time << std::endl;

    return 0;
}