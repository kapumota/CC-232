#ifndef CC232_SEMANA10_COMPARISON_SORTS_H
#define CC232_SEMANA10_COMPARISON_SORTS_H

#include "SortingStats.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace cc232 {

template <typename T, typename Compare = std::less<T>>
void bubbleSort(std::vector<T>& values, SortStats* stats = nullptr,
                Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  if (values.size() < 2) {
    return;
  }
  for (std::size_t end = values.size(); end > 1; --end) {
    bool changed = false;
    for (std::size_t i = 1; i < end; ++i) {
      if (less(values[i], values[i - 1])) {
        countedSwap(values[i], values[i - 1], stats);
        changed = true;
      }
    }
    if (!changed) {
      break;
    }
  }
}

template <typename T, typename Compare = std::less<T>>
void selectionSort(std::vector<T>& values, SortStats* stats = nullptr,
                   Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  for (std::size_t i = 0; i < values.size(); ++i) {
    std::size_t best = i;
    for (std::size_t j = i + 1; j < values.size(); ++j) {
      if (less(values[j], values[best])) {
        best = j;
      }
    }
    if (best != i) {
      countedSwap(values[i], values[best], stats);
    }
  }
}

template <typename T, typename Compare = std::less<T>>
void insertionSort(std::vector<T>& values, SortStats* stats = nullptr,
                   Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  for (std::size_t i = 1; i < values.size(); ++i) {
    T current = values[i];
    if (stats != nullptr) {
      ++stats->moves;
      ++stats->arrayReads;
    }
    std::size_t j = i;
    while (j > 0 && less(current, values[j - 1])) {
      countedAssign(values[j], values[j - 1], stats);
      --j;
    }
    countedAssign(values[j], current, stats);
  }
}

template <typename T, typename Compare>
void mergeInto(std::vector<T>& values, std::vector<T>& buffer, std::size_t left,
               std::size_t middle, std::size_t right, SortStats* stats,
               Compare less) {
  std::size_t i = left;
  std::size_t j = middle;
  std::size_t k = left;

  while (i < middle && j < right) {
    if (less(values[j], values[i])) {
      countedAssign(buffer[k], values[j], stats);
      ++j;
    } else {
      countedAssign(buffer[k], values[i], stats);
      ++i;
    }
    ++k;
  }

  while (i < middle) {
    countedAssign(buffer[k], values[i], stats);
    ++i;
    ++k;
  }

  while (j < right) {
    countedAssign(buffer[k], values[j], stats);
    ++j;
    ++k;
  }

  for (std::size_t p = left; p < right; ++p) {
    countedAssign(values[p], buffer[p], stats);
  }
}

template <typename T, typename Compare>
void mergeSortRange(std::vector<T>& values, std::vector<T>& buffer, std::size_t left,
                    std::size_t right, SortStats* stats, Compare less,
                    std::size_t depth) {
  if (stats != nullptr) {
    ++stats->recursionCalls;
    stats->observeDepth(depth);
  }
  if (right - left <= 1) {
    return;
  }
  const std::size_t middle = left + (right - left) / 2;
  mergeSortRange(values, buffer, left, middle, stats, less, depth + 1);
  mergeSortRange(values, buffer, middle, right, stats, less, depth + 1);
  mergeInto(values, buffer, left, middle, right, stats, less);
}

template <typename T, typename Compare = std::less<T>>
void mergeSort(std::vector<T>& values, SortStats* stats = nullptr,
               Compare compare = Compare()) {
  std::vector<T> buffer(values);
  auto less = makeCountingCompare(stats, compare);
  mergeSortRange(values, buffer, 0, values.size(), stats, less, 1);
}

template <typename T, typename Compare>
std::size_t partitionRange(std::vector<T>& values, std::size_t left, std::size_t right,
                           SortStats* stats, Compare less) {
  if (right <= left) {
    return left;
  }
  if (stats != nullptr) {
    ++stats->partitions;
  }

  const std::size_t middle = left + (right - left) / 2;
  if (less(values[middle], values[left])) {
    countedSwap(values[middle], values[left], stats);
  }
  if (less(values[right - 1], values[left])) {
    countedSwap(values[right - 1], values[left], stats);
  }
  if (less(values[right - 1], values[middle])) {
    countedSwap(values[right - 1], values[middle], stats);
  }

  countedSwap(values[middle], values[right - 1], stats);
  const T pivot = values[right - 1];
  if (stats != nullptr) {
    ++stats->moves;
    ++stats->arrayReads;
  }

  std::size_t store = left;
  for (std::size_t i = left; i + 1 < right; ++i) {
    if (less(values[i], pivot)) {
      countedSwap(values[i], values[store], stats);
      ++store;
    }
  }
  countedSwap(values[store], values[right - 1], stats);
  return store;
}

template <typename T, typename Compare>
void quickSortRange(std::vector<T>& values, std::size_t left, std::size_t right,
                    SortStats* stats, Compare less, std::size_t depth) {
  if (stats != nullptr) {
    ++stats->recursionCalls;
    stats->observeDepth(depth);
  }
  if (right - left <= 16) {
    for (std::size_t i = left + 1; i < right; ++i) {
      T current = values[i];
      if (stats != nullptr) {
        ++stats->moves;
        ++stats->arrayReads;
      }
      std::size_t j = i;
      while (j > left && less(current, values[j - 1])) {
        countedAssign(values[j], values[j - 1], stats);
        --j;
      }
      countedAssign(values[j], current, stats);
    }
    return;
  }

  const std::size_t pivot = partitionRange(values, left, right, stats, less);
  quickSortRange(values, left, pivot, stats, less, depth + 1);
  quickSortRange(values, pivot + 1, right, stats, less, depth + 1);
}

template <typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T>& values, SortStats* stats = nullptr,
               Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  quickSortRange(values, 0, values.size(), stats, less, 1);
}

template <typename T, typename Compare = std::less<T>>
void quickSortIterative(std::vector<T>& values, SortStats* stats = nullptr,
                        Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  if (values.size() < 2) {
    return;
  }

  std::vector<std::pair<std::size_t, std::size_t>> stack;
  stack.push_back({0, values.size()});

  while (!stack.empty()) {
    const auto [left, right] = stack.back();
    stack.pop_back();
    if (right - left <= 16) {
      for (std::size_t i = left + 1; i < right; ++i) {
        T current = values[i];
        if (stats != nullptr) {
          ++stats->moves;
          ++stats->arrayReads;
        }
        std::size_t j = i;
        while (j > left && less(current, values[j - 1])) {
          countedAssign(values[j], values[j - 1], stats);
          --j;
        }
        countedAssign(values[j], current, stats);
      }
      continue;
    }

    const std::size_t pivot = partitionRange(values, left, right, stats, less);
    const std::size_t leftSize = pivot - left;
    const std::size_t rightSize = right - (pivot + 1);
    if (leftSize > rightSize) {
      stack.push_back({left, pivot});
      stack.push_back({pivot + 1, right});
    } else {
      stack.push_back({pivot + 1, right});
      stack.push_back({left, pivot});
    }
  }
}

template <typename T, typename Compare = std::less<T>>
void heapSort(std::vector<T>& values, SortStats* stats = nullptr,
              Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  auto heapLess = [&less](const T& left, const T& right) { return less(left, right); };
  std::make_heap(values.begin(), values.end(), heapLess);
  std::sort_heap(values.begin(), values.end(), heapLess);
  if (stats != nullptr) {
    stats->moves += values.size() * 2;
  }
}

template <typename T, typename Compare = std::less<T>>
void shellSort(std::vector<T>& values, SortStats* stats = nullptr,
               Compare compare = Compare()) {
  auto less = makeCountingCompare(stats, compare);
  for (std::size_t gap = values.size() / 2; gap > 0; gap /= 2) {
    for (std::size_t i = gap; i < values.size(); ++i) {
      T current = values[i];
      if (stats != nullptr) {
        ++stats->moves;
        ++stats->arrayReads;
      }
      std::size_t j = i;
      while (j >= gap && less(current, values[j - gap])) {
        countedAssign(values[j], values[j - gap], stats);
        j -= gap;
      }
      countedAssign(values[j], current, stats);
    }
  }
}

template <typename T, typename Compare>
void introSortRange(std::vector<T>& values, std::size_t left, std::size_t right,
                    int depthLimit, SortStats* stats, Compare less) {
  if (right - left <= 16) {
    for (std::size_t i = left + 1; i < right; ++i) {
      T current = values[i];
      if (stats != nullptr) {
        ++stats->moves;
        ++stats->arrayReads;
      }
      std::size_t j = i;
      while (j > left && less(current, values[j - 1])) {
        countedAssign(values[j], values[j - 1], stats);
        --j;
      }
      countedAssign(values[j], current, stats);
    }
    return;
  }

  if (depthLimit <= 0) {
    std::make_heap(values.begin() + static_cast<std::ptrdiff_t>(left),
                   values.begin() + static_cast<std::ptrdiff_t>(right), less);
    std::sort_heap(values.begin() + static_cast<std::ptrdiff_t>(left),
                   values.begin() + static_cast<std::ptrdiff_t>(right), less);
    return;
  }

  const std::size_t pivot = partitionRange(values, left, right, stats, less);
  introSortRange(values, left, pivot, depthLimit - 1, stats, less);
  introSortRange(values, pivot + 1, right, depthLimit - 1, stats, less);
}

template <typename T, typename Compare = std::less<T>>
void introSort(std::vector<T>& values, SortStats* stats = nullptr,
               Compare compare = Compare()) {
  if (values.size() < 2) {
    return;
  }
  auto less = makeCountingCompare(stats, compare);
  const int depthLimit = 2 * static_cast<int>(std::log2(values.size()));
  introSortRange(values, 0, values.size(), depthLimit, stats, less);
}

template <typename T, typename Compare = std::less<T>>
long long countInversions(std::vector<T> values, Compare compare = Compare()) {
  long long inversions = 0;
  std::vector<T> buffer(values.size());

  std::function<void(std::size_t, std::size_t)> solve = [&](std::size_t left,
                                                            std::size_t right) {
    if (right - left <= 1) {
      return;
    }
    const std::size_t middle = left + (right - left) / 2;
    solve(left, middle);
    solve(middle, right);

    std::size_t i = left;
    std::size_t j = middle;
    std::size_t k = left;
    while (i < middle && j < right) {
      if (!compare(values[j], values[i])) {
        buffer[k++] = values[i++];
      } else {
        buffer[k++] = values[j++];
        inversions += static_cast<long long>(middle - i);
      }
    }
    while (i < middle) {
      buffer[k++] = values[i++];
    }
    while (j < right) {
      buffer[k++] = values[j++];
    }
    for (std::size_t p = left; p < right; ++p) {
      values[p] = buffer[p];
    }
  };

  solve(0, values.size());
  return inversions;
}

}  // namespace cc232

#endif  // CC232_SEMANA10_COMPARISON_SORTS_H
