#include "array.hpp"
#include <iostream>

int main()
{
    Array<int, 4> arr;
    for (unsigned i = 0; i < 4; ++i)
        arr.at(i) = i * 15;
    std::cout << get<0>(arr) << '\n';
    std::cout << get<1>(arr) << '\n';
    std::cout << get<2>(arr) << '\n';
    std::cout << get<3>(arr) << '\n';
    get<2>(arr) = 100;
    const auto& ref = arr;
    std::cout << get<0>(ref) << '\n';
    std::cout << get<1>(ref) << '\n';
    std::cout << get<2>(ref) << '\n';
    std::cout << get<3>(ref) << '\n';
}
