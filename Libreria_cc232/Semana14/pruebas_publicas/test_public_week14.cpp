#include "CapituloProyectoIntegrador.h"

#include <cassert>
#include <string>

int main() {
    using namespace cc232::week14;
    DataStructureAdvisor advisor;
    const auto prefixProfile = makePrefixWorkload(1000);
    const auto recommendations = advisor.recommend(prefixProfile);
    assert(!recommendations.empty());
    assert(recommendations.front().structureName == "Trie");

    WorkloadGenerator generator(1);
    const auto values = generator.randomIntegers(100);
    SortingBenchmark sortingBenchmark;
    const auto stats = sortingBenchmark.run(values, 1);
    assert(stats.size() == 2);
    assert(stats[0].samplesNanoseconds.size() == 1);
    return 0;
}
