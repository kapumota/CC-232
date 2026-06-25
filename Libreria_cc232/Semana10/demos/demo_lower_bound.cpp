#include "CapituloOrdenamiento.h"

#include <iostream>

using namespace cc232;

int main() {
  for (std::size_t n = 2; n <= 12; ++n) {
    std::cout << "n=" << n << " lower_bound=ceil(log2(n!))="
              << ceilLog2Factorial(n) << " aproximacion="
              << static_cast<double>(stirlingLowerApproximation(n)) << '\n';
  }

  std::cout << lowerBoundExplanation(8) << '\n';
  return 0;
}
