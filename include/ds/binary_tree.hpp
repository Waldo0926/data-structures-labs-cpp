#pragma once

#include <memory>
#include <string>

namespace ds {

class BinaryTree {
public:
    static BinaryTree fromPreorder(const std::string& encoded, char null_marker = '#');

    std::string preorder() const;
    std::string inorder() const;
    std::string postorder() const;
    bool empty() const noexcept { return root_ == nullptr; }

private:
    struct Node {
        explicit Node(char value) : value(value) {}
        char value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    static std::unique_ptr<Node> parse(const std::string& encoded,
                                       std::size_t& index,
                                       char null_marker);
    static void preorder(const Node* node, std::string& out);
    static void inorder(const Node* node, std::string& out);
    static void postorder(const Node* node, std::string& out);

    std::unique_ptr<Node> root_;
};

}  // namespace ds
