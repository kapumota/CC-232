#include "simple_array.h"

#include <iostream>
#include <string>

namespace {

void printNumbers(const cc232::SimpleArray<int>& values) {
    std::cout << "valores = [";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 != values.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

} // namespace

int main() {
    std::cout << "Demostracion de templates elemental\n";

    const int bestNumber = cc232::maximum(10, 7);
    const std::string bestWord = cc232::maximum(std::string{"arbol"}, std::string{"grafo"});

    std::cout << "maximo entero = " << bestNumber << '\n';
    std::cout << "maximo texto = " << bestWord << '\n';

    cc232::SimpleArray<int> values(4);
    values.fill(0);
    values[0] = 3;
    values[1] = 1;
    values[2] = 4;
    values[3] = 2;

    printNumbers(values);

    cc232::SimpleArray<int> copy = values;
    copy[0] = 99;

    std::cout << "despues de copiar y modificar la copia\n";
    std::cout << "original: ";
    printNumbers(values);
    std::cout << "copia: ";
    printNumbers(copy);

    return 0;
}
