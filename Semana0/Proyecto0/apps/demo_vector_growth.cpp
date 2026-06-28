#include <iostream>
#include <vector>

void printState(const std::vector<int>& values) {
    std::cout << "tamaño=" << values.size()
              << ", capacidad=" << values.capacity() << '\n';
}

int main() {
    std::cout << "Demostración STL: crecimiento de std::vector\n";

    std::vector<int> values;
    printState(values);

    for (int i = 0; i < 12; ++i) {
        values.push_back(i);
        printState(values);
    }

    std::cout << "Reserva explícita para evitar varias reubicaciones\n";
    values.reserve(64);
    printState(values);

    return 0;
}
