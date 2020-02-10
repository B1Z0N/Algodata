#include "splay.hpp"

#include <iostream>

using namespace alda;

void printin(SplayTree<int>& spt) {
    spt.in_order_traversal([](int& i) {
        std::cout << i << ' ';
    });
    std::cout << '\n';
}

void printlvl(SplayTree<int>& spt) {
    spt.breadth_first_traversal([](int& i) {
        std::cout << i << ' ';
    });
    std::cout << '\n';
}

int main() {
    SplayTree<int> spt {};
    spt.insert(2);
    printlvl(spt);
    spt.insert(3);
    printlvl(spt);
    spt.insert(4);
    printlvl(spt);
    spt.insert(1);
    printlvl(spt);
    spt.insert(5);
    printlvl(spt);

    printin(spt);

    return 0;
}