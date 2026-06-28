#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Demo STL: invalidación de iteradores en std::vector\n";

    std::vector<int> values;
    values.reserve(2);
    values.push_back(10);
    values.push_back(20);

    auto iterator = values.begin();
    const std::size_t logicalIndex = 0;

    std::cout << "Valor antes de crecer: " << *iterator << '\n';

    // Esta inserción puede reubicar la memoria interna del vector.
    values.push_back(30);

    // No se usa el iterador anterior. Se recupera la posición mediante índice.
    auto refreshedIterator = values.begin() + static_cast<std::ptrdiff_t>(logicalIndex);

    std::cout << "Valor después de recuperar el iterador: "
              << *refreshedIterator << '\n';

    return 0;
}
