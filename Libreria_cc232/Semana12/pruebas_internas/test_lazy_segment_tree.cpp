#include "CapituloConsultasRango.h"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {1, 2, 3, 4, 5, 6};
    LazySegmentTree lazy(values);
    RangeQueryOracle oracle(values);

    lazy.rangeAdd(1, 4, 10);
    oracle.rangeAdd(1, 4, 10);
    lazy.rangeAdd(0, 2, -3);
    oracle.rangeAdd(0, 2, -3);

    for (int l = 0; l < 6; ++l) {
        for (int r = l; r < 6; ++r) {
            assert(lazy.rangeSum(l, r) == oracle.rangeSum(l, r));
        }
    }

    AssignmentLazySegmentTree assignTree(values);
    RangeQueryOracle assignOracle(values);
    assignTree.rangeAssign(2, 5, 9);
    assignOracle.rangeAssign(2, 5, 9);
    assignTree.rangeAssign(0, 1, -4);
    assignOracle.rangeAssign(0, 1, -4);

    for (int l = 0; l < 6; ++l) {
        for (int r = l; r < 6; ++r) {
            assert(assignTree.rangeSum(l, r) == assignOracle.rangeSum(l, r));
        }
    }

    std::cout << "Pruebas lazy propagation Semana12 aprobadas\n";
    return 0;
}
