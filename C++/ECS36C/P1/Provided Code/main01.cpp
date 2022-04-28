#include "array.hpp"
#include <iostream>

int main()
{
    Array<bool, 5> vals;
    std::cout << vals.size() << '\n';
}
