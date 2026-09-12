# Modernisation Notes

This repository was reconstructed from an early Data Structures coursework archive. The goal is not to pretend that the original laboratory code was written with modern C++ practices. Instead, the repository preserves selected original implementations under `legacy/` and provides a clean C++17 implementation of the same concepts in the main codebase.

## Issues found while revisiting the original code

| Area | Original issue | Revisited implementation |
| --- | --- | --- |
| Sequential stack | One version allocated only the increment size while recording the capacity as the much larger initial size, which could lead to out-of-bounds writes | Capacity and allocation always agree; growth uses RAII-managed arrays |
| Linked queue | Removing the final element could leave queue pointers referring to freed memory | `head_` owns nodes with `std::unique_ptr`; `tail_` is reset when the queue becomes empty |
| Binary tree | `void main`, manual allocation and no corresponding cleanup | Standard `int main` demos and automatic ownership with `std::unique_ptr` |
| Threaded binary tree | Manual allocation and global traversal state made ownership difficult to reason about | Nodes are owned by a container while thread links remain explicit non-owning pointers |
| Huffman coding | The original `int *w` frequency pointer was used before storage was allocated | Frequency data is validated and stored safely before tree construction |
| Graph | A missing vertex label could leave an adjacency index uninitialised; allocated edge nodes were not released | Vertex lookup is validated and adjacency storage is managed automatically |
| Sorting | Fixed-size storage relied on callers respecting a maximum length | Algorithms operate on `std::vector<int>` and support arbitrary practical input sizes |

## Scope

The modern version focuses on the concepts represented in the original coursework:

- sequential stack
- linked queue
- binary-tree construction and traversal
- inorder-threaded binary tree traversal
- Huffman coding and decoding
- adjacency-list graph traversal with DFS and BFS
- direct insertion sort, binary insertion sort, quick sort, and heap sort

The larger Binary Search Tree record-management coursework project is maintained separately:

- <https://github.com/Waldo0926/bst-record-management-cpp>
