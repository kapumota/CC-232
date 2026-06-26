#pragma once

#include <map>
#include <memory>
#include <string>

namespace cc232::semana11 {

class SuffixTrie {
private:
    struct Node {
        std::map<char, std::unique_ptr<Node>> next;
        bool terminal = false;
    };

    std::unique_ptr<Node> root_;
    std::string text_;
    std::size_t node_count_ = 1;

public:
    SuffixTrie() : root_(std::make_unique<Node>()) {}
    explicit SuffixTrie(const std::string& text) : SuffixTrie() { build(text); }

    void build(const std::string& text) {
        root_ = std::make_unique<Node>();
        text_ = text;
        node_count_ = 1;
        std::string with_terminal = text + "$";
        for (std::size_t start = 0; start < with_terminal.size(); ++start) {
            Node* node = root_.get();
            for (std::size_t i = start; i < with_terminal.size(); ++i) {
                char ch = with_terminal[i];
                auto& child = node->next[ch];
                if (!child) {
                    child = std::make_unique<Node>();
                    node_count_++;
                }
                node = child.get();
            }
            node->terminal = true;
        }
    }

    [[nodiscard]] bool containsSubstring(const std::string& pattern) const {
        const Node* node = root_.get();
        for (char ch : pattern) {
            auto it = node->next.find(ch);
            if (it == node->next.end()) {
                return false;
            }
            node = it->second.get();
        }
        return true;
    }

    [[nodiscard]] bool containsSuffix(const std::string& suffix) const {
        const Node* node = root_.get();
        std::string query = suffix + "$";
        for (char ch : query) {
            auto it = node->next.find(ch);
            if (it == node->next.end()) {
                return false;
            }
            node = it->second.get();
        }
        return node->terminal;
    }

    [[nodiscard]] std::size_t nodeCount() const { return node_count_; }
    [[nodiscard]] const std::string& text() const { return text_; }
};

}  // namespace cc232::semana11
