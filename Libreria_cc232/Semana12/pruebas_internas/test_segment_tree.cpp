#include "CapituloConsultasRango.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {4, -2, 7, 1, 0, 5, -3};
    SegmentTree recursive(values);
    IterativeSegmentTree iterative(values);
    RangeQueryOracle oracle(values);

    for (int l = 0; l < static_cast<int>(values.size()); ++l) {
        for (int r = l; r < static_cast<int>(values.size()); ++r) {
            assert(recursive.rangeSum(l, r) == oracle.rangeSum(l, r));
            assert(iterative.rangeSum(l, r) == oracle.rangeSum(l, r));
        }
    }

    recursive.pointSet(2, 100);
    iterative.pointSet(2, 100);
    oracle.pointSet(2, 100);
    assert(recursive.rangeSum(0, 6) == oracle.rangeSum(0, 6));
    assert(iterative.rangeSum(2, 4) == oracle.rangeSum(2, 4));

    MonoidSegmentTree<long long> minTree(oracle.values(), std::numeric_limits<long long>::max(),
                                         [](const long long& a, const long long& b) { return std::min(a, b); });
    assert(minTree.rangeQuery(0, 6) == oracle.rangeMin(0, 6));

    MaxSubarraySegmentTree maxTree({-2, 1, -3, 4, -1, 2, 1, -5, 4});
    assert(maxTree.rangeMaxSubarray(0, 8) == 6);
    maxTree.pointSet(4, 10);
    assert(maxTree.rangeMaxSubarray(0, 8) == 17);

    std::cout << "Pruebas SegmentTree Semana12 aprobadas\n";
    return 0;
}
