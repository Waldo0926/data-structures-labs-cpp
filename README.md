# Data Structures Labs in C++

[简体中文](README.zh-CN.md)

A revisited collection of classic Data Structures coursework implementations, covering stacks, queues, trees, Huffman coding, graphs, traversal algorithms, and sorting.

The original laboratory exercises were completed during my earlier undergraduate studies using a largely **C-style programming approach**. Although the source files were submitted primarily as `.cpp` files, the implementations relied heavily on structs, raw pointers, manual memory management, fixed-size arrays, and procedural programming patterns.

I revisited the archive in 2026, preserved selected original source files for comparison, and rebuilt the core exercises as a small, testable **modern C++17** codebase. The modern version retains the original data-structure and algorithm concepts while improving memory safety, modularity, validation, portability, and automated verification.

> The purpose of this repository is to demonstrate **computer-science fundamentals and code evolution**, not to present old coursework as newly written code.

## Topics covered

| Topic | Modern implementation | Core concepts |
| --- | --- | --- |
| Sequential stack | `SequentialStack` | dynamic storage, LIFO, capacity growth |
| Linked queue | `LinkedQueue` | linked nodes, FIFO, ownership |
| Binary tree | `BinaryTree` | recursive construction, preorder/inorder/postorder traversal |
| Threaded binary tree | `ThreadedBinaryTree` | inorder threading, predecessor/successor links |
| Huffman coding | `HuffmanCodec` | weighted binary tree, prefix coding, encode/decode |
| Graph | `Graph` | adjacency lists, DFS, BFS |
| Sorting | sorting module | insertion, binary insertion, quick sort, heap sort |

## Highlights

- Modern C++17 implementations of the original laboratory topics
- RAII-based ownership for dynamic data structures
- Safer alternatives to manual memory management and raw ownership
- Explicit validation of malformed inputs and invalid operations
- Automated tests covering every major module
- Cross-platform CMake build
- GitHub Actions CI on Linux, macOS, and Windows
- Selected original coursework sources preserved under `legacy/`
- Modernisation notes documenting real defects found while revisiting the old code

## Project structure

```text
data-structures-labs-cpp/
├── include/ds/         # Public interfaces
├── src/                # Modern C++17 implementations
├── examples/           # Small runnable demonstrations
├── tests/              # Automated correctness tests
├── legacy/             # Selected original C-style coursework sources
├── docs/               # Modernisation notes
├── .github/workflows/  # Cross-platform CI
└── CMakeLists.txt
```

## Build

Requirements:

- CMake 3.16+
- A C++17-compatible compiler

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

### Run an example

On macOS/Linux with a single-config generator:

```bash
./build/stack_demo
./build/queue_demo
./build/tree_demo
./build/threaded_tree_demo
./build/huffman_demo
./build/graph_demo
./build/sorting_demo
```

## Example: binary-tree traversal

The tree demo uses the same style of preorder encoding as the original exercise:

```text
ABD#F###CE###
```

where `#` represents an empty child.

The modern implementation produces:

```text
Preorder : ABDFCE
Inorder  : DFBAEC
Postorder: FDBECA
```

## Why keep the legacy code?

The `legacy/` directory makes the development history explicit.

The original coursework primarily used a C-style programming approach despite being stored in `.cpp` source files. Typical patterns included:

- structs and procedural functions
- raw pointers
- `malloc`, `realloc`, and `free`
- fixed-size arrays
- manual resource management
- interactive console input

The modern C++17 implementation demonstrates how the same underlying data-structure concepts can be expressed with clearer ownership, safer resource management, modular interfaces, automated testing, and cross-platform tooling.

See [Modernisation Notes](docs/modernisation-notes.md) for concrete issues found in the original code and how they were addressed.

## Related project

The larger Binary Search Tree coursework project was modernised separately as a complete record-management application:

**[BST Record Management System — Modern C++](https://github.com/Waldo0926/bst-record-management-cpp)**

It demonstrates a more complete application built around Binary Search Tree operations, including insertion, search, update, deletion, persistence, testing, and modern C++ memory management.

## Academic integrity and repository scope

Only selected source code from my own coursework is preserved in this repository.

Course slides, teaching materials, executable binaries, archived class submissions, and other students' work are intentionally excluded.

The modern C++17 implementation represents a later engineering revisit of the original coursework rather than the original submission itself.

## License

MIT License. See [LICENSE](LICENSE).
