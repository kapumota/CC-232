#include "BlockModel.h"
#include "ExternalMemoryCost.h"

#include <iostream>

int main() {
    using namespace cc232::week13;

    BlockModel model(4096, 8, 8);
    auto comparison = compareTreeHeights(1'000'000, model);

    std::cout << "Modelo de bloques para B-Tree\n";
    std::cout << "Claves maximas por nodo: " << model.maxKeysInBTreeNode() << "\n";
    std::cout << "Fanout aproximado: " << model.approximateFanout() << "\n";
    std::cout << comparison.summary() << "\n";
    return 0;
}
