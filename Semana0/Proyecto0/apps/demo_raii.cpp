#include <iostream>
#include <string>
#include <vector>

namespace {

class ResourceGuard {
public:
    explicit ResourceGuard(std::string name)
        : name_(std::move(name)) {
        std::cout << "Adquiriendo recurso: " << name_ << '\n';
    }

    ~ResourceGuard() {
        std::cout << "Liberando recurso: " << name_ << '\n';
    }

    void addValue(int value) {
        values_.push_back(value);
    }

    int sum() const {
        int total = 0;
        for (const int value : values_) {
            total += value;
        }
        return total;
    }

private:
    std::string name_;
    std::vector<int> values_;
};

void runScopeExample() {
    ResourceGuard guard("buffer local");
    guard.addValue(7);
    guard.addValue(5);
    guard.addValue(3);

    std::cout << "Suma dentro del alcance: " << guard.sum() << '\n';
}

}  // namespace

int main() {
    std::cout << "Antes de entrar al alcance\n";
    runScopeExample();
    std::cout << "Despues de salir del alcance\n";

    std::cout << "RAII vincula recursos al ciclo de vida de objetos: se adquieren al construir y liberan al destruir..\n";
    return 0;
}
