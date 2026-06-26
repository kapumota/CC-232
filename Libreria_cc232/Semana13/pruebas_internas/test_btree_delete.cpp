#include "BTree.h"

#include <cassert>
#include <set>
#include <vector>

int main() {
    using namespace cc232::week13;

    BTree<int> tree(3);
    std::set<int> oracle;
    for (int value = 1; value <= 80; ++value) {
        tree.insert(value);
        oracle.insert(value);
    }

    for (int value : {1, 2, 3, 40, 41, 42, 79, 80, 15, 25, 35, 45, 55, 65}) {
        assert(tree.remove(value));
        oracle.erase(value);
        assert(tree.validate());
    }
    assert(!tree.remove(1000));

    std::vector<int> expected(oracle.begin(), oracle.end());
    assert(tree.inorder() == expected);
    for (int value : expected) {
        assert(tree.contains(value));
    }
    return 0;
}
