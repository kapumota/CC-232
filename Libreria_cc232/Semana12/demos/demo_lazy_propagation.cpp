#include "CapituloConsultasRango.h"

#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {1, 2, 3, 4, 5, 6, 7, 8};
    LazySegmentTree addTree(values);

    std::cout << "### Demo: Lazy propagation\n";
    std::cout << "Suma inicial [0, 7]: " << addTree.rangeSum(0, 7) << "\n";
    addTree.rangeAdd(2, 5, 10);
    std::cout << "Suma despues de sumar 10 en [2, 5]: " << addTree.rangeSum(0, 7) << "\n";

    AssignmentLazySegmentTree assignTree(values);
    assignTree.rangeAssign(1, 3, 100);
    std::cout << "Suma despues de asignar 100 en [1, 3]: " << assignTree.rangeSum(0, 7) << "\n";
    return 0;
}
