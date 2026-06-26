#include "BTree.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

int main() {
    using namespace cc232::week13;

    BTree<int> tree(2);
    std::vector<int> values(100);
    std::iota(values.begin(), values.end(), 1);
    std::reverse(values.begin(), values.end());

    for (int value : values) {
        assert(tree.insert(value));
        assert(tree.validate());
    }
    for (int value = 1; value <= 100; ++value) {
        assert(tree.contains(value));
    }
    assert(!tree.contains(101));

    auto ordered = tree.inorder();
    assert(std::is_sorted(ordered.begin(), ordered.end()));
    assert(ordered.size() == 100);
    assert(ordered.front() == 1);
    assert(ordered.back() == 100);
    return 0;
}
