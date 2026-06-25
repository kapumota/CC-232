#ifndef CC232_SEMANA10_SORTING_UTILS_H
#define CC232_SEMANA10_SORTING_UTILS_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace cc232 {

template <typename T, typename Compare>
bool isSortedBy(const std::vector<T>& values, Compare compare) {
  for (std::size_t i = 1; i < values.size(); ++i) {
    if (compare(values[i], values[i - 1])) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool isSorted(const std::vector<T>& values) {
  return isSortedBy(values, std::less<T>());
}

template <typename T>
std::vector<T> sortedCopy(std::vector<T> values) {
  std::sort(values.begin(), values.end());
  return values;
}

template <typename T>
bool sameMultiset(std::vector<T> left, std::vector<T> right) {
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());
  return left == right;
}

template <typename T, typename Key>
struct StableItem {
  Key key;
  T value;
  int originalIndex;

  bool operator==(const StableItem& other) const {
    return key == other.key && value == other.value && originalIndex == other.originalIndex;
  }
};

template <typename T, typename Key>
struct StableItemLess {
  bool operator()(const StableItem<T, Key>& left, const StableItem<T, Key>& right) const {
    return left.key < right.key;
  }
};

template <typename T, typename Key>
bool preservesRelativeOrderForEqualKeys(const std::vector<StableItem<T, Key>>& values) {
  for (std::size_t i = 1; i < values.size(); ++i) {
    if (values[i - 1].key == values[i].key &&
        values[i - 1].originalIndex > values[i].originalIndex) {
      return false;
    }
  }
  return true;
}

inline int checkedNonNegative(int value, const char* message) {
  if (value < 0) {
    throw std::invalid_argument(message);
  }
  return value;
}

}  // namespace cc232

#endif  // CC232_SEMANA10_SORTING_UTILS_H
