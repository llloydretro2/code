#include "array.hpp"
#include <iostream>

int main()
{
    Array<int, 4> vals;
    vals.at(0) = 20;
    vals.at(1) = 30;
    vals.at(2) = 40;
    vals.at(3) = 50;
    std::cout << vals;
    vals.at(1) = 100;
    std::cout << vals;
}
