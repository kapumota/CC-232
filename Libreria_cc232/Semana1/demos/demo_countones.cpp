#include <bitset>
#include <iostream>

#include "count_ones.h"

int main() {
    const unsigned int x = 0b101101001u;
    std::cout << "x = " << x << " = " << std::bitset<16>(x) << "\n";
    std::cout << "countOnes1(x) = " << countOnes1(x) << "\n";
    std::cout << "countOnes2(x) = " << countOnes2(x) << "\n";
    std::cout << "Idea: una version elimina el ultimo 1, la otra agrupa bits por bloques.\n";
    return 0;
}
