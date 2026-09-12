#include "ds/sequential_stack.hpp"
#include <iostream>

int main() {
    ds::SequentialStack stack;
    for (int value : {1, 2, 3, 4, 5}) stack.push(value);
    std::cout << "Top: " << stack.top() << "\nPop order:";
    while (!stack.empty()) std::cout << ' ' << stack.pop();
    std::cout << '\n';
}
