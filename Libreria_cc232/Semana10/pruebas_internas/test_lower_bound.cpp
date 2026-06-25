#include "CapituloOrdenamiento.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace cc232;

void testKnownValues() {
  assert(ceilLog2Factorial(1) == 0);
  assert(ceilLog2Factorial(2) == 1);
  assert(ceilLog2Factorial(3) == 3);
  assert(ceilLog2Factorial(4) == 5);
  assert(ceilLog2Factorial(5) == 7);
}

void testMonotonicity() {
  for (std::size_t n = 2; n <= 30; ++n) {
    assert(log2Factorial(n) > log2Factorial(n - 1));
  }
}

void testStirlingLowerApproximation() {
  for (std::size_t n = 3; n <= 50; ++n) {
    assert(stirlingLowerApproximation(n) <= log2Factorial(n));
  }
}

int main() {
  testKnownValues();
  testMonotonicity();
  testStirlingLowerApproximation();
  std::cout << "Pruebas de lower bound Semana10 completadas\n";
  return 0;
}
