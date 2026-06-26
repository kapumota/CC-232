#include "DataStructureAdvisor.h"

#include <cassert>

int main() {
    using namespace cc232::week14;
    DataStructureAdvisor advisor;
    const auto dynamicProfile = makeRangeWorkload(1000, true);
    const auto dynamicRecommendations = advisor.recommend(dynamicProfile);
    assert(dynamicRecommendations.front().structureName == "LazySegmentTree");

    const auto staticProfile = makeRangeWorkload(1000, false);
    const auto staticRecommendations = advisor.recommend(staticProfile);
    assert(staticRecommendations.front().structureName == "SparseTable");
    return 0;
}
