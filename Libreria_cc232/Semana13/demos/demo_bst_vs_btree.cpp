#include "BTree.h"
#include "BinarySearchTreeBaseline.h"
#include "BlockModel.h"
#include "ExternalMemoryCost.h"

#include <iostream>

int main() {
    using namespace cc232::week13;

    BinarySearchTreeBaseline<int> bst;
    BTree<int> btree(16);
    for (int value = 1; value <= 1000; ++value) {
        bst.insert(value);
        btree.insert(value);
    }

    BlockModel model(4096, 8, 8);
    auto cost = compareTreeHeights(1000, model);

    std::cout << "Comparacion BST no balanceado vs B-Tree\n";
    std::cout << "Altura BST con insercion ordenada: " << bst.height() << "\n";
    std::cout << "Altura B-Tree grado 16: " << btree.height() << "\n";
    std::cout << cost.summary() << "\n";
    return 0;
}
