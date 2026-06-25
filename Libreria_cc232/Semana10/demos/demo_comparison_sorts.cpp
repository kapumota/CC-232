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
  std::vector<int> base{7, 2, 9, 1, 5, 3, 8, 4, 6};

  std::vector<int> mergeValues = base;
  SortStats mergeStats;
  mergeSort(mergeValues, &mergeStats);
  std::cout << "MergeSort: ";
  printVector(mergeValues);
  std::cout << summarizeStats(mergeStats) << '\n';

  std::vector<int> quickValues = base;
  SortStats quickStats;
  quickSort(quickValues, &quickStats);
  std::cout << "QuickSort: ";
  printVector(quickValues);
  std::cout << summarizeStats(quickStats) << '\n';

  std::vector<int> heapValues = base;
  SortStats heapStats;
  heapSort(heapValues, &heapStats);
  std::cout << "HeapSort: ";
  printVector(heapValues);
  std::cout << summarizeStats(heapStats) << '\n';

  return 0;
}
