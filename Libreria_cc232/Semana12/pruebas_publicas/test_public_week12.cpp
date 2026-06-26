#include "CapituloConsultasRango.h"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {1, 2, 3, 4, 5};
    auto prefix = buildPrefixSums(values);
    assert(rangeSumFromPrefix(prefix, 0, 4) == 15);
    assert(rangeSumFromPrefix(prefix, 1, 3) == 9);

    DifferenceArray diff(values);
    diff.rangeAdd(1, 3, 10);
    auto updated = diff.materialize();
    assert((updated == std::vector<long long>{1, 12, 13, 14, 5}));

    FenwickTree bit(values);
    assert(bit.rangeSum(0, 4) == 15);
    bit.add(2, 7);
    assert(bit.rangeSum(2, 2) == 10);

    SegmentTree segment(values);
    assert(segment.rangeSum(1, 3) == 9);
    segment.pointSet(1, 20);
    assert(segment.rangeSum(0, 2) == 24);

    auto minTable = makeMinSparseTable({5, 3, 8, 2, 7});
    assert(minTable.query(1, 4) == 2);

    std::cout << "Pruebas publicas Semana12 aprobadas\n";
    return 0;
}
