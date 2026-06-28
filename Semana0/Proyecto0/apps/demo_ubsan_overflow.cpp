#include <iostream>
#include <limits>

int main() {
    std::cout << "Demo UBSan: desbordamiento de entero con signo\n";

    int value = std::numeric_limits<int>::max();

    // Esta suma es intencionalmente incorrecta para que UBSan la detecte.
    int result = value + 1;

    std::cout << "Resultado no válido: " << result << '\n';

    return 0;
}
