#include "ds/threaded_binary_tree.hpp"
#include <iostream>

int main() {
    const auto tree = ds::ThreadedBinaryTree::fromPreorder("ABC##DE#G##F###");
    std::cout << "Threaded inorder: " << tree.inorder() << '\n';
}
