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

    TrieSet trie;
    CHECK(trie.empty());
    CHECK(trie.insert(""));
    CHECK(trie.contains(""));
    CHECK(trie.insert("a"));
    CHECK(trie.insert("ab"));
    CHECK(trie.insert("abc"));
    CHECK(trie.size() == 4);
    CHECK(trie.longestPrefixOf("abcd") == "abc");
    CHECK(trie.erase("ab"));
    CHECK(!trie.contains("ab"));
    CHECK(trie.contains("abc"));
    CHECK(trie.contains("a"));
    CHECK(!trie.erase("ab"));
    CHECK(trie.size() == 3);

    CompressedTrie compressed;
    CHECK(compressed.insert("romano"));
    CHECK(compressed.insert("roma"));
    CHECK(compressed.insert("robot"));
    CHECK(compressed.contains("romano"));
    CHECK(compressed.contains("roma"));
    CHECK(compressed.startsWith("ro"));
    CHECK(!compressed.contains("rom"));

    std::cout << "Semana11 invariantes de tries: OK\n";
    return 0;
}
