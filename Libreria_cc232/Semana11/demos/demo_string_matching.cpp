#include <iostream>
#include <string>
#include <vector>

#include "CapituloCadenas.h"

static void printPositions(const std::string& name, const std::vector<int>& positions) {
    std::cout << name << ':';
    for (int position : positions) {
        std::cout << ' ' << position;
    }
    std::cout << '\n';
}

int main() {
    using namespace cc232::semana11;

    std::string text = "abracadabra abracadabra";
    std::string pattern = "abra";

    printPositions("fuerza bruta", bruteForceSearchAll(text, pattern));
    printPositions("kmp", kmpSearchAll(text, pattern));
    printPositions("rabin karp", rabinKarpSearchAll(text, pattern));
    printPositions("boyer moore", boyerMooreBadCharacterSearchAll(text, pattern));

    AhoCorasick ac;
    ac.addPattern("abra");
    ac.addPattern("cad");
    ac.addPattern("ra");
    ac.build();

    for (const auto& [position, id] : ac.search(text)) {
        std::cout << "aho-corasick: " << ac.pattern(id) << " en " << position << '\n';
    }
}
