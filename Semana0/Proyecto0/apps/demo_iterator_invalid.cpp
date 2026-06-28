#include <iostream>
#include <vector>

int main() {
    std::cout << "Demo ASan: uso de iterador invalidado\n";

    std::vector<int> values;
    values.reserve(1);
    values.push_back(10);

    auto iterator = values.begin();

    // Este push_back puede reubicar el arreglo interno e invalidar el iterador.
    values.push_back(20);

    std::cout << "Valor leído desde un iterador inválido: " << *iterator << '\n';

    return 0;
}
