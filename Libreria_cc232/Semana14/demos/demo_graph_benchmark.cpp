#include "CapituloProyectoIntegrador.h"

#include <iostream>

int main() {
    using namespace cc232::week14;
    GraphBenchmark benchmark;
    const auto stats = benchmark.benchBfsAdjacencyList(5000, 3);
    std::cout << stats.name << ": promedio ns = " << stats.averageNanoseconds() << "\n";
    return 0;
}
