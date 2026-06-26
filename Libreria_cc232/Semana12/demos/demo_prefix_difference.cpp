#include "CapituloConsultasRango.h"

#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {3, 1, 4, 1, 5, 9};
    auto prefix = buildPrefixSums(values);

    std::cout << "### Demo: sumas de prefijo y arreglo de diferencias\n";
    std::cout << "Suma del rango [1, 4]: " << rangeSumFromPrefix(prefix, 1, 4) << "\n";

    DifferenceArray diff(values);
    diff.rangeAdd(2, 5, 10);
    auto updated = diff.materialize();

    std::cout << "Despues de sumar 10 al rango [2, 5]: ";
    for (long long value : updated) {
        std::cout << value << ' ';
    }
    std::cout << "\n";

    PrefixSum2D prefix2d({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::cout << "Suma del rectangulo (1,1)-(2,2): " << prefix2d.rectangleSum(1, 1, 2, 2) << "\n";
    return 0;
}
