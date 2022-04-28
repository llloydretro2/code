/**
 * numElements()??
 */

#include "priority_queue.hpp"
#include <iostream>

int main() {
    std::cout << "Test insertiong first." << std::endl;
    PriorityQueue<std::string> p1(9);
    p1.insert(100, "Ben Morris");
    p1.insert(97, "Zhaojun Bai");
    p1.insert(80, "Thomas Weideman");
    p1.insert(40, "Aaron Kaloti");
    p1.insert(200, "Mathew Butner");
    p1.insert(1000, "Sam Blitz");
    p1.insert(4, "John Chanellor");
    p1.insert(30, "Jiaming Jiang");
    p1.insert(2, "Daryl Posnett");
    std::cout << "Should print 0 since the size can't go beyond 9." << std::endl;
    std::cout << p1.insert(9000, "Chris Nitta") << std::endl;
    std::cout << p1;
    std::cout << "Test for copy constructor" << std::endl;
    auto p2 = p1;
    std::cout << "Test for operator=" << std::endl;
    p2 = p1;
    std::cout << p2.maxSize() << std::endl;
    std::cout << p2.numElements() << std::endl;
    std::cout << p2;
    std::cout << "Testing getMin Operations" << std::endl;
    std::cout << *(p2.getMinKey()) << std::endl;
    std::cout << *(p2.getMinValue()) << std::endl;
    std::cout << "Testing delete Operations and deleteMin" << std::endl;
    std::cout << p1.deleteMin() << std::endl;
    std::cout << p2;
    std::cout << p2.remove(2) << std::endl;
    std::cout << p2;
    /*
    PriorityQueue<std::string> p3(10000);
    std::cout << p3.deleteMin() << std::endl;
    std::cout << p1;
    std::cout << "P1 and p2 should be the same. Check manually" << std::endl;
    std::cout << p2;
    std::cout << "Print p3, altough it doesn't give us anything" << std::endl;
    std::cout << p3;
    std::cout << "Check decrease and increase key operation."  << std::endl;
    std::cout << p1.decreaseKey(1000, 999) << std::endl;
    std::cout << p2.increaseKey(30, 10000) << std::endl;
    std::cout << p1;
    std::cout << "Separate p1 and p2" << std::endl;
    std::cout << p2;
    std::cout << "Testing get method. Also update the heap" << std::endl;
    std::cout << (p1.get(1000) == nullptr) << std::endl;
    std::cout << (p2.get(30) == nullptr) << std::endl;
    std::cout << (p2.get(10030) == nullptr) << std::endl;
    std::cout << "Do a update by ourself" << std::endl;
    std::cout << "Get the professor with key of 4 " <<*(p1.get(4)) << std::endl;
    *(p1.get(4)) = "Zhan Zhang";
    std::cout << p1;
    std::cout << "I will use an empty object to test our operations. It should give you 1s" << std::endl;
    std::cout << (p3.getMinKey() == nullptr) << std::endl;
    std::cout << (p3.getMinValue() == nullptr) << std::endl;
    std::cout << (!p3.deleteMin()) << std::endl;
    std::cout << (p3.get(8) == nullptr) << std::endl;
    std::cout << (!p3.decreaseKey(9 , 1)) << std::endl;
    std::cout << (!p3.increaseKey(8 , 1)) << std::endl;
    std::cout << (!p3.remove(10)) << std::endl;
    p3 = p2;
    std::cout << "Clean up heap" << std::endl;
    while (p1.numElements() > 0) {
        p1.deleteMin();
    }
    p2.remove(40);
    p2.remove(30);
    p2.remove(4);
    p2.remove(100);
    p2.remove(1000);
    p2.remove(97);
    p2.remove(80);
    p2.remove(200);
    p2.remove(10030);
    std::cout << "Shouldn't print anything and goes straight to that's all." << std::endl;
    std::cout << p1;
    std::cout << p2;
    p3 = p2;
    std::cout << p3;
    std::cout << "That's all for my_test" << std::endl;
    return 0;*/
}
