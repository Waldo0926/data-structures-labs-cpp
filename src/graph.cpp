#include "ds/graph.hpp"

#include <algorithm>
#include <queue>
#include <stdexcept>

namespace ds {

void Graph::addVertex(int label) {
    if (index_.count(label) != 0) {
        throw std::invalid_argument("duplicate vertex label");
    }
    index_[label] = labels_.size();
    labels_.push_back(label);
    adjacency_.emplace_back();
}

std::size_t Graph::indexOf(int label) const {
    const auto it = index_.find(label);
    if (it == index_.end()) {
        throw std::out_of_range("vertex label not found");
    }
    return it->second;
}

void Graph::addUndirectedEdge(int from, int to) {
    const std::size_t a = indexOf(from);
    const std::size_t b = indexOf(to);

    auto add_once = [](std::vector<std::size_t>& list, std::size_t value) {
        if (std::find(list.begin(), list.end(), value) == list.end()) {
            list.push_back(value);
            return true;
        }
        return false;
    };

    const bool added = add_once(adjacency_[a], b);
    add_once(adjacency_[b], a);
    if (added) {
        ++edge_count_;
    }
}

std::vector<int> Graph::dfs() const {
    std::vector<int> order;
    std::vector<bool> visited(labels_.size(), false);

    const auto visit = [&](auto&& self, std::size_t current) -> void {
        visited[current] = true;
        order.push_back(labels_[current]);
        for (std::size_t next : adjacency_[current]) {
            if (!visited[next]) self(self, next);
        }
    };

    for (std::size_t i = 0; i < labels_.size(); ++i) {
        if (!visited[i]) visit(visit, i);
    }
    return order;
}

std::vector<int> Graph::bfs() const {
    std::vector<int> order;
    std::vector<bool> visited(labels_.size(), false);
    std::queue<std::size_t> queue;

    for (std::size_t start = 0; start < labels_.size(); ++start) {
        if (visited[start]) continue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty()) {
            const std::size_t current = queue.front();
            queue.pop();
            order.push_back(labels_[current]);

            for (std::size_t next : adjacency_[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    queue.push(next);
                }
            }
        }
    }
    return order;
}

}  // namespace ds
