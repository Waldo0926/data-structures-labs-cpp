#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ds {

class SequentialStack {
public:
    explicit SequentialStack(std::size_t initial_capacity = 8);

    void push(int value);
    int pop();
    int top() const;

    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }

private:
    void grow();

    std::unique_ptr<int[]> data_;
    std::size_t size_{0};
    std::size_t capacity_{0};
};

}  // namespace ds
