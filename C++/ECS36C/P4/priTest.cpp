#include "priority_queue.hpp"

#include <iostream>

int main()
{
    // Basic operations, including insert().
    PriorityQueue<std::string> p1(20);
    std::cout << p1;
    std::cout<<"ash"<<std::endl;
    p1.insert(10, "AA");
    std::cout << p1 << '\n';

}
