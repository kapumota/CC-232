#include "CapituloProyectoIntegrador.h"

#include <iostream>

int main() {
    using namespace cc232::week14;
    WorkloadGenerator generator(232);
    auto profile = makeExternalMemoryWorkload(100000);
    DataStructureAdvisor advisor;
    DictionaryBenchmark dictionaryBenchmark;

    BenchmarkReport report;
    report.setProfile(profile);
    const auto keys = generator.randomIntegers(3000);
    for (const auto& stats : dictionaryBenchmark.run(keys, 2)) {
        report.addStats(stats);
    }
    for (const auto& rec : advisor.recommend(profile)) {
        report.addRecommendation(rec);
    }
    std::cout << report.toMarkdown();
    return 0;
}
