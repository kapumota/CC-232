#pragma once

#include <string>
#include <vector>

#include "PrefixFunction.h"
#include "StringStats.h"

namespace cc232::semana11 {

inline std::vector<int> kmpSearchAll(const std::string& text, const std::string& pattern,
                                     StringStats* stats = nullptr) {
    std::vector<int> matches;
    if (pattern.empty()) {
        for (std::size_t i = 0; i <= text.size(); ++i) {
            matches.push_back(static_cast<int>(i));
        }
        return matches;
    }

    std::vector<int> pi = prefixFunction(pattern, stats);
    int j = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[static_cast<std::size_t>(j)]) {
            if (stats != nullptr) {
                stats->comparisons++;
                stats->fallback_steps++;
            }
            j = pi[static_cast<std::size_t>(j - 1)];
        }
        if (stats != nullptr) {
            stats->comparisons++;
        }
        if (text[i] == pattern[static_cast<std::size_t>(j)]) {
            ++j;
        }
        if (j == static_cast<int>(pattern.size())) {
            matches.push_back(static_cast<int>(i + 1 - pattern.size()));
            if (stats != nullptr) {
                stats->matches++;
            }
            j = pi[static_cast<std::size_t>(j - 1)];
        }
    }
    return matches;
}

}  // namespace cc232::semana11
