#include <iostream>
#include <string>

#include "CapituloCadenas.h"

int main() {
    using namespace cc232::semana11;

    std::string text = "banana";
    SuffixArray suffix_array(text);
    SuffixTrie suffix_trie(text);

    std::cout << "suffix array:";
    for (int index : suffix_array.array()) {
        std::cout << ' ' << index;
    }
    std::cout << '\n';

    std::cout << "ana esta en suffix array: " << suffix_array.contains("ana") << '\n';
    std::cout << "ana esta en suffix trie: " << suffix_trie.containsSubstring("ana") << '\n';
    std::cout << "nodos en suffix trie: " << suffix_trie.nodeCount() << '\n';
}
