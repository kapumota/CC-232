#include "CapituloConsultasRango.h"

#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;

    std::vector<long long> values = {5, 2, 9, 1, 7, 3, 8, 4};
    FenwickTree bit(values);

    std::cout << "### Demo: Fenwick Tree\n";
    std::cout << "Suma [1, 4]: " << bit.rangeSum(1, 4) << "\n";
    bit.add(3, 10);
    std::cout << "Despues de sumar 10 en posicion 3, suma [1, 4]: " << bit.rangeSum(1, 4) << "\n";
    std::cout << "Primer indice con prefijo al menos 20: " << bit.lowerBoundPrefix(20) << "\n";

    FenwickRange rangeBit(values);
    rangeBit.rangeAdd(2, 6, 5);
    std::cout << "FenwickRange suma [2, 6] despues de rangeAdd: " << rangeBit.rangeSum(2, 6) << "\n";
    return 0;
}
