#pragma once

#include "IoStats.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace cc232::week13 {

template <typename Key>
struct BTreeNode {
    explicit BTreeNode(bool is_leaf) : leaf(is_leaf) {}

    bool leaf = true;
    std::vector<Key> keys;
    std::vector<std::unique_ptr<BTreeNode<Key>>> children;
};

template <typename Key>
class BTree {
public:
    explicit BTree(std::size_t minimum_degree) : minimum_degree_(minimum_degree) {
        if (minimum_degree_ < 2) {
            throw std::invalid_argument("El grado minimo debe ser al menos dos");
        }
        root_ = std::make_unique<Node>(true);
    }

    [[nodiscard]] std::size_t minimumDegree() const { return minimum_degree_; }
    [[nodiscard]] std::size_t maxKeysPerNode() const { return 2 * minimum_degree_ - 1; }
    [[nodiscard]] std::size_t minKeysPerNonRootNode() const { return minimum_degree_ - 1; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    [[nodiscard]] bool contains(const Key& key) const {
        return search(root_.get(), key).has_value();
    }

    bool insert(const Key& key) {
        if (contains(key)) {
            return false;
        }
        if (root_->keys.size() == maxKeysPerNode()) {
            auto new_root = std::make_unique<Node>(false);
            new_root->children.push_back(std::move(root_));
            root_ = std::move(new_root);
            splitChild(root_.get(), 0);
        }
        insertNonFull(root_.get(), key);
        ++size_;
        return true;
    }

    bool remove(const Key& key) {
        if (empty()) {
            return false;
        }
        const bool removed = remove(root_.get(), key);
        if (!removed) {
            return false;
        }
        --size_;
        if (!root_->leaf && root_->keys.empty()) {
            root_ = std::move(root_->children.front());
        }
        if (size_ == 0) {
            root_ = std::make_unique<Node>(true);
        }
        return true;
    }

    [[nodiscard]] std::vector<Key> inorder() const {
        std::vector<Key> result;
        result.reserve(size_);
        inorder(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::size_t height() const {
        if (empty()) {
            return 0;
        }
        return height(root_.get());
    }

    [[nodiscard]] std::size_t searchBlockReads(const Key& key) const {
        const Node* current = root_.get();
        std::size_t reads = 0;
        while (current != nullptr) {
            ++reads;
            const auto it = std::lower_bound(current->keys.begin(), current->keys.end(), key);
            const std::size_t index = static_cast<std::size_t>(it - current->keys.begin());
            if (it != current->keys.end() && *it == key) {
                return reads;
            }
            if (current->leaf) {
                return reads;
            }
            current = current->children[index].get();
        }
        return reads;
    }

    [[nodiscard]] bool validate() const {
        if (!root_) {
            return size_ == 0;
        }
        std::size_t counted = 0;
        std::optional<std::size_t> leaf_depth;
        std::optional<Key> lower;
        std::optional<Key> upper;
        return validateNode(root_.get(), true, 0, lower, upper, leaf_depth, counted) && counted == size_;
    }

private:
    using Node = BTreeNode<Key>;

    static std::optional<std::pair<const Node*, std::size_t>> search(const Node* node, const Key& key) {
        if (node == nullptr) {
            return std::nullopt;
        }
        const auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
        const std::size_t index = static_cast<std::size_t>(it - node->keys.begin());
        if (it != node->keys.end() && *it == key) {
            return std::make_pair(node, index);
        }
        if (node->leaf) {
            return std::nullopt;
        }
        return search(node->children[index].get(), key);
    }

    void splitChild(Node* parent, std::size_t child_index) {
        auto& child_ptr = parent->children[child_index];
        auto right = std::make_unique<Node>(child_ptr->leaf);
        Node* child = child_ptr.get();
        const std::size_t t = minimum_degree_;
        const Key median = child->keys[t - 1];

        right->keys.assign(child->keys.begin() + static_cast<std::ptrdiff_t>(t), child->keys.end());
        child->keys.resize(t - 1);

        if (!child->leaf) {
            for (std::size_t i = t; i < child->children.size(); ++i) {
                right->children.push_back(std::move(child->children[i]));
            }
            child->children.resize(t);
        }

        parent->keys.insert(parent->keys.begin() + static_cast<std::ptrdiff_t>(child_index), median);
        parent->children.insert(parent->children.begin() + static_cast<std::ptrdiff_t>(child_index + 1), std::move(right));
    }

    void insertNonFull(Node* node, const Key& key) {
        if (node->leaf) {
            node->keys.insert(std::upper_bound(node->keys.begin(), node->keys.end(), key), key);
            return;
        }
        std::size_t index = static_cast<std::size_t>(std::upper_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin());
        if (node->children[index]->keys.size() == maxKeysPerNode()) {
            splitChild(node, index);
            if (node->keys[index] < key) {
                ++index;
            }
        }
        insertNonFull(node->children[index].get(), key);
    }

    bool remove(Node* node, const Key& key) {
        std::size_t index = firstGreaterOrEqual(node, key);
        if (index < node->keys.size() && node->keys[index] == key) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + static_cast<std::ptrdiff_t>(index));
                return true;
            }
            return removeFromInternal(node, index);
        }

        if (node->leaf) {
            return false;
        }

        const bool was_last_child = index == node->keys.size();
        if (node->children[index]->keys.size() < minimum_degree_) {
            fillChild(node, index);
        }

        if (was_last_child && index > node->keys.size()) {
            return remove(node->children[index - 1].get(), key);
        }
        return remove(node->children[index].get(), key);
    }

    bool removeFromInternal(Node* node, std::size_t index) {
        const Key key = node->keys[index];
        if (node->children[index]->keys.size() >= minimum_degree_) {
            const Key predecessor = getPredecessor(node, index);
            node->keys[index] = predecessor;
            return remove(node->children[index].get(), predecessor);
        }
        if (node->children[index + 1]->keys.size() >= minimum_degree_) {
            const Key successor = getSuccessor(node, index);
            node->keys[index] = successor;
            return remove(node->children[index + 1].get(), successor);
        }
        mergeChildren(node, index);
        return remove(node->children[index].get(), key);
    }

    Key getPredecessor(Node* node, std::size_t index) const {
        Node* current = node->children[index].get();
        while (!current->leaf) {
            current = current->children.back().get();
        }
        return current->keys.back();
    }

    Key getSuccessor(Node* node, std::size_t index) const {
        Node* current = node->children[index + 1].get();
        while (!current->leaf) {
            current = current->children.front().get();
        }
        return current->keys.front();
    }

    void fillChild(Node* node, std::size_t index) {
        if (index != 0 && node->children[index - 1]->keys.size() >= minimum_degree_) {
            borrowFromPrevious(node, index);
        } else if (index != node->keys.size() && node->children[index + 1]->keys.size() >= minimum_degree_) {
            borrowFromNext(node, index);
        } else {
            if (index != node->keys.size()) {
                mergeChildren(node, index);
            } else {
                mergeChildren(node, index - 1);
            }
        }
    }

    void borrowFromPrevious(Node* node, std::size_t index) {
        Node* child = node->children[index].get();
        Node* sibling = node->children[index - 1].get();

        child->keys.insert(child->keys.begin(), node->keys[index - 1]);
        if (!child->leaf) {
            child->children.insert(child->children.begin(), std::move(sibling->children.back()));
            sibling->children.pop_back();
        }
        node->keys[index - 1] = sibling->keys.back();
        sibling->keys.pop_back();
    }

    void borrowFromNext(Node* node, std::size_t index) {
        Node* child = node->children[index].get();
        Node* sibling = node->children[index + 1].get();

        child->keys.push_back(node->keys[index]);
        if (!child->leaf) {
            child->children.push_back(std::move(sibling->children.front()));
            sibling->children.erase(sibling->children.begin());
        }
        node->keys[index] = sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());
    }

    void mergeChildren(Node* node, std::size_t index) {
        Node* child = node->children[index].get();
        auto sibling = std::move(node->children[index + 1]);

        child->keys.push_back(node->keys[index]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

        if (!child->leaf) {
            for (auto& grandchild : sibling->children) {
                child->children.push_back(std::move(grandchild));
            }
        }

        node->keys.erase(node->keys.begin() + static_cast<std::ptrdiff_t>(index));
        node->children.erase(node->children.begin() + static_cast<std::ptrdiff_t>(index + 1));
    }

    static std::size_t firstGreaterOrEqual(const Node* node, const Key& key) {
        return static_cast<std::size_t>(std::lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin());
    }

    static void inorder(const Node* node, std::vector<Key>& output) {
        if (node == nullptr) {
            return;
        }
        for (std::size_t i = 0; i < node->keys.size(); ++i) {
            if (!node->leaf) {
                inorder(node->children[i].get(), output);
            }
            output.push_back(node->keys[i]);
        }
        if (!node->leaf) {
            inorder(node->children.back().get(), output);
        }
    }

    static std::size_t height(const Node* node) {
        if (node->leaf) {
            return 1;
        }
        return 1 + height(node->children.front().get());
    }

    bool validateNode(const Node* node,
                      bool is_root,
                      std::size_t depth,
                      const std::optional<Key>& lower,
                      const std::optional<Key>& upper,
                      std::optional<std::size_t>& leaf_depth,
                      std::size_t& counted) const {
        if (node == nullptr) {
            return false;
        }
        if (!std::is_sorted(node->keys.begin(), node->keys.end())) {
            return false;
        }
        for (std::size_t i = 1; i < node->keys.size(); ++i) {
            if (!(node->keys[i - 1] < node->keys[i])) {
                return false;
            }
        }
        for (const auto& key : node->keys) {
            if (lower.has_value() && !(lower.value() < key)) {
                return false;
            }
            if (upper.has_value() && !(key < upper.value())) {
                return false;
            }
        }
        if (!is_root && node->keys.size() < minKeysPerNonRootNode()) {
            return false;
        }
        if (node->keys.size() > maxKeysPerNode()) {
            return false;
        }
        counted += node->keys.size();
        if (node->leaf) {
            if (!node->children.empty()) {
                return false;
            }
            if (!leaf_depth.has_value()) {
                leaf_depth = depth;
            }
            return leaf_depth.value() == depth;
        }
        if (node->children.size() != node->keys.size() + 1) {
            return false;
        }
        for (std::size_t i = 0; i < node->children.size(); ++i) {
            std::optional<Key> child_lower = lower;
            std::optional<Key> child_upper = upper;
            if (i > 0) {
                child_lower = node->keys[i - 1];
            }
            if (i < node->keys.size()) {
                child_upper = node->keys[i];
            }
            if (!validateNode(node->children[i].get(), false, depth + 1, child_lower, child_upper, leaf_depth, counted)) {
                return false;
            }
        }
        return true;
    }

    std::size_t minimum_degree_;
    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

}  // namespace cc232::week13
