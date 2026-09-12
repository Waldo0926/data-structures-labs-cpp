# C++ 数据结构课程实验合集

这是一个重新整理的数据结构课程实验合集，涵盖栈、队列、树、哈夫曼编码、图遍历和经典排序算法。

这些实验最初完成于我早期的本科阶段。2026 年重新整理旧资料时，我保留了部分原始代码用于对照，并把核心实验重新实现为一个可编译、可测试的 C++17 项目。

> 这个仓库的目的，是展示 **计算机科学基础能力以及代码演进过程**，而不是把旧课程作业包装成 2026 年新写的项目。

## 涵盖内容

| 主题 | 现代实现 | 核心概念 |
| --- | --- | --- |
| 顺序栈 | `SequentialStack` | 动态存储、LIFO、容量扩展 |
| 链队列 | `LinkedQueue` | 链式结点、FIFO、所有权管理 |
| 二叉树 | `BinaryTree` | 递归建树、前/中/后序遍历 |
| 线索二叉树 | `ThreadedBinaryTree` | 中序线索化、前驱/后继 |
| 哈夫曼编码 | `HuffmanCodec` | 带权二叉树、前缀编码、编码/解码 |
| 图 | `Graph` | 邻接表、DFS、BFS |
| 排序 | sorting module | 直接插入、折半插入、快速排序、堆排序 |

## 项目特点

- 使用 C++17 重新实现原课程实验中的核心内容
- 动态结构采用 RAII 管理
- 对非法输入和空结构操作进行显式检查
- 自动化测试覆盖各主要模块
- 使用 CMake 进行跨平台构建
- GitHub Actions 在 Linux、macOS、Windows 上持续集成
- `legacy/` 保留部分原始课程代码用于对照
- `docs/modernisation-notes.md` 记录重新检查旧代码时发现的真实问题和修复方式

## 编译与测试

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## 为什么保留原始代码？

`legacy/` 用于真实展示代码演进。原始版本仍然保留了当时常见的 C 风格动态内存、裸指针、固定长度数组和交互式输入方式；主代码则展示如何用更安全、更易测试的现代 C++ 表达相同的数据结构概念。

## 相关项目

较完整的二叉搜索树课程设计已经单独整理为一个项目：

**[BST Record Management System — Modern C++](https://github.com/Waldo0926/bst-record-management-cpp)**

## 仓库范围与学术规范

本仓库只保留我自己的部分课程源代码。课程 PPT、教学资料、可执行文件、整班作业压缩包以及其他同学的提交均不会公开上传。

## License

MIT License，详见 [LICENSE](LICENSE)。
