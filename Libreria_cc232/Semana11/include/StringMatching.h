#pragma once

#include <string>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

inline std::vector<int> bruteForceSearchAll(const std::string& text, const std::string& pattern,
                                            StringStats* stats = nullptr) {
    std::vector<int> matches;
    if (pattern.empty()) {
        for (std::size_t i = 0; i <= text.size(); ++i) {
            matches.push_back(static_cast<int>(i));
        }
        return matches;
    }
    if (pattern.size() > text.size()) {
        return matches;
    }

    for (std::size_t i = 0; i + pattern.size() <= text.size(); ++i) {
        std::size_t j = 0;
        while (j < pattern.size()) {
            if (stats != nullptr) {
                stats->comparisons++;
            }
            if (text[i + j] != pattern[j]) {
                break;
            }
            ++j;
        }
        if (j == pattern.size()) {
            matches.push_back(static_cast<int>(i));
            if (stats != nullptr) {
                stats->matches++;
            }
        }
    }
    return matches;
}

inline std::vector<int> zFunction(const std::string& s, StringStats* stats = nullptr) {
    std::vector<int> z(s.size(), 0);
    int left = 0;
    int right = 0;
    for (int i = 1; i < static_cast<int>(s.size()); ++i) {
        if (i <= right) {
            z[static_cast<std::size_t>(i)] = std::min(right - i + 1, z[static_cast<std::size_t>(i - left)]);
        }
        while (i + z[static_cast<std::size_t>(i)] < static_cast<int>(s.size())) {
            if (stats != nullptr) {
                stats->comparisons++;
            }
            if (s[static_cast<std::size_t>(z[static_cast<std::size_t>(i)])] !=
                s[static_cast<std::size_t>(i + z[static_cast<std::size_t>(i)])]) {
                break;
            }
            ++z[static_cast<std::size_t>(i)];
        }
        if (i + z[static_cast<std::size_t>(i)] - 1 > right) {
            left = i;
            right = i + z[static_cast<std::size_t>(i)] - 1;
        }
    }
    return z;
}

}  // namespace cc232::semana11
