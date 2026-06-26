#include <iostream>
#include <optional>
#include <string>

#include "CapituloCadenas.h"

#define CHECK(condition)                                                                  \
    do {                                                                                  \
        if (!(condition)) {                                                               \
            std::cerr << "Fallo en linea " << __LINE__ << ": " << #condition << '\n';    \
            return 1;                                                                     \
        }                                                                                 \
    } while (false)

int main() {
    using cc232::semana11::TrieMap;

    TrieMap<int> map;
    CHECK(map.insert("uno", 1));
    CHECK(map.insert("unidad", 10));
    CHECK(!map.insert("uno", 100));
    CHECK(map.size() == 2);
    CHECK(map.get("uno").value() == 100);
    CHECK(map.contains("unidad"));
    CHECK(!map.contains("un"));

    auto entries = map.entriesWithPrefix("un");
    CHECK(entries.size() == 2);

    auto best = map.longestPrefixOf("unidadAcademica");
    CHECK(best.has_value());
    CHECK(best->first == "unidad");
    CHECK(best->second == 10);

    CHECK(map.erase("uno"));
    CHECK(!map.contains("uno"));
    CHECK(map.contains("unidad"));

    std::cout << "Semana11 TrieMap: OK\n";
    return 0;
}
