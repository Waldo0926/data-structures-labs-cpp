#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ds {

class LinkedQueue {
public:
    LinkedQueue() = default;

    void enqueue(int value);
    int dequeue();
    int front() const;

    bool empty() const noexcept { return head_ == nullptr; }
    std::size_t size() const noexcept { return size_; }

private:
    struct Node {
        explicit Node(int value) : value(value) {}
        int value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
    Node* tail_{nullptr};
    std::size_t size_{0};
};

}  // namespace ds
