#include "BPlusTree.h"

#include <cassert>
#include <string>
#include <vector>

int main() {
    using namespace cc232::week13;

    BPlusTree<int, std::string> tree(2);
    for (int value = 1; value <= 30; ++value) {
        tree.insert(value, "r" + std::to_string(value));
    }
    assert(tree.validate());

    const auto range = tree.rangeQuery(11, 17);
    assert(range.size() == 7);
    for (std::size_t i = 0; i < range.size(); ++i) {
        assert(range[i].first == static_cast<int>(11 + i));
        assert(range[i].second == "r" + std::to_string(11 + static_cast<int>(i)));
    }

    const auto empty = tree.rangeQuery(100, 200);
    assert(empty.empty());
    return 0;
}
