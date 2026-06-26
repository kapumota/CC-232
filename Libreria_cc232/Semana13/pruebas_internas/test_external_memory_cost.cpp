#include "BinarySearchTreeBaseline.h"
#include "BlockModel.h"
#include "BlockStoreSimulator.h"
#include "ExternalMemoryCost.h"

#include <cassert>
#include <string>

int main() {
    using namespace cc232::week13;

    BlockModel model(4096, 8, 8, 32);
    assert(model.approximateFanout() > 100);
    auto cost = compareTreeHeights(1'000'000, model);
    assert(cost.btree_height < cost.balanced_bst_height);
    assert(cost.balanced_bst_height < cost.worst_bst_height);

    BinarySearchTreeBaseline<int> bst;
    for (int value = 1; value <= 50; ++value) {
        bst.insert(value);
    }
    assert(bst.height() == 50);
    assert(bst.searchPathLength(50) == 50);

    BlockStoreSimulator<std::string> store;
    auto id = store.placeBlock("pagina_1");
    assert(store.contains(id));
    assert(store.readBlock(id) == "pagina_1");
    store.writeBlock(id, "pagina_2");
    assert(store.readBlock(id) == "pagina_2");
    assert(store.stats().block_reads == 2);
    assert(store.stats().block_writes == 2);
    return 0;
}
