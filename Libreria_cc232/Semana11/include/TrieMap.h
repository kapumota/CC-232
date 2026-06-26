#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace cc232::semana11 {

template <typename Value>
class TrieMap {
private:
    struct Node {
        std::optional<Value> value;
        std::map<char, std::unique_ptr<Node>> next;
    };

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;

    static void collect(const Node* node, std::string& current,
                        std::vector<std::pair<std::string, Value>>& output,
                        std::size_t limit) {
        if (output.size() >= limit) {
            return;
        }
        if (node->value.has_value()) {
            output.emplace_back(current, *node->value);
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

    Node* findNode(const std::string& key) {
        Node* node = root_.get();
        for (char ch : key) {
            auto it = node->next.find(ch);
            if (it == node->next.end()) {
                return nullptr;
            }
            node = it->second.get();
        }
        return node;
    }

    const Node* findNode(const std::string& key) const {
        const Node* node = root_.get();
        for (char ch : key) {
            auto it = node->next.find(ch);
            if (it == node->next.end()) {
                return nullptr;
            }
            node = it->second.get();
        }
        return node;
    }

    static bool eraseRecursive(Node* node, const std::string& key, std::size_t depth, bool& removed) {
        if (depth == key.size()) {
            if (!node->value.has_value()) {
                return false;
            }
            node->value.reset();
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
        return !node->value.has_value() && node->next.empty();
    }

public:
    TrieMap() : root_(std::make_unique<Node>()) {}

    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    bool insert(const std::string& key, Value value) {
        Node* node = root_.get();
        for (char ch : key) {
            auto& child = node->next[ch];
            if (!child) {
                child = std::make_unique<Node>();
            }
            node = child.get();
        }
        bool was_new = !node->value.has_value();
        node->value = std::move(value);
        if (was_new) {
            size_++;
        }
        return was_new;
    }

    [[nodiscard]] bool contains(const std::string& key) const {
        const Node* node = findNode(key);
        return node != nullptr && node->value.has_value();
    }

    [[nodiscard]] std::optional<Value> get(const std::string& key) const {
        const Node* node = findNode(key);
        if (node == nullptr || !node->value.has_value()) {
            return std::nullopt;
        }
        return *node->value;
    }

    bool erase(const std::string& key) {
        bool removed = false;
        eraseRecursive(root_.get(), key, 0, removed);
        if (removed) {
            size_--;
        }
        return removed;
    }

    [[nodiscard]] std::vector<std::pair<std::string, Value>> entriesWithPrefix(
        const std::string& prefix, std::size_t limit = 20) const {
        const Node* node = findNode(prefix);
        if (node == nullptr) {
            return {};
        }
        std::vector<std::pair<std::string, Value>> output;
        std::string current = prefix;
        collect(node, current, output, limit);
        return output;
    }

    [[nodiscard]] std::optional<std::pair<std::string, Value>> longestPrefixOf(
        const std::string& query) const {
        const Node* node = root_.get();
        std::optional<std::pair<std::string, Value>> best;
        if (node->value.has_value()) {
            best = std::make_pair(std::string{}, *node->value);
        }
        for (std::size_t i = 0; i < query.size(); ++i) {
            auto it = node->next.find(query[i]);
            if (it == node->next.end()) {
                break;
            }
            node = it->second.get();
            if (node->value.has_value()) {
                best = std::make_pair(query.substr(0, i + 1), *node->value);
            }
        }
        return best;
    }
};

}  // namespace cc232::semana11
