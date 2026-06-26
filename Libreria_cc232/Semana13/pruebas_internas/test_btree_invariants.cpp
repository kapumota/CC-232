#include "BTree.h"
#include "BTreeValidator.h"

#include <cassert>
#include <vector>

int main() {
    using namespace cc232::week13;

    for (std::size_t degree : {2U, 3U, 5U}) {
        BTree<int> tree(degree);
        for (int value = 0; value < 200; value += 3) {
            assert(tree.insert(value));
            assert(validateBTree(tree).ok);
        }
        for (int value = 0; value < 200; value += 6) {
            assert(tree.remove(value));
            assert(validateBTree(tree).ok);
        }
    }
    return 0;
}
