#include "hash_table.hpp"

#include <iostream>

int main()
{

    // Copy constructor and copy assignment.
    std::cout << "=== copy semantics ===\n";
    HashTable<bool> ht4(5);
    ht4.insert(8, false);
    ht4.insert(4, true);
    HashTable<bool> ht5(ht4);
    std::cout << ht4;
    std::cout << "---\n";
    std::cout << ht5;
    std::cout << "-----\n";

    ht5.insert(10, true);
    std::cout << ht5 << std::endl;
    std::cout << ht4;
    std::cout << "-------------\n";

    ht4 = ht5;
    HashTable<bool> ht6(ht4);
    std::cout << ht6 << "aaaaaaaaaaaaaaaaaa\n";

    std::cout << ht4;
    std::cout << "---\n";
    std::cout << ht5;

    ht5.insert(10, true);
    std::cout << ht4;
    std::cout << "---\n";
    std::cout << ht5;
}
