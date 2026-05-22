#include "search.h"
#include "sportsman.h"
#include "utils.h"

#include <fstream>
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
    if (sportsmen.empty())
    {
        std::cerr << "No sportsmen in input file" << std::endl;
        return 1;
    }

    const Sportsman &target = sportsmen[0];

    BinarySearchTree bst = build_bst(sportsmen);
    RedBlackTree rbt = build_rbt(sportsmen);

    unsigned int collisions = 0;
    unsigned int total_insertions = 0;
    HashTable ht = build_hash_table(sportsmen, collisions, total_insertions);

    SportsmanMultimap mmap = build_multimap(sportsmen);

    // Time only the search phase
    double linear_time = measure_time_ms(linear_search, sportsmen, target);

    double bst_time = measure_time_ms(
        [&bst](std::vector<Sportsman> &, const Sportsman &t) { return bst.search(t); },
        sportsmen, target);

    double rbt_time = measure_time_ms(
        [&rbt](std::vector<Sportsman> &, const Sportsman &t) { return rbt.search_all(t); },
        sportsmen, target);

    double hash_time = measure_time_ms(
        [&ht](std::vector<Sportsman> &, const Sportsman &t) { return ht.search(t); },
        sportsmen, target);

    double multimap_time = measure_time_ms(
        [&mmap](std::vector<Sportsman> &, const Sportsman &t) { return search_multimap(mmap, t); },
        sportsmen, target);

    std::cout << "Hash collisions: " << collisions << std::endl;
    std::cout << "Total insertions: " << total_insertions << std::endl;

    std::ofstream out(argv[2]);
    if (!out.is_open())
    {
        std::cerr << "Failed to open output file: " << argv[2] << std::endl;
        return 1;
    }
    out << "Size,LinearSearch,BinaryTreeSearch,RedBlackTreeSearch,HashTableSearch,MultimapSearch\n";
    out << sportsmen.size() << ","
        << linear_time << ","
        << bst_time << ","
        << rbt_time << ","
        << hash_time << ","
        << multimap_time << "\n";

    return 0;
}
