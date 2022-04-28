#include "array.hpp"
#include <iostream>

int main()
{
    Array<int, 0> vals;
    std::cout << vals.size() << '\n';
}
