#include "BenchmarkStats.h"

#include <cassert>

int main() {
    using namespace cc232::week14;
    BenchmarkStats stats;
    stats.name = "estructura";
    stats.addSample(100);
    stats.addSample(200);
    stats.addSample(300);
    assert(stats.totalNanoseconds() == 600);
    assert(stats.averageNanoseconds() == 200.0);
    assert(stats.minNanoseconds() == 100);
    assert(stats.maxNanoseconds() == 300);

    BenchmarkStats faster;
    faster.addSample(10);
    assert(fasterThan(faster, stats));
    return 0;
}
