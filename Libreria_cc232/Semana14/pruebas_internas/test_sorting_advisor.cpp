#include "DataStructureAdvisor.h"

#include <cassert>

int main() {
    using namespace cc232::week14;
    WorkloadProfile profile;
    profile.domain = WorkloadDomain::Sorting;
    profile.dataSize = 1000;
    profile.hasSmallIntegerUniverse = true;
    DataStructureAdvisor advisor;
    const auto recommendations = advisor.recommend(profile);
    assert(!recommendations.empty());
    assert(recommendations.front().structureName == "CountingSort");

    profile.hasSmallIntegerUniverse = false;
    const auto general = advisor.recommend(profile);
    assert(general.front().structureName == "IntroSort");
    return 0;
}
