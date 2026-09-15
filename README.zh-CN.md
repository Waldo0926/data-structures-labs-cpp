# C++ 数据结构课程实验合集

[![类型](https://img.shields.io/badge/%E7%B1%BB%E5%9E%8B-%E8%AF%BE%E7%A8%8B%E9%87%8D%E6%9E%84-2563eb?style=for-the-badge)](#)
[![技术](https://img.shields.io/badge/%E6%8A%80%E6%9C%AF-C%2B%2B17-7c3aed?style=for-the-badge)](#)
[![许可证](https://img.shields.io/badge/%E8%AE%B8%E5%8F%AF%E8%AF%81-MIT-16a34a?style=for-the-badge)](LICENSE)


[English](README.md)

这是对早期《数据结构》课程实验进行重新整理后的项目，涵盖栈、队列、树、哈夫曼编码、图、图遍历算法以及排序算法。

原始课程实验完成于我早期的本科阶段，整体采用了较明显的 **C 风格编程方式**。虽然当时主要以 `.cpp` 文件提交，但代码大量使用结构体、裸指针、手动内存管理、固定长度数组以及过程式函数组织。

我在 2026 年重新检查了这些旧代码，保留了部分原始源码用于对照，并将核心实验重新实现为一个规模较小、可测试的 **现代 C++17** 项目。新版保留原有的数据结构与算法思想，同时改善了内存安全性、模块化、输入校验、可移植性和自动化验证能力。

> 本仓库的目的，是展示 **计算机科学基础能力以及代码演进过程**，而不是把早期课程作业包装成新写的项目。

## 涵盖内容

| 主题 | 现代实现 | 核心概念 |
| --- | --- | --- |
| 顺序栈 | `SequentialStack` | 动态存储、LIFO、容量扩展 |
| 链队列 | `LinkedQueue` | 链式节点、FIFO、所有权管理 |
| 二叉树 | `BinaryTree` | 递归建树、前序/中序/后序遍历 |
| 线索二叉树 | `ThreadedBinaryTree` | 中序线索化、前驱/后继链接 |
| 哈夫曼编码 | `HuffmanCodec` | 带权二叉树、前缀编码、编码/解码 |
| 图 | `Graph` | 邻接表、DFS、BFS |
| 排序 | sorting module | 直接插入、折半插入、快速排序、堆排序 |

## 项目特点

- 使用现代 C++17 重新实现原课程实验中的核心主题
- 使用 RAII 管理动态数据结构的资源与所有权
- 用更安全的方式替代手动内存管理和裸所有权
- 对错误输入和非法操作进行显式校验
- 自动化测试覆盖主要模块
- 使用 CMake 实现跨平台构建
- GitHub Actions 在 Linux、macOS 和 Windows 上运行 CI
- `legacy/` 中保留部分本人原始课程代码用于对照
- Modernisation Notes 记录重新检查旧代码时发现的真实问题及修复方式

## 项目结构

```text
data-structures-labs-cpp/
├── include/ds/         # 公共接口
├── src/                # 现代 C++17 实现
├── examples/           # 可直接运行的小型示例
├── tests/              # 自动化正确性测试
├── legacy/             # 部分原始 C 风格课程代码
├── docs/               # 现代化重构说明
├── .github/workflows/  # 跨平台 CI
└── CMakeLists.txt
```

## 构建

环境要求：

- CMake 3.16+
- 支持 C++17 的编译器

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

### 运行示例

在 macOS/Linux 且使用单配置生成器时：

```bash
./build/stack_demo
./build/queue_demo
./build/tree_demo
./build/threaded_tree_demo
./build/huffman_demo
./build/graph_demo
./build/sorting_demo
```

## 示例：二叉树遍历

二叉树示例沿用了原实验中的前序编码方式：

```text
ABD#F###CE###
```

其中 `#` 表示空子节点。

现代版本输出：

```text
Preorder : ABDFCE
Inorder  : DFBAEC
Postorder: FDBECA
```

## 为什么保留原始代码？

`legacy/` 目录用于明确展示项目的代码演进过程。

原课程代码虽然主要保存在 `.cpp` 文件中，但整体采用的是 C 风格的编程方式，常见写法包括：

- 结构体与过程式函数
- 裸指针
- `malloc`、`realloc` 和 `free`
- 固定长度数组
- 手动资源管理
- 交互式控制台输入

现代 C++17 版本展示了如何在保留相同数据结构思想的基础上，使用更清晰的所有权模型、更安全的资源管理方式、模块化接口、自动化测试和跨平台工程工具重新实现这些内容。

具体的旧代码问题及其处理方式见 [现代化重构说明](docs/modernisation-notes.md)。

## 相关项目

课程中规模更大的 Binary Search Tree 课程设计被单独整理并现代化为一个完整的信息管理应用：

**[BST Record Management System — Modern C++](https://github.com/Waldo0926/bst-record-management-cpp)**

该项目进一步展示了围绕二叉搜索树构建完整应用的过程，包括插入、查询、修改、删除、持久化、测试以及现代 C++ 内存管理。

## 学术诚信与仓库范围

本仓库仅保留我本人课程作业中的部分源代码。

课程课件、教学资料、可执行文件、班级归档提交以及其他同学的作业均未包含在本仓库中。

当前的现代 C++17 实现是后来对原始课程代码进行的工程化重构，并非当年的原始提交版本。

## License

MIT License，详见 [LICENSE](LICENSE)。
