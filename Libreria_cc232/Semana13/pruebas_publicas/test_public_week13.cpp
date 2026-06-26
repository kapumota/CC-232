#include "BPlusTree.h"
#include "BTree.h"
#include "BlockModel.h"
#include "ExternalMemoryCost.h"

#include <cassert>
#include <string>
#include <vector>

int main() {
    using namespace cc232::week13;

    BTree<int> tree(3);
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17}) {
        assert(tree.insert(value));
    }
    assert(!tree.insert(10));
    assert(tree.contains(6));
    assert(!tree.contains(99));
    assert(tree.validate());
    assert((tree.inorder() == std::vector<int>{5, 6, 7, 10, 12, 17, 20, 30}));

    BPlusTree<int, std::string> index(3);
    index.insert(1, "uno");
    index.insert(3, "tres");
    index.insert(2, "dos");
    assert(index.find(2).value() == "dos");
    assert(index.validate());
    const auto range = index.rangeQuery(1, 2);
    assert(range.size() == 2);
    assert(range[0].first == 1);
    assert(range[1].first == 2);

    BlockModel model(4096, 8, 8);
    assert(model.maxKeysInBTreeNode() > 100);
    assert(estimateSearchBlockReadsForBTree(1'000'000, model) < estimateSearchBlockReadsForPointerBst(1'000'000, true));

    return 0;
}
