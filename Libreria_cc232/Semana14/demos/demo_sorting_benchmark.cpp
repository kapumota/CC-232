#include "CapituloProyectoIntegrador.h"

#include <iostream>

int main() {
    using namespace cc232::week14;
    WorkloadGenerator generator(14);
    const auto values = generator.randomIntegers(2000);
    SortingBenchmark benchmark;
    for (const auto& stats : benchmark.run(values, 3)) {
        std::cout << stats.name << ": promedio ns = " << stats.averageNanoseconds() << "\n";
    }
    return 0;
}
