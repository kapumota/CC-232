#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

inline std::vector<int> rabinKarpSearchAll(const std::string& text, const std::string& pattern,
                                           StringStats* stats = nullptr) {
    std::vector<int> matches;
    const std::uint64_t base = 257;
    const std::uint64_t mod = 1'000'000'007ULL;

    if (pattern.empty()) {
        for (std::size_t i = 0; i <= text.size(); ++i) {
            matches.push_back(static_cast<int>(i));
        }
        return matches;
    }
    if (pattern.size() > text.size()) {
        return matches;
    }

    std::uint64_t power = 1;
    std::uint64_t pattern_hash = 0;
    std::uint64_t window_hash = 0;

    for (std::size_t i = 0; i < pattern.size(); ++i) {
        pattern_hash = (pattern_hash * base + static_cast<unsigned char>(pattern[i])) % mod;
        window_hash = (window_hash * base + static_cast<unsigned char>(text[i])) % mod;
        if (i + 1 < pattern.size()) {
            power = (power * base) % mod;
        }
    }

    for (std::size_t i = 0; i + pattern.size() <= text.size(); ++i) {
        if (stats != nullptr) {
            stats->hash_checks++;
        }
        if (window_hash == pattern_hash) {
            bool equal = true;
            for (std::size_t j = 0; j < pattern.size(); ++j) {
                if (stats != nullptr) {
                    stats->comparisons++;
                }
                if (text[i + j] != pattern[j]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                matches.push_back(static_cast<int>(i));
                if (stats != nullptr) {
                    stats->matches++;
                }
            }
        }
        if (i + pattern.size() < text.size()) {
            std::uint64_t left = (static_cast<unsigned char>(text[i]) * power) % mod;
            window_hash = (window_hash + mod - left) % mod;
            window_hash = (window_hash * base + static_cast<unsigned char>(text[i + pattern.size()])) % mod;
        }
    }
    return matches;
}

}  // namespace cc232::semana11
