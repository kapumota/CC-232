#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "StringStats.h"

namespace cc232::semana11 {

class TrieSet {
private:
    struct Node {
        bool terminal = false;
        std::map<char, std::unique_ptr<Node>> next;
    };

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
    std::size_t node_count_ = 1;

    static bool eraseRecursive(Node* node, const std::string& key, std::size_t depth, bool& removed) {
        if (depth == key.size()) {
            if (!node->terminal) {
                return false;
            }
            node->terminal = false;
            removed = true;
            return node->next.empty();
        }

        auto it = node->next.find(key[depth]);
        if (it == node->next.end()) {
            return false;
        }

        bool child_empty = eraseRecursive(it->second.get(), key, depth + 1, removed);
        if (child_empty) {
            node->next.erase(it);
        }
        return !node->terminal && node->next.empty();
    }

    static void collect(const Node* node, std::string& current, std::vector<std::string>& output,
                        std::size_t limit) {
        if (output.size() >= limit) {
            return;
        }
        if (node->terminal) {
            output.push_back(current);
            if (output.size() >= limit) {
                return;
            }
        }
        for (const auto& [ch, child] : node->next) {
            current.push_back(ch);
            collect(child.get(), current, output, limit);
            current.pop_back();
            if (output.size() >= limit) {
                return;
            }
        }
    }

    const Node* findNode(const std::string& prefix, StringStats* stats) const {
        const Node* node = root_.get();
        for (char ch : prefix) {
            if (stats != nullptr) {
                stats->transitions++;
                stats->comparisons++;
            }
            auto it = node->next.find(ch);
            if (it == node->next.end()) {
                return nullptr;
            }
            node = it->second.get();
        }
        return node;
    }

public:
    TrieSet() : root_(std::make_unique<Node>()) {}

    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t nodeCount() const { return node_count_; }

    bool insert(const std::string& key, StringStats* stats = nullptr) {
        Node* node = root_.get();
        for (char ch : key) {
            if (stats != nullptr) {
                stats->transitions++;
                stats->comparisons++;
            }
            auto& child = node->next[ch];
            if (!child) {
                child = std::make_unique<Node>();
                node_count_++;
                if (stats != nullptr) {
                    stats->nodes_created++;
                }
            }
            node = child.get();
        }
        if (node->terminal) {
            return false;
        }
        node->terminal = true;
        size_++;
        return true;
    }

    [[nodiscard]] bool contains(const std::string& key, StringStats* stats = nullptr) const {
        const Node* node = findNode(key, stats);
        return node != nullptr && node->terminal;
    }

    [[nodiscard]] bool startsWith(const std::string& prefix, StringStats* stats = nullptr) const {
        return findNode(prefix, stats) != nullptr;
    }

    bool erase(const std::string& key) {
        bool removed = false;
        eraseRecursive(root_.get(), key, 0, removed);
        if (removed) {
            size_--;
        }
        return removed;
    }

    [[nodiscard]] std::vector<std::string> autocomplete(const std::string& prefix,
                                                        std::size_t limit = 20) const {
        const Node* node = findNode(prefix, nullptr);
        if (node == nullptr) {
            return {};
        }
        std::vector<std::string> output;
        std::string current = prefix;
        collect(node, current, output, limit);
        return output;
    }

    [[nodiscard]] std::string longestPrefixOf(const std::string& query) const {
        const Node* node = root_.get();
        std::size_t best = node->terminal ? 0 : std::string::npos;
        for (std::size_t i = 0; i < query.size(); ++i) {
            auto it = node->next.find(query[i]);
            if (it == node->next.end()) {
                break;
            }
            node = it->second.get();
            if (node->terminal) {
                best = i + 1;
            }
        }
        if (best == std::string::npos) {
            return "";
        }
        return query.substr(0, best);
    }
};

}  // namespace cc232::semana11
