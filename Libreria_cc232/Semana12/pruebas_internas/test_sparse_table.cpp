#include "CapituloConsultasRango.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {12, 6, 18, 24, 30, 42, 48};
    auto minTable = makeMinSparseTable(values);
    auto maxTable = makeMaxSparseTable(values);
    auto gcdTable = makeGcdSparseTable(values);
    RangeQueryOracle oracle(values);

    for (int l = 0; l < static_cast<int>(values.size()); ++l) {
        for (int r = l; r < static_cast<int>(values.size()); ++r) {
            long long expectedGcd = values[l];
            for (int i = l + 1; i <= r; ++i) {
                expectedGcd = std::gcd(expectedGcd, values[i]);
            }
            assert(minTable.query(l, r) == oracle.rangeMin(l, r));
            assert(maxTable.query(l, r) == oracle.rangeMax(l, r));
            assert(gcdTable.query(l, r) == expectedGcd);
        }
    }

    PrefixSum2D prefix2d({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    assert(prefix2d.rectangleSum(0, 0, 2, 2) == 45);
    assert(prefix2d.rectangleSum(1, 1, 2, 2) == 28);

    std::cout << "Pruebas SparseTable Semana12 aprobadas\n";
    return 0;
}
