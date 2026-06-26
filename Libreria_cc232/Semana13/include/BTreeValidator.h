#pragma once

#include "BTree.h"

#include <string>

namespace cc232::week13 {

template <typename Key>
struct BTreeValidationReport {
    bool ok = false;
    std::string message;
};

template <typename Key>
BTreeValidationReport<Key> validateBTree(const BTree<Key>& tree) {
    if (tree.validate()) {
        return {true, "El B-Tree cumple las invariantes estructurales"};
    }
    return {false, "El B-Tree no cumple alguna invariante estructural"};
}

}  // namespace cc232::week13
