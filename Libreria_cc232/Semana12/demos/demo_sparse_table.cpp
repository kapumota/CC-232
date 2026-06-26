#include "CapituloConsultasRango.h"

#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {12, 6, 18, 24, 30, 42};
    auto minTable = makeMinSparseTable(values);
    auto maxTable = makeMaxSparseTable(values);
    auto gcdTable = makeGcdSparseTable(values);

    std::cout << "### Demo: Sparse Table\n";
    std::cout << "Minimo [1, 4]: " << minTable.query(1, 4) << "\n";
    std::cout << "Maximo [1, 4]: " << maxTable.query(1, 4) << "\n";
    std::cout << "GCD [0, 5]: " << gcdTable.query(0, 5) << "\n";
    return 0;
}
