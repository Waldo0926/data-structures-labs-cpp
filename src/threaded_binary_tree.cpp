#include "ds/threaded_binary_tree.hpp"

#include <stdexcept>

namespace ds {

ThreadedBinaryTree ThreadedBinaryTree::fromPreorder(const std::string& encoded,
                                                     char null_marker) {
    ThreadedBinaryTree tree;
    std::size_t index = 0;
    tree.root_ = tree.parse(encoded, index, null_marker);
    if (index != encoded.size()) {
        throw std::invalid_argument("preorder encoding contains trailing data");
    }

    Node* previous = nullptr;
    tree.threadInorder(tree.root_, previous);
    return tree;
}

ThreadedBinaryTree::Node* ThreadedBinaryTree::makeNode(char value) {
    nodes_.push_back(std::make_unique<Node>(value));
    return nodes_.back().get();
}

ThreadedBinaryTree::Node* ThreadedBinaryTree::parse(const std::string& encoded,
                                                     std::size_t& index,
                                                     char null_marker) {
    if (index >= encoded.size()) {
        throw std::invalid_argument("incomplete preorder encoding");
    }

    const char value = encoded[index++];
    if (value == null_marker) {
        return nullptr;
    }

    Node* node = makeNode(value);
    node->left = parse(encoded, index, null_marker);
    node->right = parse(encoded, index, null_marker);
    return node;
}

void ThreadedBinaryTree::threadInorder(Node* node, Node*& previous) {
    if (!node) return;

    threadInorder(node->left, previous);

    if (node->left == nullptr) {
        node->left_thread = true;
        node->left = previous;
    }

    if (previous != nullptr && previous->right == nullptr) {
        previous->right_thread = true;
        previous->right = node;
    }

    previous = node;

    if (!node->right_thread) {
        threadInorder(node->right, previous);
    }
}

std::string ThreadedBinaryTree::inorder() const {
    std::string out;
    Node* current = root_;
    if (!current) return out;

    while (current->left != nullptr && !current->left_thread) {
        current = current->left;
    }

    while (current != nullptr) {
        out.push_back(current->value);

        if (current->right_thread) {
            current = current->right;
        } else {
            current = current->right;
            while (current != nullptr && current->left != nullptr && !current->left_thread) {
                current = current->left;
            }
        }
    }

    return out;
}

}  // namespace ds
