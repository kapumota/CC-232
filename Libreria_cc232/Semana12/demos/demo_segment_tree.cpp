#include "CapituloConsultasRango.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {2, -1, 3, 7, 0, 4};
    SegmentTree recursive(values);
    IterativeSegmentTree iterative(values);

    std::cout << "### Demo: Segment Tree recursivo e iterativo\n";
    std::cout << "Suma recursiva [1, 4]: " << recursive.rangeSum(1, 4) << "\n";
    std::cout << "Suma iterativa [1, 4]: " << iterative.rangeSum(1, 4) << "\n";

    MonoidSegmentTree<long long> minTree(values, std::numeric_limits<long long>::max(),
                                         [](const long long& a, const long long& b) { return std::min(a, b); });
    std::cout << "Minimo [0, 5] con monoide: " << minTree.rangeQuery(0, 5) << "\n";

    MaxSubarraySegmentTree maxTree({-2, 1, -3, 4, -1, 2, 1, -5, 4});
    std::cout << "Maximo subarreglo [0, 8]: " << maxTree.rangeMaxSubarray(0, 8) << "\n";
    return 0;
}
