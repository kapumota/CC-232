#pragma once

#include "BlockModel.h"

#include <algorithm>
#include <cstddef>
#include <string>

namespace cc232::week13 {

struct CostComparison {
    std::size_t keys = 0;
    std::size_t fanout = 0;
    std::size_t btree_height = 0;
    std::size_t balanced_bst_height = 0;
    std::size_t worst_bst_height = 0;

    [[nodiscard]] std::string summary() const {
        return "n=" + std::to_string(keys) +
               ", fanout=" + std::to_string(fanout) +
               ", altura_btree=" + std::to_string(btree_height) +
               ", altura_bst_balanceado=" + std::to_string(balanced_bst_height) +
               ", altura_bst_peor=" + std::to_string(worst_bst_height);
    }
};

inline CostComparison compareTreeHeights(std::size_t keys, const BlockModel& model) {
    CostComparison result;
    result.keys = keys;
    result.fanout = std::max<std::size_t>(2, model.approximateFanout());
    result.btree_height = approximateBTreeHeight(keys, result.fanout);
    result.balanced_bst_height = balancedBstHeight(keys);
    result.worst_bst_height = worstCaseBstHeight(keys);
    return result;
}

inline std::size_t estimateSearchBlockReadsForBTree(std::size_t keys, const BlockModel& model) {
    if (keys == 0) {
        return 0;
    }
    return approximateBTreeHeight(keys, model.approximateFanout()) + 1;
}

inline std::size_t estimateSearchBlockReadsForPointerBst(std::size_t keys, bool balanced) {
    if (keys == 0) {
        return 0;
    }
    return balanced ? balancedBstHeight(keys) + 1 : worstCaseBstHeight(keys) + 1;
}

}  // namespace cc232::week13
