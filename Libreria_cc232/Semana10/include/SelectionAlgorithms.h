#ifndef CC232_SEMANA10_SELECTION_ALGORITHMS_H
#define CC232_SEMANA10_SELECTION_ALGORITHMS_H

#include "ComparisonSorts.h"
#include "SortingStats.h"

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <vector>

namespace cc232 {

template <typename T, typename Compare = std::less<T>>
T quickSelect(std::vector<T> values, std::size_t k, SortStats* stats = nullptr,
              Compare compare = Compare()) {
  if (values.empty()) {
    throw std::invalid_argument("No se puede seleccionar en un arreglo vacio");
  }
  if (k >= values.size()) {
    throw std::out_of_range("Indice k fuera de rango");
  }

  auto less = makeCountingCompare(stats, compare);
  std::size_t left = 0;
  std::size_t right = values.size();

  while (right - left > 1) {
    const std::size_t pivot = partitionRange(values, left, right, stats, less);
    if (pivot == k) {
      return values[pivot];
    }
    if (k < pivot) {
      right = pivot;
    } else {
      left = pivot + 1;
    }
  }
  return values[left];
}

template <typename T, typename Compare = std::less<T>>
std::vector<T> smallestK(std::vector<T> values, std::size_t k,
                         SortStats* stats = nullptr, Compare compare = Compare()) {
  if (k > values.size()) {
    throw std::out_of_range("k no puede superar el tamano del arreglo");
  }
  if (k == 0) {
    return {};
  }

  const T boundary = quickSelect(values, k - 1, stats, compare);
  std::vector<T> result;
  result.reserve(k);
  for (const auto& value : values) {
    if (compare(value, boundary) || (!compare(boundary, value) && result.size() < k)) {
      result.push_back(value);
    }
    if (result.size() == k) {
      break;
    }
  }
  std::sort(result.begin(), result.end(), compare);
  return result;
}

}  // namespace cc232

#endif  // CC232_SEMANA10_SELECTION_ALGORITHMS_H
