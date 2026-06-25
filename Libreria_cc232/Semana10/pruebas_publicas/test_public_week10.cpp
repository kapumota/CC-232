#include "CapituloOrdenamiento.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace cc232;

void testComparisonSorts() {
  const std::vector<int> input{5, 1, 4, 2, 8, 0, 2};
  const std::vector<int> expected{0, 1, 2, 2, 4, 5, 8};

  std::vector<int> values = input;
  mergeSort(values);
  assert(values == expected);

  values = input;
  quickSort(values);
  assert(values == expected);

  values = input;
  heapSort(values);
  assert(values == expected);
}

void testLinearSorts() {
  std::vector<int> values{3, 1, 0, 3, 2, 1};
  countingSort(values, 3);
  assert((values == std::vector<int>{0, 1, 1, 2, 3, 3}));

  std::vector<int> signedValues{4, -3, 0, 9, -10, 4};
  radixSortSigned(signedValues);
  assert((signedValues == std::vector<int>{-10, -3, 0, 4, 4, 9}));
}

void testLowerBoundAndSelection() {
  assert(ceilLog2Factorial(3) == 3);
  assert(ceilLog2Factorial(4) == 5);
  assert(!canDecisionTreeHeightDistinguish(5, 5));
  assert(canDecisionTreeHeightDistinguish(5, 7));

  const int kth = quickSelect(std::vector<int>{9, 1, 4, 7, 2}, 2);
  assert(kth == 4);
}

int main() {
  testComparisonSorts();
  testLinearSorts();
  testLowerBoundAndSelection();
  std::cout << "Pruebas publicas Semana10 completadas\n";
  return 0;
}
