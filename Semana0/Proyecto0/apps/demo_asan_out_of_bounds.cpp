#include <iostream>
#include <vector>

int main() {
    std::cout << "Demostracion ASan: acceso fuera de rango en un vector\n";

    std::vector<int> values{10, 20, 30};

    // Este acceso es intencionalmente incorrecto para que ASan lo detecte.
    const std::size_t invalidIndex = values.size();
    std::cout << "Valor fuera de rango: " << values[invalidIndex] << '\n';

    return 0;
}
