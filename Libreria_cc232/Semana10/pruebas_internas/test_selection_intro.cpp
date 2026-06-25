#include "CapituloOrdenamiento.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace cc232;

void testQuickSelect() {
  std::vector<int> values{10, 3, 5, 7, 2, 9, 1};
  assert(quickSelect(values, 0) == 1);
  assert(quickSelect(values, 3) == 5);
  assert(quickSelect(values, 6) == 10);
}

void testSmallestK() {
  std::vector<int> values{9, 4, 1, 7, 3, 8, 2};
  const auto result = smallestK(values, 4);
  assert((result == std::vector<int>{1, 2, 3, 4}));
}

void testIntroSort() {
  std::vector<int> values;
  for (int value = 100; value >= 1; --value) {
    values.push_back(value);
  }
  SortStats stats;
  introSort(values, &stats);
  assert(isSorted(values));
  assert(stats.comparisons > 0);
}

int main() {
  testQuickSelect();
  testSmallestK();
  testIntroSort();
  std::cout << "Pruebas de seleccion e introsort Semana10 completadas\n";
  return 0;
}
