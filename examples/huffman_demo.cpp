#include "ds/huffman.hpp"
#include <iostream>
#include <vector>

int main() {
    const ds::HuffmanCodec codec({{'A', 5}, {'B', 9}, {'C', 12}, {'D', 13},
                                  {'E', 16}, {'F', 45}});
    const std::string text = "FACE";
    const std::string encoded = codec.encode(text);
    std::cout << text << " -> " << encoded << " -> " << codec.decode(encoded) << '\n';
}
