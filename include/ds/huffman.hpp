#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace ds {

class HuffmanCodec {
public:
    explicit HuffmanCodec(const std::vector<std::pair<char, unsigned>>& frequencies);

    const std::unordered_map<char, std::string>& codes() const noexcept { return codes_; }
    std::string encode(const std::string& text) const;
    std::string decode(const std::string& bits) const;

private:
    struct Node {
        unsigned weight{0};
        char symbol{'\0'};
        int left{-1};
        int right{-1};
        bool leaf{false};
    };

    void buildCodes(int index, std::string prefix);

    std::vector<Node> nodes_;
    int root_{-1};
    std::unordered_map<char, std::string> codes_;
};

}  // namespace ds
