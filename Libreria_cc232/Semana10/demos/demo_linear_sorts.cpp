#include "CapituloOrdenamiento.h"

#include <iostream>
#include <vector>

using namespace cc232;

void printVector(const std::vector<int>& values) {
  for (int value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> smallValues{4, 1, 3, 4, 0, 2, 1, 3};
  SortStats countingStats;
  countingSort(smallValues, 4, &countingStats);
  std::cout << "CountingSort: ";
  printVector(smallValues);
  std::cout << summarizeStats(countingStats) << '\n';

  std::vector<int> signedValues{100, -4, 0, 19, -20, 7, 7};
  SortStats radixStats;
  radixSortSigned(signedValues, &radixStats);
  std::cout << "RadixSort signed: ";
  printVector(signedValues);
  std::cout << summarizeStats(radixStats) << '\n';

  return 0;
}
