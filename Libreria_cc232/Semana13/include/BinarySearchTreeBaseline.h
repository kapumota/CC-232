#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

namespace cc232::week13 {

template <typename Key>
class BinarySearchTreeBaseline {
private:
    struct Node {
        explicit Node(const Key& value) : key(value) {}
        Key key;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

public:
    bool insert(const Key& key) {
        return insert(root_, key);
    }

    [[nodiscard]] bool contains(const Key& key) const {
        return contains(root_.get(), key);
    }

    [[nodiscard]] std::size_t size() const {
        return size_;
    }

    [[nodiscard]] std::size_t height() const {
        return height(root_.get());
    }

    [[nodiscard]] std::size_t searchPathLength(const Key& key) const {
        const Node* current = root_.get();
        std::size_t length = 0;
        while (current != nullptr) {
            ++length;
            if (key == current->key) {
                return length;
            }
            current = key < current->key ? current->left.get() : current->right.get();
        }
        return length;
    }

    [[nodiscard]] std::vector<Key> inorder() const {
        std::vector<Key> result;
        inorder(root_.get(), result);
        return result;
    }

private:
    bool insert(std::unique_ptr<Node>& node, const Key& key) {
        if (!node) {
            node = std::make_unique<Node>(key);
            ++size_;
            return true;
        }
        if (key == node->key) {
            return false;
        }
        if (key < node->key) {
            return insert(node->left, key);
        }
        return insert(node->right, key);
    }

    static bool contains(const Node* node, const Key& key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        return key < node->key ? contains(node->left.get(), key) : contains(node->right.get(), key);
    }

    static std::size_t height(const Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left.get()), height(node->right.get()));
    }

    static void inorder(const Node* node, std::vector<Key>& output) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), output);
        output.push_back(node->key);
        inorder(node->right.get(), output);
    }

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

}  // namespace cc232::week13
