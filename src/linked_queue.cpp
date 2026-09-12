#include "ds/linked_queue.hpp"

namespace ds {

void LinkedQueue::enqueue(int value) {
    auto node = std::make_unique<Node>(value);
    Node* raw = node.get();

    if (tail_ == nullptr) {
        head_ = std::move(node);
    } else {
        tail_->next = std::move(node);
    }

    tail_ = raw;
    ++size_;
}

int LinkedQueue::dequeue() {
    if (empty()) {
        throw std::underflow_error("dequeue from empty queue");
    }

    const int value = head_->value;
    head_ = std::move(head_->next);
    --size_;

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    return value;
}

int LinkedQueue::front() const {
    if (empty()) {
        throw std::underflow_error("front of empty queue");
    }
    return head_->value;
}

}  // namespace ds
