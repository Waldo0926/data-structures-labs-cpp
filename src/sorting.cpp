#include "ds/sorting.hpp"

#include <algorithm>
#include <cstddef>

namespace ds {

void insertionSort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const int key = values[i];
        std::size_t j = i;
        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = key;
    }
}

void binaryInsertionSort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const int key = values[i];
        const auto position = std::upper_bound(values.begin(), values.begin() + static_cast<std::ptrdiff_t>(i), key);
        const std::size_t index = static_cast<std::size_t>(position - values.begin());
        for (std::size_t j = i; j > index; --j) {
            values[j] = values[j - 1];
        }
        values[index] = key;
    }
}

namespace {

void quickSortRange(std::vector<int>& values, std::ptrdiff_t low, std::ptrdiff_t high) {
    if (low >= high) return;

    const int pivot = values[static_cast<std::size_t>(low + (high - low) / 2)];
    std::ptrdiff_t i = low;
    std::ptrdiff_t j = high;

    while (i <= j) {
        while (values[static_cast<std::size_t>(i)] < pivot) ++i;
        while (values[static_cast<std::size_t>(j)] > pivot) --j;
        if (i <= j) {
            std::swap(values[static_cast<std::size_t>(i)], values[static_cast<std::size_t>(j)]);
            ++i;
            --j;
        }
    }

    if (low < j) quickSortRange(values, low, j);
    if (i < high) quickSortRange(values, i, high);
}

void siftDown(std::vector<int>& values, std::size_t root, std::size_t end) {
    while (true) {
        std::size_t child = root * 2 + 1;
        if (child >= end) return;
        if (child + 1 < end && values[child] < values[child + 1]) ++child;
        if (values[root] >= values[child]) return;
        std::swap(values[root], values[child]);
        root = child;
    }
}

}  // namespace

void quickSort(std::vector<int>& values) {
    if (!values.empty()) {
        quickSortRange(values, 0, static_cast<std::ptrdiff_t>(values.size() - 1));
    }
}

void heapSort(std::vector<int>& values) {
    if (values.size() < 2) return;

    for (std::size_t i = values.size() / 2; i > 0; --i) {
        siftDown(values, i - 1, values.size());
    }

    for (std::size_t end = values.size(); end > 1; --end) {
        std::swap(values[0], values[end - 1]);
        siftDown(values, 0, end - 1);
    }
}

}  // namespace ds
