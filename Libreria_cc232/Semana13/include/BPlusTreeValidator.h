#pragma once

#include "BPlusTree.h"

#include <string>

namespace cc232::week13 {

template <typename Key, typename Value>
struct BPlusTreeValidationReport {
    bool ok = false;
    std::string message;
};

template <typename Key, typename Value>
BPlusTreeValidationReport<Key, Value> validateBPlusTree(const BPlusTree<Key, Value>& tree) {
    if (tree.validate()) {
        return {true, "El B+Tree cumple las invariantes estructurales"};
    }
    return {false, "El B+Tree no cumple alguna invariante estructural"};
}

}  // namespace cc232::week13
