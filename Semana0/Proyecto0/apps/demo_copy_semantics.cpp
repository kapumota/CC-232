#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {

struct SharedBox {
    std::shared_ptr<std::vector<int>> values;
};

struct DeepBox {
    std::vector<int> values;
};

void printVector(const std::string& label, const std::vector<int>& values) {
    std::cout << label << ": {";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 != values.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "}\n";
}

void printSharedBox(const std::string& label, const SharedBox& box) {
    printVector(label, *box.values);
}

void printDeepBox(const std::string& label, const DeepBox& box) {
    printVector(label, box.values);
}

}  // namespace

int main() {
    std::cout << "Demostracion de copia superficial controlada\n";

    SharedBox sharedOriginal{std::make_shared<std::vector<int>>(std::vector<int>{1, 2, 3})};
    SharedBox sharedCopy = sharedOriginal;

    sharedCopy.values->push_back(4);

    printSharedBox("Original compartido", sharedOriginal);
    printSharedBox("Copia compartida", sharedCopy);

    std::cout << "\nDemostracion de copia profunda con std::vector\n";

    DeepBox deepOriginal{{10, 20, 30}};
    DeepBox deepCopy = deepOriginal;

    deepCopy.values.push_back(40);

    printDeepBox("Original profundo", deepOriginal);
    printDeepBox("Copia profunda", deepCopy);

    std::cout << "\nConclusion: copiar no siempre significa lo mismo.\n";
    std::cout << "Hay que distinguir propiedad compartida y datos duplicados.\n";

    return 0;
}
