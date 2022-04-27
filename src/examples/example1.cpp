#include <iostream>

#include "FixedAllocator.hpp"

struct Node {
    int a = 3;
    int b = 4;
};

int main() {
    FixedAllocator a{sizeof(Node)};
    Node* node = (Node*)a.Allocate();

    std::cout << node << "\n";

    node->a = 5;
    node->b = 6;

    a.Deallocate(node);

    node = (Node*)a.Allocate();
    std::cout << node;

}