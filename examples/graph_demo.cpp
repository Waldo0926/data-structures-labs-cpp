#include "ds/graph.hpp"
#include <iostream>

static void print(const char* label, const std::vector<int>& values) {
    std::cout << label;
    for (int value : values) std::cout << ' ' << value;
    std::cout << '\n';
}

int main() {
    ds::Graph graph;
    for (int vertex : {1, 2, 3, 4, 5}) graph.addVertex(vertex);
    graph.addUndirectedEdge(1, 2);
    graph.addUndirectedEdge(1, 3);
    graph.addUndirectedEdge(2, 4);
    graph.addUndirectedEdge(3, 5);
    print("DFS:", graph.dfs());
    print("BFS:", graph.bfs());
}
