#ifndef CC232_SEMANA10_LINEAR_SORTS_H
#define CC232_SEMANA10_LINEAR_SORTS_H

#include "SortingStats.h"
#include "SortingUtils.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace cc232 {

inline void countingSort(std::vector<int>& values, int maxValue,
                         SortStats* stats = nullptr) {
  if (maxValue < 0) {
    throw std::invalid_argument("El maximo debe ser no negativo");
  }
  std::vector<int> counts(static_cast<std::size_t>(maxValue) + 1, 0);

  for (int value : values) {
    if (value < 0 || value > maxValue) {
      throw std::invalid_argument("Valor fuera del rango permitido para counting sort");
    }
    ++counts[static_cast<std::size_t>(value)];
    if (stats != nullptr) {
      ++stats->arrayReads;
      ++stats->arrayWrites;
    }
  }

  std::size_t index = 0;
  for (std::size_t value = 0; value < counts.size(); ++value) {
    while (counts[value] > 0) {
      values[index++] = static_cast<int>(value);
      --counts[value];
      if (stats != nullptr) {
        ++stats->moves;
        ++stats->arrayWrites;
      }
    }
  }
}

inline std::vector<int> countingSortStableByKey(const std::vector<int>& values, int maxValue,
                                                SortStats* stats = nullptr) {
  if (maxValue < 0) {
    throw std::invalid_argument("El maximo debe ser no negativo");
  }
  std::vector<int> counts(static_cast<std::size_t>(maxValue) + 1, 0);
  for (int value : values) {
    if (value < 0 || value > maxValue) {
      throw std::invalid_argument("Valor fuera del rango permitido para counting sort estable");
    }
    ++counts[static_cast<std::size_t>(value)];
  }
  for (std::size_t i = 1; i < counts.size(); ++i) {
    counts[i] += counts[i - 1];
  }
  std::vector<int> output(values.size());
  for (std::size_t i = values.size(); i > 0; --i) {
    const int value = values[i - 1];
    const std::size_t position = static_cast<std::size_t>(--counts[static_cast<std::size_t>(value)]);
    output[position] = value;
    if (stats != nullptr) {
      ++stats->moves;
      ++stats->arrayReads;
      ++stats->arrayWrites;
    }
  }
  return output;
}

template <typename Item, typename KeyFunction>
std::vector<Item> countingSortByKeyStable(const std::vector<Item>& values, int maxValue,
                                          KeyFunction keyOf, SortStats* stats = nullptr) {
  if (maxValue < 0) {
    throw std::invalid_argument("El maximo debe ser no negativo");
  }
  std::vector<int> counts(static_cast<std::size_t>(maxValue) + 1, 0);
  for (const auto& item : values) {
    const int key = keyOf(item);
    if (key < 0 || key > maxValue) {
      throw std::invalid_argument("Clave fuera del rango permitido");
    }
    ++counts[static_cast<std::size_t>(key)];
  }
  for (std::size_t i = 1; i < counts.size(); ++i) {
    counts[i] += counts[i - 1];
  }
  std::vector<Item> output(values.size());
  for (std::size_t i = values.size(); i > 0; --i) {
    const auto& item = values[i - 1];
    const int key = keyOf(item);
    const std::size_t position = static_cast<std::size_t>(--counts[static_cast<std::size_t>(key)]);
    output[position] = item;
    if (stats != nullptr) {
      ++stats->moves;
      ++stats->arrayReads;
      ++stats->arrayWrites;
    }
  }
  return output;
}

inline void lsdRadixSort(std::vector<unsigned int>& values, SortStats* stats = nullptr) {
  constexpr int base = 256;
  constexpr int passes = 4;
  std::vector<unsigned int> output(values.size());

  for (int pass = 0; pass < passes; ++pass) {
    std::array<std::size_t, base> counts{};
    const int shift = pass * 8;

    for (unsigned int value : values) {
      ++counts[(value >> shift) & 0xFFu];
      if (stats != nullptr) {
        ++stats->arrayReads;
      }
    }

    std::size_t total = 0;
    for (std::size_t i = 0; i < counts.size(); ++i) {
      const std::size_t old = counts[i];
      counts[i] = total;
      total += old;
    }

    for (unsigned int value : values) {
      const std::size_t bucket = (value >> shift) & 0xFFu;
      output[counts[bucket]++] = value;
      if (stats != nullptr) {
        ++stats->moves;
        ++stats->arrayWrites;
      }
    }

    values.swap(output);
    if (stats != nullptr) {
      ++stats->swaps;
    }
  }
}

inline void radixSortSigned(std::vector<int>& values, SortStats* stats = nullptr) {
  std::vector<unsigned int> transformed(values.size());
  constexpr unsigned int signMask = 0x80000000u;
  for (std::size_t i = 0; i < values.size(); ++i) {
    transformed[i] = static_cast<unsigned int>(values[i]) ^ signMask;
  }
  lsdRadixSort(transformed, stats);
  for (std::size_t i = 0; i < values.size(); ++i) {
    values[i] = static_cast<int>(transformed[i] ^ signMask);
    if (stats != nullptr) {
      ++stats->moves;
      ++stats->arrayWrites;
    }
  }
}

}  // namespace cc232

#endif  // CC232_SEMANA10_LINEAR_SORTS_H
