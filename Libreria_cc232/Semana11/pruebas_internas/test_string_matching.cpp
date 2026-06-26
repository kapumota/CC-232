#include <iostream>
#include <string>
#include <vector>

#include "CapituloCadenas.h"

#define CHECK(condition)                                                                  \
    do {                                                                                  \
        if (!(condition)) {                                                               \
            std::cerr << "Fallo en linea " << __LINE__ << ": " << #condition << '\n';    \
            return 1;                                                                     \
        }                                                                                 \
    } while (false)

int main() {
    using namespace cc232::semana11;

    std::string text = "aaaaa";
    std::string pattern = "aa";
    std::vector<int> expected{0, 1, 2, 3};

    CHECK(bruteForceSearchAll(text, pattern) == expected);
    CHECK(kmpSearchAll(text, pattern) == expected);
    CHECK(rabinKarpSearchAll(text, pattern) == expected);
    CHECK(boyerMooreBadCharacterSearchAll(text, pattern) == expected);

    auto pi = prefixFunction("ababaca");
    CHECK(pi == std::vector<int>({0, 0, 1, 2, 3, 0, 1}));

    auto z = zFunction("aaaaa");
    CHECK(z == std::vector<int>({0, 4, 3, 2, 1}));

    std::cout << "Semana11 busqueda de patrones: OK\n";
    return 0;
}
