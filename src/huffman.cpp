#include "ds/huffman.hpp"

#include <queue>
#include <stdexcept>
#include <unordered_set>

namespace ds {

HuffmanCodec::HuffmanCodec(const std::vector<std::pair<char, unsigned>>& frequencies) {
    if (frequencies.empty()) {
        throw std::invalid_argument("at least one symbol is required");
    }

    struct Entry {
        unsigned weight;
        int index;
        bool operator>(const Entry& other) const {
            if (weight != other.weight) return weight > other.weight;
            return index > other.index;
        }
    };

    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> queue;
    std::unordered_set<char> seen;

    for (const auto& [symbol, weight] : frequencies) {
        if (weight == 0) {
            throw std::invalid_argument("symbol weights must be positive");
        }
        if (!seen.insert(symbol).second) {
            throw std::invalid_argument("duplicate symbol in frequency table");
        }

        nodes_.push_back(Node{weight, symbol, -1, -1, true});
        queue.push(Entry{weight, static_cast<int>(nodes_.size() - 1)});
    }

    if (queue.size() == 1) {
        root_ = queue.top().index;
        codes_[nodes_[root_].symbol] = "0";
        return;
    }

    while (queue.size() > 1) {
        const Entry left = queue.top();
        queue.pop();
        const Entry right = queue.top();
        queue.pop();

        nodes_.push_back(Node{left.weight + right.weight, '\0', left.index, right.index, false});
        const int parent = static_cast<int>(nodes_.size() - 1);
        queue.push(Entry{nodes_[parent].weight, parent});
    }

    root_ = queue.top().index;
    buildCodes(root_, "");
}

void HuffmanCodec::buildCodes(int index, std::string prefix) {
    const Node& node = nodes_.at(static_cast<std::size_t>(index));
    if (node.leaf) {
        codes_[node.symbol] = prefix.empty() ? "0" : std::move(prefix);
        return;
    }

    buildCodes(node.left, prefix + '0');
    buildCodes(node.right, prefix + '1');
}

std::string HuffmanCodec::encode(const std::string& text) const {
    std::string out;
    for (char ch : text) {
        const auto it = codes_.find(ch);
        if (it == codes_.end()) {
            throw std::invalid_argument("text contains symbol absent from Huffman table");
        }
        out += it->second;
    }
    return out;
}

std::string HuffmanCodec::decode(const std::string& bits) const {
    if (root_ < 0) return {};

    const Node& root = nodes_[static_cast<std::size_t>(root_)];
    if (root.leaf) {
        std::string out;
        for (char bit : bits) {
            if (bit != '0') {
                throw std::invalid_argument("invalid bit string for single-symbol Huffman tree");
            }
            out.push_back(root.symbol);
        }
        return out;
    }

    std::string out;
    int current = root_;

    for (char bit : bits) {
        if (bit != '0' && bit != '1') {
            throw std::invalid_argument("Huffman code must contain only 0 and 1");
        }

        const Node& node = nodes_[static_cast<std::size_t>(current)];
        current = (bit == '0') ? node.left : node.right;
        if (current < 0) {
            throw std::invalid_argument("invalid Huffman bit sequence");
        }

        const Node& next = nodes_[static_cast<std::size_t>(current)];
        if (next.leaf) {
            out.push_back(next.symbol);
            current = root_;
        }
    }

    if (current != root_) {
        throw std::invalid_argument("incomplete Huffman bit sequence");
    }

    return out;
}

}  // namespace ds
