#include "BTree.h"

#include <iostream>

int main() {
    using namespace cc232::week13;

    BTree<int> tree(3);
    for (int value : {40, 10, 30, 20, 60, 50, 70, 80, 90, 100}) {
        tree.insert(value);
    }

    std::cout << "B-Tree despues de inserciones\n";
    std::cout << "Altura: " << tree.height() << "\n";
    std::cout << "Contiene 60: " << (tree.contains(60) ? "si" : "no") << "\n";
    std::cout << "Invariantes: " << (tree.validate() ? "correctas" : "incorrectas") << "\n";

    for (int key : tree.inorder()) {
        std::cout << key << ' ';
    }
    std::cout << "\n";
    return 0;
}
