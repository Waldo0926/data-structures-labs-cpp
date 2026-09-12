#include "ds/linked_queue.hpp"
#include <iostream>

int main() {
    ds::LinkedQueue queue;
    for (int value : {1, 2, 3, 4, 5}) queue.enqueue(value);
    std::cout << "Front: " << queue.front() << "\nDequeue order:";
    while (!queue.empty()) std::cout << ' ' << queue.dequeue();
    std::cout << '\n';
}
