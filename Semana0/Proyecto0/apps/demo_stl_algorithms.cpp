#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

void printValues(const std::vector<int>& values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::cout << "Demostracion STL: algoritmos y adaptadores\n";

    std::vector<int> values{7, 2, 9, 1, 5, 4, 8};

    std::cout << "Datos originales: ";
    printValues(values);

    std::sort(values.begin(), values.end());
    std::cout << "Después de std::sort: ";
    printValues(values);

    auto position = std::lower_bound(values.begin(), values.end(), 5);
    if (position != values.end()) {
        std::cout << "Primer valor mayor o igual que 5: " << *position << '\n';
    }

    std::vector<int> selection{7, 2, 9, 1, 5, 4, 8};
    auto middle = selection.begin() + static_cast<std::ptrdiff_t>(selection.size() / 2);
    std::nth_element(selection.begin(), middle, selection.end());
    std::cout << "Mediana por nth_element: " << *middle << '\n';

    std::vector<int> top{7, 2, 9, 1, 5, 4, 8};
    std::partial_sort(top.begin(), top.begin() + 3, top.end());
    std::cout << "Tres menores con partial_sort: ";
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << top[i] << ' ';
    }
    std::cout << '\n';

    std::priority_queue<int> priorities;
    for (int value : values) {
        priorities.push(value);
    }

    std::cout << "Prioridad máxima: " << priorities.top() << '\n';

    return 0;
}
