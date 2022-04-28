#include "array.hpp"
#include <iostream>

struct X
{
    X() = default;
    X(int a, int b) : a{a}, b{b} { }
    X(const X& rhs) = default;
    X& operator=(const X& rhs) = default;
    bool operator==(const X& rhs) const { return false; }
    bool operator!=(const X& rhs) const { return false; }
    int a;
    int b;
};

std::ostream& operator<<(std::ostream& os, const X& x)
{
    std::cout << x.a;
    return os;
}

int main()
{
    Array<X, 3> arr;
    arr.at(0) = X{18, 42};
    arr.at(1) = X{35, 90};
    arr.at(2) = X{88, 20};
    std::cout << arr;
    std::cout << arr.front() << ' ' << arr.back() << '\n';
}
