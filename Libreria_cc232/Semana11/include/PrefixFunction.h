#pragma once

#include <string>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

inline std::vector<int> prefixFunction(const std::string& pattern, StringStats* stats = nullptr) {
    std::vector<int> pi(pattern.size(), 0);
    for (std::size_t i = 1; i < pattern.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[static_cast<std::size_t>(j)]) {
            if (stats != nullptr) {
                stats->comparisons++;
                stats->fallback_steps++;
            }
            j = pi[static_cast<std::size_t>(j - 1)];
        }
        if (stats != nullptr) {
            stats->comparisons++;
        }
        if (pattern[i] == pattern[static_cast<std::size_t>(j)]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

}  // namespace cc232::semana11
