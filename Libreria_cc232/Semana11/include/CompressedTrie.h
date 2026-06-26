#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cc232::semana11 {

class CompressedTrie {
private:
    struct Edge;
    struct Node {
        bool terminal = false;
        std::vector<Edge> edges;
    };
    struct Edge {
        std::string label;
        std::unique_ptr<Node> child;
    };

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
    std::size_t node_count_ = 1;

    static std::size_t commonPrefixLength(const std::string& a, std::size_t a_pos,
                                          const std::string& b) {
        std::size_t i = 0;
        while (a_pos + i < a.size() && i < b.size() && a[a_pos + i] == b[i]) {
            ++i;
        }
        return i;
    }

    static const Edge* findEdge(const Node* node, char ch) {
        for (const auto& edge : node->edges) {
            if (!edge.label.empty() && edge.label.front() == ch) {
                return &edge;
            }
        }
        return nullptr;
    }

public:
    CompressedTrie() : root_(std::make_unique<Node>()) {}

    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t nodeCount() const { return node_count_; }

    bool insert(const std::string& key) {
        Node* node = root_.get();
        std::size_t pos = 0;

        while (pos < key.size()) {
            Edge* chosen = nullptr;
            for (auto& edge : node->edges) {
                if (!edge.label.empty() && edge.label.front() == key[pos]) {
                    chosen = &edge;
                    break;
                }
            }

            if (chosen == nullptr) {
                auto child = std::make_unique<Node>();
                child->terminal = true;
                node->edges.push_back(Edge{key.substr(pos), std::move(child)});
                size_++;
                node_count_++;
                return true;
            }

            std::size_t common = commonPrefixLength(key, pos, chosen->label);
            if (common == chosen->label.size()) {
                node = chosen->child.get();
                pos += common;
                continue;
            }

            auto split_node = std::make_unique<Node>();
            node_count_++;
            std::string old_suffix = chosen->label.substr(common);
            std::string new_suffix = key.substr(pos + common);

            split_node->edges.push_back(Edge{old_suffix, std::move(chosen->child)});
            chosen->label = chosen->label.substr(0, common);
            chosen->child = std::move(split_node);

            if (new_suffix.empty()) {
                if (chosen->child->terminal) {
                    return false;
                }
                chosen->child->terminal = true;
            } else {
                auto new_child = std::make_unique<Node>();
                new_child->terminal = true;
                chosen->child->edges.push_back(Edge{new_suffix, std::move(new_child)});
                node_count_++;
            }
            size_++;
            return true;
        }

        if (node->terminal) {
            return false;
        }
        node->terminal = true;
        size_++;
        return true;
    }

    [[nodiscard]] bool contains(const std::string& key) const {
        const Node* node = root_.get();
        std::size_t pos = 0;
        while (pos < key.size()) {
            const Edge* edge = findEdge(node, key[pos]);
            if (edge == nullptr) {
                return false;
            }
            std::size_t common = commonPrefixLength(key, pos, edge->label);
            if (common != edge->label.size()) {
                return false;
            }
            pos += common;
            node = edge->child.get();
        }
        return node->terminal;
    }

    [[nodiscard]] bool startsWith(const std::string& prefix) const {
        const Node* node = root_.get();
        std::size_t pos = 0;
        while (pos < prefix.size()) {
            const Edge* edge = findEdge(node, prefix[pos]);
            if (edge == nullptr) {
                return false;
            }
            std::size_t common = commonPrefixLength(prefix, pos, edge->label);
            if (pos + common == prefix.size()) {
                return true;
            }
            if (common != edge->label.size()) {
                return false;
            }
            pos += common;
            node = edge->child.get();
        }
        return true;
    }
};

}  // namespace cc232::semana11
