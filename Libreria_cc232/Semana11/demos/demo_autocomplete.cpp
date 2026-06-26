#include <iostream>
#include <string>

#include "CapituloCadenas.h"

int main() {
    using cc232::semana11::TrieMap;

    TrieMap<int> frequency;
    frequency.insert("casa", 15);
    frequency.insert("caso", 8);
    frequency.insert("casamiento", 3);
    frequency.insert("cadena", 10);
    frequency.insert("ciencia", 20);

    for (const auto& [word, count] : frequency.entriesWithPrefix("cas")) {
        std::cout << word << " -> " << count << '\n';
    }

    auto route = frequency.longestPrefixOf("casamientoCivil");
    if (route.has_value()) {
        std::cout << "prefijo encontrado: " << route->first << " con valor " << route->second << '\n';
    }
}
