#include "ds/binary_tree.hpp"
#include <iostream>

int main() {
    const auto tree = ds::BinaryTree::fromPreorder("ABD#F###CE###");
    std::cout << "Preorder : " << tree.preorder() << '\n';
    std::cout << "Inorder  : " << tree.inorder() << '\n';
    std::cout << "Postorder: " << tree.postorder() << '\n';
}
