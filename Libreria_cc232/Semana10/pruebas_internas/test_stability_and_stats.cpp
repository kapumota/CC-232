#include "CapituloOrdenamiento.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace cc232;

void testMergeSortIsStable() {
  using Item = StableItem<char, int>;
  std::vector<Item> values{{2, 'a', 0}, {1, 'b', 1}, {2, 'c', 2},
                           {1, 'd', 3}, {2, 'e', 4}};
  mergeSort(values, nullptr, StableItemLess<char, int>());
  assert(preservesRelativeOrderForEqualKeys(values));
}

void testCountingSortByKeyIsStable() {
  using Item = StableItem<char, int>;
  std::vector<Item> values{{2, 'a', 0}, {1, 'b', 1}, {2, 'c', 2},
                           {1, 'd', 3}, {2, 'e', 4}};
  auto sorted = countingSortByKeyStable(values, 2, [](const Item& item) {
    return item.key;
  });
  assert(preservesRelativeOrderForEqualKeys(sorted));
}

void testInversionCount() {
  assert(countInversions(std::vector<int>{}) == 0);
  assert(countInversions(std::vector<int>{1, 2, 3}) == 0);
  assert(countInversions(std::vector<int>{3, 2, 1}) == 3);
  assert(countInversions(std::vector<int>{2, 4, 1, 3, 5}) == 3);
}

int main() {
  testMergeSortIsStable();
  testCountingSortByKeyIsStable();
  testInversionCount();
  std::cout << "Pruebas de estabilidad y estadisticas Semana10 completadas\n";
  return 0;
}
