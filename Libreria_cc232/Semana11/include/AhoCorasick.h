#pragma once

#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

class AhoCorasick {
private:
    struct Node {
        std::map<char, int> next;
        int link = 0;
        std::vector<int> output;
    };

    std::vector<Node> trie_;
    std::vector<std::string> patterns_;
    bool built_ = false;

public:
    AhoCorasick() : trie_(1) {}

    int addPattern(const std::string& pattern) {
        int node = 0;
        for (char ch : pattern) {
            auto it = trie_[static_cast<std::size_t>(node)].next.find(ch);
            if (it == trie_[static_cast<std::size_t>(node)].next.end()) {
                trie_[static_cast<std::size_t>(node)].next[ch] = static_cast<int>(trie_.size());
                trie_.push_back(Node{});
            }
            node = trie_[static_cast<std::size_t>(node)].next[ch];
        }
        int id = static_cast<int>(patterns_.size());
        patterns_.push_back(pattern);
        trie_[static_cast<std::size_t>(node)].output.push_back(id);
        built_ = false;
        return id;
    }

    void build(StringStats* stats = nullptr) {
        std::queue<int> q;
        for (const auto& [ch, child] : trie_[0].next) {
            (void)ch;
            trie_[static_cast<std::size_t>(child)].link = 0;
            q.push(child);
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& [ch, u] : trie_[static_cast<std::size_t>(v)].next) {
                int fallback = trie_[static_cast<std::size_t>(v)].link;
                while (fallback != 0 && trie_[static_cast<std::size_t>(fallback)].next.count(ch) == 0) {
                    fallback = trie_[static_cast<std::size_t>(fallback)].link;
                    if (stats != nullptr) {
                        stats->fallback_steps++;
                    }
                }
                auto it = trie_[static_cast<std::size_t>(fallback)].next.find(ch);
                if (it != trie_[static_cast<std::size_t>(fallback)].next.end() && it->second != u) {
                    trie_[static_cast<std::size_t>(u)].link = it->second;
                } else {
                    trie_[static_cast<std::size_t>(u)].link = 0;
                }
                const auto& inherited = trie_[static_cast<std::size_t>(trie_[static_cast<std::size_t>(u)].link)].output;
                trie_[static_cast<std::size_t>(u)].output.insert(
                    trie_[static_cast<std::size_t>(u)].output.end(), inherited.begin(), inherited.end());
                q.push(u);
            }
        }
        built_ = true;
    }

    [[nodiscard]] std::vector<std::pair<int, int>> search(const std::string& text,
                                                          StringStats* stats = nullptr) {
        if (!built_) {
            build(stats);
        }
        std::vector<std::pair<int, int>> matches;
        int node = 0;
        for (std::size_t i = 0; i < text.size(); ++i) {
            char ch = text[i];
            while (node != 0 && trie_[static_cast<std::size_t>(node)].next.count(ch) == 0) {
                node = trie_[static_cast<std::size_t>(node)].link;
                if (stats != nullptr) {
                    stats->fallback_steps++;
                }
            }
            auto it = trie_[static_cast<std::size_t>(node)].next.find(ch);
            if (it != trie_[static_cast<std::size_t>(node)].next.end()) {
                node = it->second;
            }
            if (stats != nullptr) {
                stats->transitions++;
            }
            for (int id : trie_[static_cast<std::size_t>(node)].output) {
                int start = static_cast<int>(i + 1 - patterns_[static_cast<std::size_t>(id)].size());
                matches.emplace_back(start, id);
                if (stats != nullptr) {
                    stats->matches++;
                }
            }
        }
        return matches;
    }

    [[nodiscard]] const std::string& pattern(int id) const { return patterns_[static_cast<std::size_t>(id)]; }
    [[nodiscard]] std::size_t nodeCount() const { return trie_.size(); }
    [[nodiscard]] std::size_t patternCount() const { return patterns_.size(); }
};

}  // namespace cc232::semana11
