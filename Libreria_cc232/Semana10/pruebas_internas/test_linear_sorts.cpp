#include "CapituloOrdenamiento.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace cc232;

void testCountingSortRange() {
  std::vector<int> values{0, 5, 2, 5, 1, 4, 3};
  countingSort(values, 5);
  assert((values == std::vector<int>{0, 1, 2, 3, 4, 5, 5}));
}

void testCountingSortRejectsInvalidRange() {
  bool failed = false;
  try {
    std::vector<int> values{0, 2, 5};
    countingSort(values, 3);
  } catch (const std::invalid_argument&) {
    failed = true;
  }
  assert(failed);
}

void testRadixSortSigned() {
  std::vector<int> values{2147483647, -1, 0, -2147483647, 42, -42};
  radixSortSigned(values);
  assert((values == std::vector<int>{-2147483647, -42, -1, 0, 42, 2147483647}));
}

int main() {
  testCountingSortRange();
  testCountingSortRejectsInvalidRange();
  testRadixSortSigned();
  std::cout << "Pruebas de ordenamiento lineal Semana10 completadas\n";
  return 0;
}
