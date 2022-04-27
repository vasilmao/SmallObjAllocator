#include "Allocator.hpp"
#include <iostream>

struct Node {
    int a = 3;
    int b = 4;
};

struct A {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
};

int main() {
    Node* node = Allocator<Node>::Allocate();
    Node* node2 = Allocator<Node>::Allocate();

    A* ptr = Allocator<A>::Allocate();

    std::cout << node << "\n";

    node->a = 5;
    node->b = 6;

    Allocator<Node>::Deallocate(node);

    node = Allocator<Node>::Allocate();
    std::cout << node;

    Allocator<bool>::Deallocate(Allocator<bool>::Allocate());

    Allocator<Node>::Deallocate(node);
    Allocator<Node>::Deallocate(node2);

    Allocator<A>::Deallocate(ptr);

    std::vector<Node*> v;
    for (size_t i = 0; i < 1000000; ++i) {
        v.push_back(Allocator<Node>::Allocate());
    }

    for (size_t i = 0; i < v.size(); ++i) {
        Allocator<Node>::Deallocate(v[i]);
    }

}