#include "ds/sequential_stack.hpp"

#include <algorithm>

namespace ds {

SequentialStack::SequentialStack(std::size_t initial_capacity)
    : data_(std::make_unique<int[]>(initial_capacity == 0 ? 1 : initial_capacity)),
      capacity_(initial_capacity == 0 ? 1 : initial_capacity) {}

void SequentialStack::grow() {
    const std::size_t next_capacity = capacity_ * 2;
    auto next = std::make_unique<int[]>(next_capacity);
    std::copy_n(data_.get(), size_, next.get());
    data_ = std::move(next);
    capacity_ = next_capacity;
}

void SequentialStack::push(int value) {
    if (size_ == capacity_) {
        grow();
    }
    data_[size_++] = value;
}

int SequentialStack::pop() {
    if (empty()) {
        throw std::underflow_error("pop from empty stack");
    }
    return data_[--size_];
}

int SequentialStack::top() const {
    if (empty()) {
        throw std::underflow_error("top of empty stack");
    }
    return data_[size_ - 1];
}

}  // namespace ds
