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

    SuffixArray sa("banana");
    CHECK(sa.array() == std::vector<int>({5, 3, 1, 0, 4, 2}));
    CHECK(sa.findAll("na") == std::vector<int>({2, 4}));
    CHECK(!sa.contains("nana$"));

    SuffixTrie st("banana");
    CHECK(st.containsSubstring("ban"));
    CHECK(st.containsSubstring("ana"));
    CHECK(st.containsSuffix("ana"));
    CHECK(!st.containsSuffix("ban"));
    CHECK(st.nodeCount() > 1);

    std::cout << "Semana11 estructuras de sufijos: OK\n";
    return 0;
}
