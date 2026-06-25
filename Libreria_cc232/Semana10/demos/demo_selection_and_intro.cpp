#include "CapituloOrdenamiento.h"

#include <iostream>
#include <vector>

using namespace cc232;

int main() {
  std::vector<int> values{12, 4, 7, 1, 9, 2, 10, 3, 8, 5, 6, 11};
  SortStats selectStats;
  const int kth = quickSelect(values, 4, &selectStats);
  std::cout << "El quinto menor elemento es " << kth << '\n';
  std::cout << summarizeStats(selectStats) << '\n';

  SortStats introStats;
  introSort(values, &introStats);
  std::cout << "IntroSort ordeno " << values.size() << " elementos\n";
  std::cout << summarizeStats(introStats) << '\n';

  std::cout << "Inversiones en {3, 1, 2}: "
            << countInversions(std::vector<int>{3, 1, 2}) << '\n';
  return 0;
}
