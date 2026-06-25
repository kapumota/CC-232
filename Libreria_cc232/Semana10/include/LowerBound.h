#ifndef CC232_SEMANA10_LOWER_BOUND_H
#define CC232_SEMANA10_LOWER_BOUND_H

#include <cmath>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>

namespace cc232 {

inline long double log2Factorial(std::size_t n) {
  long double total = 0.0L;
  for (std::size_t value = 2; value <= n; ++value) {
    total += std::log2(static_cast<long double>(value));
  }
  return total;
}

inline std::size_t ceilLog2Factorial(std::size_t n) {
  const long double value = log2Factorial(n);
  return static_cast<std::size_t>(std::ceil(value - 1e-12L));
}

inline long double stirlingLowerApproximation(std::size_t n) {
  if (n < 2) {
    return 0.0L;
  }
  const long double x = static_cast<long double>(n);
  return x * std::log2(x) - x * std::log2(std::exp(1.0L));
}

inline long double comparisonLowerBound(std::size_t n) {
  return log2Factorial(n);
}

inline bool canDecisionTreeHeightDistinguish(std::size_t n, std::size_t height) {
  return static_cast<long double>(height) + 1e-12L >= log2Factorial(n);
}

inline std::string lowerBoundExplanation(std::size_t n) {
  return "Para ordenar " + std::to_string(n) +
         " elementos distintos mediante comparaciones se deben distinguir " +
         std::to_string(n) + "! permutaciones. Un arbol binario de decision con altura h "
         "tiene a lo mas 2^h hojas. Por eso h >= log2(" + std::to_string(n) +
         "!) = " + std::to_string(static_cast<double>(log2Factorial(n))) + ".";
}

}  // namespace cc232

#endif  // CC232_SEMANA10_LOWER_BOUND_H
