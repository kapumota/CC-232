#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace cc232::semana11 {

class SuffixArray {
private:
    std::string text_;
    std::vector<int> sa_;
    std::vector<int> lcp_;

    static int compareSuffixWithPattern(const std::string& text, int suffix_start,
                                        const std::string& pattern) {
        std::size_t i = 0;
        while (suffix_start + static_cast<int>(i) < static_cast<int>(text.size()) && i < pattern.size()) {
            char a = text[static_cast<std::size_t>(suffix_start) + i];
            char b = pattern[i];
            if (a < b) {
                return -1;
            }
            if (a > b) {
                return 1;
            }
            ++i;
        }
        if (i == pattern.size()) {
            return 0;
        }
        return -1;
    }

public:
    SuffixArray() = default;
    explicit SuffixArray(std::string text) { build(std::move(text)); }

    void build(std::string text) {
        text_ = std::move(text);
        int n = static_cast<int>(text_.size());
        sa_.resize(static_cast<std::size_t>(n));
        for (int i = 0; i < n; ++i) {
            sa_[static_cast<std::size_t>(i)] = i;
        }
        std::sort(sa_.begin(), sa_.end(), [&](int a, int b) {
            return text_.substr(static_cast<std::size_t>(a)) < text_.substr(static_cast<std::size_t>(b));
        });
        buildLcp();
    }

    void buildLcp() {
        lcp_.assign(sa_.size(), 0);
        if (sa_.empty()) {
            return;
        }
        std::vector<int> rank(sa_.size(), 0);
        for (std::size_t i = 0; i < sa_.size(); ++i) {
            rank[static_cast<std::size_t>(sa_[i])] = static_cast<int>(i);
        }
        int h = 0;
        for (std::size_t i = 0; i < text_.size(); ++i) {
            int r = rank[i];
            if (r == 0) {
                continue;
            }
            int j = sa_[static_cast<std::size_t>(r - 1)];
            while (i + static_cast<std::size_t>(h) < text_.size() &&
                   static_cast<std::size_t>(j + h) < text_.size() &&
                   text_[i + static_cast<std::size_t>(h)] == text_[static_cast<std::size_t>(j + h)]) {
                ++h;
            }
            lcp_[static_cast<std::size_t>(r)] = h;
            if (h > 0) {
                --h;
            }
        }
    }

    [[nodiscard]] const std::vector<int>& array() const { return sa_; }
    [[nodiscard]] const std::vector<int>& lcp() const { return lcp_; }
    [[nodiscard]] const std::string& text() const { return text_; }

    [[nodiscard]] bool contains(const std::string& pattern) const {
        return !findAll(pattern).empty();
    }

    [[nodiscard]] std::vector<int> findAll(const std::string& pattern) const {
        std::vector<int> positions;
        if (pattern.empty()) {
            for (std::size_t i = 0; i <= text_.size(); ++i) {
                positions.push_back(static_cast<int>(i));
            }
            return positions;
        }
        int left = 0;
        int right = static_cast<int>(sa_.size());
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cmp = compareSuffixWithPattern(text_, sa_[static_cast<std::size_t>(mid)], pattern);
            if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        for (int i = left; i < static_cast<int>(sa_.size()); ++i) {
            if (compareSuffixWithPattern(text_, sa_[static_cast<std::size_t>(i)], pattern) != 0) {
                break;
            }
            positions.push_back(sa_[static_cast<std::size_t>(i)]);
        }
        std::sort(positions.begin(), positions.end());
        return positions;
    }
};

}  // namespace cc232::semana11
