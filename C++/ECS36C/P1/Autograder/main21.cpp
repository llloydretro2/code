#include "array.hpp"
#include <iostream>

int main()
{
    Array<char, 5> a;
    get<0>(a) = 'A';
    get<1>(a) = 'B';
    get<2>(a) = 'C';
    get<3>(a) = 'D';
    get<4>(a) = 'E';
    get<5>(a) = 'F';
    std::cout << a;
}
