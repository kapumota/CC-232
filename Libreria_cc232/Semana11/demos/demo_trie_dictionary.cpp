#include <iostream>
#include <string>

#include "CapituloCadenas.h"

int main() {
    using cc232::semana11::TrieSet;

    TrieSet dictionary;
    dictionary.insert("algoritmo");
    dictionary.insert("algebra");
    dictionary.insert("arbol");
    dictionary.insert("grafo");
    dictionary.insert("gramatica");

    std::cout << "contiene algoritmo: " << dictionary.contains("algoritmo") << '\n';
    std::cout << "prefijo gra: " << dictionary.startsWith("gra") << '\n';
    std::cout << "prefijo mas largo de algoritmico: " << dictionary.longestPrefixOf("algoritmico") << '\n';

    for (const auto& word : dictionary.autocomplete("gra")) {
        std::cout << "sugerencia: " << word << '\n';
    }
}
