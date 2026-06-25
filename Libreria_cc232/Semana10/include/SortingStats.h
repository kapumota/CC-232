#ifndef CC232_SEMANA10_SORTING_STATS_H
#define CC232_SEMANA10_SORTING_STATS_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <string>

namespace cc232 {

struct SortStats {
  std::size_t comparisons = 0;
  std::size_t moves = 0;
  std::size_t swaps = 0;
  std::size_t partitions = 0;
  std::size_t recursionCalls = 0;
  std::size_t maxDepth = 0;
  std::size_t arrayReads = 0;
  std::size_t arrayWrites = 0;

  void observeDepth(std::size_t depth) { maxDepth = std::max(maxDepth, depth); }

  void reset() {
    comparisons = 0;
    moves = 0;
    swaps = 0;
    partitions = 0;
    recursionCalls = 0;
    maxDepth = 0;
    arrayReads = 0;
    arrayWrites = 0;
  }
};

template <typename Compare>
class CountingCompare {
 public:
  explicit CountingCompare(SortStats* stats, Compare compare = Compare())
      : stats_(stats), compare_(compare) {}

  template <typename T, typename U>
  bool operator()(const T& left, const U& right) const {
    if (stats_ != nullptr) {
      ++stats_->comparisons;
    }
    return compare_(left, right);
  }

 private:
  SortStats* stats_;
  Compare compare_;
};

template <typename Compare>
CountingCompare<Compare> makeCountingCompare(SortStats* stats, Compare compare) {
  return CountingCompare<Compare>(stats, compare);
}

template <typename T>
void countedSwap(T& left, T& right, SortStats* stats) {
  using std::swap;
  swap(left, right);
  if (stats != nullptr) {
    ++stats->swaps;
    stats->moves += 3;
    stats->arrayReads += 2;
    stats->arrayWrites += 2;
  }
}

template <typename T>
void countedAssign(T& destination, const T& source, SortStats* stats) {
  destination = source;
  if (stats != nullptr) {
    ++stats->moves;
    ++stats->arrayReads;
    ++stats->arrayWrites;
  }
}

inline std::string summarizeStats(const SortStats& stats) {
  return "comparaciones=" + std::to_string(stats.comparisons) +
         ", movimientos=" + std::to_string(stats.moves) +
         ", intercambios=" + std::to_string(stats.swaps) +
         ", particiones=" + std::to_string(stats.partitions) +
         ", profundidad_maxima=" + std::to_string(stats.maxDepth);
}

}  // namespace cc232

#endif  // CC232_SEMANA10_SORTING_STATS_H
