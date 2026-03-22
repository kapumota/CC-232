#ifndef CC232_MINI_TEST_H
#define CC232_MINI_TEST_H

#include <cstdlib>
#include <iostream>
#include <string>

namespace cc232::test {

inline void expect(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "TESTS FALLARON: " << message << '\n';
        std::exit(1);
    }
}

inline void pass() {
    std::cout << "Todos los test pasaron.\n";
}

}  // namespace cc232::test

#endif
