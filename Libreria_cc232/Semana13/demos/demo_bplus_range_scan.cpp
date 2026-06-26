#include "BPlusTree.h"

#include <iostream>
#include <string>

int main() {
    using namespace cc232::week13;

    BPlusTree<int, std::string> index(3);
    for (int value : {5, 2, 8, 1, 3, 7, 10, 6, 4, 9}) {
        index.insert(value, "registro_" + std::to_string(value));
    }

    std::cout << "Range scan en B+Tree para [3, 8]\n";
    for (const auto& [key, value] : index.rangeQuery(3, 8)) {
        std::cout << key << " -> " << value << "\n";
    }
    std::cout << "Invariantes: " << (index.validate() ? "correctas" : "incorrectas") << "\n";
    return 0;
}
