#include "CapituloConsultasRango.h"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {2, 1, 3, 4, 2, 5, 1};
    FenwickTree bit(values);
    RangeQueryOracle oracle(values);

    for (int l = 0; l < static_cast<int>(values.size()); ++l) {
        for (int r = l; r < static_cast<int>(values.size()); ++r) {
            assert(bit.rangeSum(l, r) == oracle.rangeSum(l, r));
        }
    }

    bit.add(3, 10);
    oracle.pointAdd(3, 10);
    bit.add(0, -2);
    oracle.pointAdd(0, -2);

    for (int l = 0; l < static_cast<int>(values.size()); ++l) {
        for (int r = l; r < static_cast<int>(values.size()); ++r) {
            assert(bit.rangeSum(l, r) == oracle.rangeSum(l, r));
        }
    }

    FenwickTree nonNegative({1, 2, 3, 4, 5});
    assert(nonNegative.lowerBoundPrefix(1) == 0);
    assert(nonNegative.lowerBoundPrefix(3) == 1);
    assert(nonNegative.lowerBoundPrefix(15) == 4);
    assert(nonNegative.lowerBoundPrefix(16) == -1);

    FenwickRange range({1, 2, 3, 4, 5});
    RangeQueryOracle rangeOracle({1, 2, 3, 4, 5});
    range.rangeAdd(1, 3, 7);
    rangeOracle.rangeAdd(1, 3, 7);
    range.rangeAdd(0, 4, -1);
    rangeOracle.rangeAdd(0, 4, -1);
    for (int l = 0; l < 5; ++l) {
        for (int r = l; r < 5; ++r) {
            assert(range.rangeSum(l, r) == rangeOracle.rangeSum(l, r));
        }
    }

    FenwickTree2D bit2d({{1, 2}, {3, 4}});
    assert(bit2d.rectangleSum(0, 0, 1, 1) == 10);
    bit2d.add(0, 1, 5);
    assert(bit2d.rectangleSum(0, 1, 1, 1) == 11);

    std::cout << "Pruebas Fenwick Semana12 aprobadas\n";
    return 0;
}
