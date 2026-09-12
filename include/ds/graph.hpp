#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

namespace ds {

class Graph {
public:
    void addVertex(int label);
    void addUndirectedEdge(int from, int to);

    std::vector<int> dfs() const;
    std::vector<int> bfs() const;

    std::size_t vertexCount() const noexcept { return labels_.size(); }
    std::size_t edgeCount() const noexcept { return edge_count_; }

private:
    std::size_t indexOf(int label) const;

    std::vector<int> labels_;
    std::unordered_map<int, std::size_t> index_;
    std::vector<std::vector<std::size_t>> adjacency_;
    std::size_t edge_count_{0};
};

}  // namespace ds
