#pragma once

#include <cstddef>

namespace cc232::semana11 {

struct StringStats {
    std::size_t comparisons = 0;
    std::size_t transitions = 0;
    std::size_t fallback_steps = 0;
    std::size_t hash_checks = 0;
    std::size_t matches = 0;
    std::size_t nodes_created = 0;

    void reset() {
        comparisons = 0;
        transitions = 0;
        fallback_steps = 0;
        hash_checks = 0;
        matches = 0;
        nodes_created = 0;
    }
};

}  // namespace cc232::semana11
