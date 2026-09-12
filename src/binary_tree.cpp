#include "ds/binary_tree.hpp"

#include <stdexcept>

namespace ds {

BinaryTree BinaryTree::fromPreorder(const std::string& encoded, char null_marker) {
    BinaryTree tree;
    std::size_t index = 0;
    tree.root_ = parse(encoded, index, null_marker);
    if (index != encoded.size()) {
        throw std::invalid_argument("preorder encoding contains trailing data");
    }
    return tree;
}

std::unique_ptr<BinaryTree::Node> BinaryTree::parse(const std::string& encoded,
                                                    std::size_t& index,
                                                    char null_marker) {
    if (index >= encoded.size()) {
        throw std::invalid_argument("incomplete preorder encoding");
    }

    const char value = encoded[index++];
    if (value == null_marker) {
        return nullptr;
    }

    auto node = std::make_unique<Node>(value);
    node->left = parse(encoded, index, null_marker);
    node->right = parse(encoded, index, null_marker);
    return node;
}

void BinaryTree::preorder(const Node* node, std::string& out) {
    if (!node) return;
    out.push_back(node->value);
    preorder(node->left.get(), out);
    preorder(node->right.get(), out);
}

void BinaryTree::inorder(const Node* node, std::string& out) {
    if (!node) return;
    inorder(node->left.get(), out);
    out.push_back(node->value);
    inorder(node->right.get(), out);
}

void BinaryTree::postorder(const Node* node, std::string& out) {
    if (!node) return;
    postorder(node->left.get(), out);
    postorder(node->right.get(), out);
    out.push_back(node->value);
}

std::string BinaryTree::preorder() const {
    std::string out;
    preorder(root_.get(), out);
    return out;
}

std::string BinaryTree::inorder() const {
    std::string out;
    inorder(root_.get(), out);
    return out;
}

std::string BinaryTree::postorder() const {
    std::string out;
    postorder(root_.get(), out);
    return out;
}

}  // namespace ds
