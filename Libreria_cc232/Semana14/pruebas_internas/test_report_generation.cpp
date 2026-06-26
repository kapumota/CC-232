#include "BenchmarkReport.h"
#include "DataStructureAdvisor.h"
#include "WorkloadProfile.h"

#include <cassert>
#include <string>

int main() {
    using namespace cc232::week14;
    BenchmarkReport report;
    const auto profile = makeExternalMemoryWorkload(1000);
    report.setProfile(profile);

    BenchmarkStats stats;
    stats.name = "demo";
    stats.addSample(10);
    report.addStats(stats);

    DataStructureAdvisor advisor;
    for (const auto& rec : advisor.recommend(profile)) {
        report.addRecommendation(rec);
    }

    const auto text = report.toMarkdown();
    assert(text.find("Reporte experimental") != std::string::npos);
    assert(text.find("BPlusTree") != std::string::npos);
    return 0;
}
