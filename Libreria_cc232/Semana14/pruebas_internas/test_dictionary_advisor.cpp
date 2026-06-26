#include "DataStructureAdvisor.h"

#include <cassert>

int main() {
    using namespace cc232::week14;
    DataStructureAdvisor advisor;
    auto profile = makeDictionaryWorkload(1000);
    const auto recommendations = advisor.recommend(profile);
    assert(!recommendations.empty());
    assert(recommendations.front().structureName == "HashTable");

    profile.requiresOrderedTraversal = true;
    const auto ordered = advisor.recommend(profile);
    assert(!ordered.empty());
    bool hasTree = false;
    for (const auto& rec : ordered) {
        hasTree = hasTree || rec.structureName == "RedBlackTree";
    }
    assert(hasTree);
    return 0;
}
