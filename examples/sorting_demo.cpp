#include "ds/sorting.hpp"
#include <iostream>
#include <vector>

static void print(const char* label, const std::vector<int>& values) {
    std::cout << label;
    for (int value : values) std::cout << ' ' << value;
    std::cout << '\n';
}

int main() {
    const std::vector<int> input{9, 3, 7, 1, 5, 2, 8, 4, 6};

    auto a = input;
    ds::insertionSort(a);
    print("Insertion:", a);

    auto b = input;
    ds::binaryInsertionSort(b);
    print("Binary insertion:", b);

    auto c = input;
    ds::quickSort(c);
    print("Quick sort:", c);

    auto d = input;
    ds::heapSort(d);
    print("Heap sort:", d);
}
