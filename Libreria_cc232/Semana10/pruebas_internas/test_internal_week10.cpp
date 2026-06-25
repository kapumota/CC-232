#include "CapituloOrdenamiento.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace cc232;

void assertAllComparisonSorts(const std::vector<int>& input) {
  const auto expected = sortedCopy(input);
  std::vector<int> values;

  values = input;
  bubbleSort(values);
  assert(values == expected);

  values = input;
  selectionSort(values);
  assert(values == expected);

  values = input;
  insertionSort(values);
  assert(values == expected);

  values = input;
  mergeSort(values);
  assert(values == expected);

  values = input;
  quickSort(values);
  assert(values == expected);

  values = input;
  quickSortIterative(values);
  assert(values == expected);

  values = input;
  heapSort(values);
  assert(values == expected);

  values = input;
  shellSort(values);
  assert(values == expected);

  values = input;
  introSort(values);
  assert(values == expected);
}

void testEdgeCases() {
  assertAllComparisonSorts({});
  assertAllComparisonSorts({1});
  assertAllComparisonSorts({2, 1});
  assertAllComparisonSorts({1, 1, 1, 1});
  assertAllComparisonSorts({9, 8, 7, 6, 5, 4, 3, 2, 1});
  assertAllComparisonSorts({-5, 10, 0, -2, 10, 7, 7, -5});
}

void testStatsAreCollected() {
  std::vector<int> values{6, 5, 4, 3, 2, 1};
  SortStats stats;
  quickSort(values, &stats);
  assert(isSorted(values));
  assert(stats.comparisons > 0);
  assert(stats.moves > 0);
}

int main() {
  testEdgeCases();
  testStatsAreCollected();
  std::cout << "Pruebas internas Semana10 completadas\n";
  return 0;
}
