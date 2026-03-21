#include <iostream>

#include "bubble_sort.h"

namespace {
void printArray(const int A[], int n) {
    std::cout << "[";
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << (i + 1 < n ? ", " : "");
    }
    std::cout << "]";
  }
}

int main() {
    int a[] = {5, 1, 4, 2, 8, 3};
    const int n = static_cast<int>(sizeof(a) / sizeof(a[0]));

    std::cout << "Estado inicial: ";
    printArray(a, n);
    std::cout << "\n";

    auto witnesses = inversionWitnesses(a, n);
    std::cout << "Indices con desorden local A[i] > A[i+1]: ";
    if (witnesses.empty()) {
        std::cout << "ninguno\n";
    } else {
        for (int idx : witnesses) std::cout << idx << ' ';
        std::cout << "\n";
    }

    const BubbleStats stats = bubbleSortOptimized(a, n);
    std::cout << "Tras bubbleSortOptimized: ";
    printArray(a, n);
    std::cout << "\ncomparaciones = " << stats.comparisons
              << ", intercambios = " << stats.swaps
              << ", ultimo swap = " << stats.lastSwapIndex << "\n";
    std::cout << "Invariante observable: el sufijo despues del ultimo intercambio ya queda ordenado.\n";
    std::cout << "Arreglo ordenado globalmente? " << (isSortedNonDecreasing(a, n) ? "si" : "no") << "\n";
    return 0;
}
