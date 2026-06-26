#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
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
    using cc232::semana11::AhoCorasick;

    AhoCorasick ac;
    int he = ac.addPattern("he");
    int she = ac.addPattern("she");
    int his = ac.addPattern("his");
    int hers = ac.addPattern("hers");
    (void)he;
    (void)she;
    (void)his;
    (void)hers;
    ac.build();

    auto matches = ac.search("ushers");
    std::vector<std::pair<int, std::string>> readable;
    for (auto [position, id] : matches) {
        readable.emplace_back(position, ac.pattern(id));
    }

    CHECK(std::find(readable.begin(), readable.end(), std::make_pair(1, std::string("she"))) != readable.end());
    CHECK(std::find(readable.begin(), readable.end(), std::make_pair(2, std::string("he"))) != readable.end());
    CHECK(std::find(readable.begin(), readable.end(), std::make_pair(2, std::string("hers"))) != readable.end());
    CHECK(ac.nodeCount() > ac.patternCount());

    std::cout << "Semana11 Aho-Corasick: OK\n";
    return 0;
}
