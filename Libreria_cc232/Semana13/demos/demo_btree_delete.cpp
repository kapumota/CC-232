#include "BTree.h"

#include <iostream>

int main() {
    using namespace cc232::week13;

    BTree<int> tree(2);
    for (int value = 1; value <= 20; ++value) {
        tree.insert(value);
    }
    for (int value : {6, 13, 7, 4, 2, 16}) {
        tree.remove(value);
    }

    std::cout << "B-Tree despues de eliminaciones\n";
    std::cout << "Tamano: " << tree.size() << "\n";
    std::cout << "Invariantes: " << (tree.validate() ? "correctas" : "incorrectas") << "\n";
    for (int key : tree.inorder()) {
        std::cout << key << ' ';
    }
    std::cout << "\n";
    return 0;
}
