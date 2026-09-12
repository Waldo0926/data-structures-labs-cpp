#include "ds/binary_tree.hpp"
#include "ds/graph.hpp"
#include "ds/huffman.hpp"
#include "ds/linked_queue.hpp"
#include "ds/sequential_stack.hpp"
#include "ds/sorting.hpp"
#include "ds/threaded_binary_tree.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

int failures = 0;

void check(bool condition, const std::string& name) {
    if (!condition) {
        ++failures;
        std::cerr << "[FAIL] " << name << '\n';
    }
}

template <typename Fn>
void checkThrows(Fn&& fn, const std::string& name) {
    try {
        fn();
        check(false, name);
    } catch (const std::exception&) {
        check(true, name);
    }
}

void testStack() {
    ds::SequentialStack stack(2);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    check(stack.capacity() >= 3, "stack grows capacity");
    check(stack.top() == 30, "stack top");
    check(stack.pop() == 30 && stack.pop() == 20 && stack.pop() == 10, "stack LIFO");
    checkThrows([&] { stack.pop(); }, "stack empty pop throws");
}

void testQueue() {
    ds::LinkedQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    check(queue.front() == 10, "queue front");
    check(queue.dequeue() == 10 && queue.dequeue() == 20 && queue.dequeue() == 30, "queue FIFO");
    check(queue.empty(), "queue becomes empty");
    queue.enqueue(40);
    check(queue.dequeue() == 40, "queue reusable after becoming empty");
}

void testBinaryTree() {
    const auto tree = ds::BinaryTree::fromPreorder("ABD#F###CE###");
    check(tree.preorder() == "ABDFCE", "binary tree preorder");
    check(tree.inorder() == "DFBAEC", "binary tree inorder");
    check(tree.postorder() == "FDBECA", "binary tree postorder");
    checkThrows([] { ds::BinaryTree::fromPreorder("A#"); }, "binary tree rejects incomplete encoding");
}

void testThreadedTree() {
    const auto tree = ds::ThreadedBinaryTree::fromPreorder("ABC##DE#G##F###");
    check(tree.inorder() == "CBEGDFA", "threaded tree inorder traversal");
    check(tree.size() == 7, "threaded tree node count");
}

void testHuffman() {
    const ds::HuffmanCodec codec({{'A', 5}, {'B', 9}, {'C', 12}, {'D', 13}, {'E', 16}, {'F', 45}});
    const std::string text = "FACE";
    const std::string bits = codec.encode(text);
    check(codec.decode(bits) == text, "Huffman round trip");
    checkThrows([&] { codec.encode("Z"); }, "Huffman rejects unknown symbol");
    checkThrows([&] { codec.decode("10x"); }, "Huffman rejects non-binary input");
}

void testGraph() {
    ds::Graph graph;
    for (int vertex : {1, 2, 3, 4, 5}) graph.addVertex(vertex);
    graph.addUndirectedEdge(1, 2);
    graph.addUndirectedEdge(1, 3);
    graph.addUndirectedEdge(2, 4);
    graph.addUndirectedEdge(3, 5);
    check(graph.vertexCount() == 5, "graph vertex count");
    check(graph.edgeCount() == 4, "graph edge count");
    check(graph.dfs() == std::vector<int>({1, 2, 4, 3, 5}), "graph DFS order");
    check(graph.bfs() == std::vector<int>({1, 2, 3, 4, 5}), "graph BFS order");
    graph.addUndirectedEdge(1, 2);
    check(graph.edgeCount() == 4, "graph ignores duplicate edge");
}

void testSorting() {
    const std::vector<int> input{5, 1, 4, 2, 8, 5, -1, 0};
    auto expected = input;
    std::sort(expected.begin(), expected.end());

    auto a = input;
    ds::insertionSort(a);
    check(a == expected, "insertion sort");

    auto b = input;
    ds::binaryInsertionSort(b);
    check(b == expected, "binary insertion sort");

    auto c = input;
    ds::quickSort(c);
    check(c == expected, "quick sort");

    auto d = input;
    ds::heapSort(d);
    check(d == expected, "heap sort");
}

}  // namespace

int main() {
    testStack();
    testQueue();
    testBinaryTree();
    testThreadedTree();
    testHuffman();
    testGraph();
    testSorting();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed\n";
        return 1;
    }

    std::cout << "All data-structure tests passed.\n";
    return 0;
}
