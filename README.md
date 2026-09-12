# Data Structures Labs in C++

[简体中文](README.zh-CN.md)

A revisited collection of classic Data Structures coursework implementations, covering stacks, queues, trees, Huffman coding, graphs, traversal algorithms, and sorting.

The original laboratory exercises were completed during my earlier undergraduate studies. I revisited the archive in 2026, preserved selected source files for comparison, and rebuilt the core exercises as a small, testable C++17 codebase.

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

- C++17 implementations of the original laboratory topics
- RAII-based ownership for dynamic structures
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
├── legacy/             # Selected original coursework source files
├── docs/               # Modernisation notes
├── .github/workflows/  # Cross-platform CI
└── CMakeLists.txt
```

## Build

Requirements:

- CMake 3.16+
- A C++17 compiler

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

The `legacy/` directory makes the development history explicit. It shows how the same data-structure concepts were originally implemented with C-style allocation, raw pointers, fixed-size arrays, and interactive input, and how those ideas can later be expressed with safer ownership and automated verification.

See [Modernisation Notes](docs/modernisation-notes.md) for concrete issues found in the original code and how they were addressed.

## Related project

The larger Binary Search Tree coursework project was modernised separately as a complete record-management application:

**[BST Record Management System — Modern C++](https://github.com/Waldo0926/bst-record-management-cpp)**

## Academic integrity and repository scope

Only selected source code from my own coursework is preserved here. Course slides, teaching materials, executable binaries, archived class submissions, and other students' work are intentionally excluded.

## License

MIT License. See [LICENSE](LICENSE).
