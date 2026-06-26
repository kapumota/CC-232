#pragma once

#include <array>
#include <string>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

inline std::vector<int> boyerMooreBadCharacterSearchAll(const std::string& text,
                                                        const std::string& pattern,
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

    std::array<int, 256> last{};
    last.fill(-1);
    for (std::size_t i = 0; i < pattern.size(); ++i) {
        last[static_cast<unsigned char>(pattern[i])] = static_cast<int>(i);
    }

    std::size_t shift = 0;
    while (shift + pattern.size() <= text.size()) {
        int j = static_cast<int>(pattern.size()) - 1;
        while (j >= 0) {
            if (stats != nullptr) {
                stats->comparisons++;
            }
            if (pattern[static_cast<std::size_t>(j)] != text[shift + static_cast<std::size_t>(j)]) {
                break;
            }
            --j;
        }
        if (j < 0) {
            matches.push_back(static_cast<int>(shift));
            if (stats != nullptr) {
                stats->matches++;
            }
            shift += 1;
        } else {
            int bad = last[static_cast<unsigned char>(text[shift + static_cast<std::size_t>(j)])];
            int jump = std::max(1, j - bad);
            shift += static_cast<std::size_t>(jump);
        }
    }
    return matches;
}

}  // namespace cc232::semana11
