#include "CapituloConsultasRango.h"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values;
    for (int i = 0; i < 50; ++i) {
        values.push_back((i * i + 3 * i) % 17 - 8);
    }

    RangeQueryOracle oracle(values);
    SegmentTree segment(values);
    IterativeSegmentTree iterative(values);
    FenwickTree fenwick(values);

    for (int l = 0; l < 50; ++l) {
        for (int r = l; r < 50; ++r) {
            long long expected = oracle.rangeSum(l, r);
            assert(segment.rangeSum(l, r) == expected);
            assert(iterative.rangeSum(l, r) == expected);
            assert(fenwick.rangeSum(l, r) == expected);
        }
    }

    std::cout << "Comparacion entre estructuras Semana12 aprobada\n";
    return 0;
}
