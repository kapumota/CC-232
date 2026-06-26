#include "BPlusTree.h"
#include "BPlusTreeValidator.h"

#include <cassert>
#include <map>
#include <string>

int main() {
    using namespace cc232::week13;

    BPlusTree<int, std::string> tree(3);
    std::map<int, std::string> oracle;
    for (int value : {50, 10, 30, 20, 40, 60, 70, 80, 90, 100, 5, 15, 25, 35, 45}) {
        const std::string text = "v" + std::to_string(value);
        assert(tree.insert(value, text));
        oracle[value] = text;
        assert(validateBPlusTree(tree).ok);
    }
    assert(!tree.insert(30, "actualizado"));
    assert(tree.find(30).value() == "actualizado");
    assert(tree.size() == oracle.size());
    for (const auto& [key, value] : oracle) {
        assert(tree.contains(key));
    }
    assert(!tree.contains(999));
    return 0;
}
