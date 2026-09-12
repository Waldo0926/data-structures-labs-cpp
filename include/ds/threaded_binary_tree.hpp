#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ds {

class ThreadedBinaryTree {
public:
    static ThreadedBinaryTree fromPreorder(const std::string& encoded,
                                           char null_marker = '#');

    std::string inorder() const;
    std::size_t size() const noexcept { return nodes_.size(); }

private:
    struct Node {
        explicit Node(char value) : value(value) {}
        char value;
        Node* left{nullptr};
        Node* right{nullptr};
        bool left_thread{false};
        bool right_thread{false};
    };

    Node* makeNode(char value);
    Node* parse(const std::string& encoded, std::size_t& index, char null_marker);
    void threadInorder(Node* node, Node*& previous);

    std::vector<std::unique_ptr<Node>> nodes_;
    Node* root_{nullptr};
};

}  // namespace ds
