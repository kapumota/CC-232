#include <algorithm>
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

    TrieSet words;
    CHECK(words.insert("casa"));
    CHECK(words.insert("caso"));
    CHECK(words.insert("casamiento"));
    CHECK(!words.insert("casa"));
    CHECK(words.contains("casa"));
    CHECK(!words.contains("cas"));
    CHECK(words.startsWith("cas"));
    CHECK(words.longestPrefixOf("casamientoCivil") == "casamiento");

    auto suggestions = words.autocomplete("cas");
    CHECK(suggestions.size() == 3);
    CHECK(std::is_sorted(suggestions.begin(), suggestions.end()));

    std::string text = "abracadabra";
    std::vector<int> expected{0, 7};
    CHECK(kmpSearchAll(text, "abra") == expected);
    CHECK(rabinKarpSearchAll(text, "abra") == expected);
    CHECK(boyerMooreBadCharacterSearchAll(text, "abra") == expected);

    SuffixArray sa("banana");
    CHECK(sa.contains("ana"));
    CHECK(sa.findAll("ana") == std::vector<int>({1, 3}));

    std::cout << "Semana11 pruebas publicas: OK\n";
    return 0;
}
