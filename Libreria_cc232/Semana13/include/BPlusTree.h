#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace cc232::week13 {

template <typename Key, typename Value>
struct BPlusTreeNode {
    explicit BPlusTreeNode(bool is_leaf) : leaf(is_leaf) {}

    bool leaf = true;
    std::vector<Key> keys;
    std::vector<Value> values;
    std::vector<std::unique_ptr<BPlusTreeNode<Key, Value>>> children;
    BPlusTreeNode<Key, Value>* next = nullptr;
};

template <typename Key, typename Value>
class BPlusTree {
public:
    explicit BPlusTree(std::size_t minimum_degree) : minimum_degree_(minimum_degree) {
        if (minimum_degree_ < 2) {
            throw std::invalid_argument("El grado minimo debe ser al menos dos");
        }
        root_ = std::make_unique<Node>(true);
    }

    [[nodiscard]] std::size_t minimumDegree() const { return minimum_degree_; }
    [[nodiscard]] std::size_t maxKeysPerNode() const { return 2 * minimum_degree_ - 1; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    bool insert(const Key& key, const Value& value) {
        SplitResult split = insertRecursive(root_.get(), key, value);
        if (split.updated_existing) {
            return false;
        }
        if (split.right != nullptr) {
            auto new_root = std::make_unique<Node>(false);
            new_root->keys.push_back(split.promoted_key.value());
            new_root->children.push_back(std::move(root_));
            new_root->children.push_back(std::move(split.right));
            root_ = std::move(new_root);
        }
        ++size_;
        return true;
    }

    [[nodiscard]] std::optional<Value> find(const Key& key) const {
        const Node* leaf = findLeaf(key);
        if (leaf == nullptr) {
            return std::nullopt;
        }
        const auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        const std::size_t index = static_cast<std::size_t>(it - leaf->keys.begin());
        if (it != leaf->keys.end() && *it == key) {
            return leaf->values[index];
        }
        return std::nullopt;
    }

    [[nodiscard]] bool contains(const Key& key) const {
        return find(key).has_value();
    }

    [[nodiscard]] std::vector<std::pair<Key, Value>> rangeQuery(const Key& low, const Key& high) const {
        std::vector<std::pair<Key, Value>> result;
        if (high < low) {
            return result;
        }
        const Node* leaf = findLeaf(low);
        while (leaf != nullptr) {
            for (std::size_t i = 0; i < leaf->keys.size(); ++i) {
                if (leaf->keys[i] < low) {
                    continue;
                }
                if (high < leaf->keys[i]) {
                    return result;
                }
                result.emplace_back(leaf->keys[i], leaf->values[i]);
            }
            leaf = leaf->next;
        }
        return result;
    }

    [[nodiscard]] std::vector<Key> keys() const {
        std::vector<Key> result;
        const Node* leaf = leftmostLeaf();
        while (leaf != nullptr) {
            result.insert(result.end(), leaf->keys.begin(), leaf->keys.end());
            leaf = leaf->next;
        }
        return result;
    }

    [[nodiscard]] std::size_t height() const {
        if (empty()) {
            return 0;
        }
        std::size_t h = 1;
        const Node* current = root_.get();
        while (!current->leaf) {
            ++h;
            current = current->children.front().get();
        }
        return h;
    }

    [[nodiscard]] bool validate() const {
        if (!root_) {
            return size_ == 0;
        }
        std::size_t counted = 0;
        std::optional<std::size_t> leaf_depth;
        std::optional<Key> lower;
        std::optional<Key> upper;
        const bool tree_ok = validateNode(root_.get(), true, 0, lower, upper, leaf_depth, counted);
        return tree_ok && counted == size_ && validateLeafLinks();
    }

private:
    using Node = BPlusTreeNode<Key, Value>;

    struct SplitResult {
        std::optional<Key> promoted_key;
        std::unique_ptr<Node> right;
        bool updated_existing = false;
    };

    SplitResult insertRecursive(Node* node, const Key& key, const Value& value) {
        if (node->leaf) {
            const auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
            const std::size_t index = static_cast<std::size_t>(it - node->keys.begin());
            if (it != node->keys.end() && *it == key) {
                node->values[index] = value;
                return {std::nullopt, nullptr, true};
            }
            node->keys.insert(it, key);
            node->values.insert(node->values.begin() + static_cast<std::ptrdiff_t>(index), value);
            if (node->keys.size() <= maxKeysPerNode()) {
                return {std::nullopt, nullptr, false};
            }
            return splitLeaf(node);
        }

        const std::size_t child_index = internalChildIndex(node, key);
        SplitResult child_split = insertRecursive(node->children[child_index].get(), key, value);
        if (child_split.updated_existing || child_split.right == nullptr) {
            return child_split;
        }

        node->keys.insert(node->keys.begin() + static_cast<std::ptrdiff_t>(child_index), child_split.promoted_key.value());
        node->children.insert(node->children.begin() + static_cast<std::ptrdiff_t>(child_index + 1), std::move(child_split.right));
        if (node->keys.size() <= maxKeysPerNode()) {
            return {std::nullopt, nullptr, false};
        }
        return splitInternal(node);
    }

    SplitResult splitLeaf(Node* node) {
        const std::size_t split_index = node->keys.size() / 2;
        auto right = std::make_unique<Node>(true);
        right->keys.assign(node->keys.begin() + static_cast<std::ptrdiff_t>(split_index), node->keys.end());
        right->values.assign(node->values.begin() + static_cast<std::ptrdiff_t>(split_index), node->values.end());
        node->keys.resize(split_index);
        node->values.resize(split_index);

        right->next = node->next;
        node->next = right.get();
        const Key promoted = right->keys.front();
        return {promoted, std::move(right), false};
    }

    SplitResult splitInternal(Node* node) {
        const std::size_t mid = node->keys.size() / 2;
        const Key promoted = node->keys[mid];
        auto right = std::make_unique<Node>(false);

        right->keys.assign(node->keys.begin() + static_cast<std::ptrdiff_t>(mid + 1), node->keys.end());
        node->keys.resize(mid);

        for (std::size_t i = mid + 1; i < node->children.size(); ++i) {
            right->children.push_back(std::move(node->children[i]));
        }
        node->children.resize(mid + 1);
        return {promoted, std::move(right), false};
    }

    [[nodiscard]] const Node* findLeaf(const Key& key) const {
        const Node* current = root_.get();
        if (current == nullptr || (current->leaf && current->keys.empty())) {
            return current;
        }
        while (current != nullptr && !current->leaf) {
            const std::size_t index = internalChildIndex(current, key);
            current = current->children[index].get();
        }
        return current;
    }

    static std::size_t internalChildIndex(const Node* node, const Key& key) {
        // En B+Tree, una clave igual al separador baja al hijo derecho.
        return static_cast<std::size_t>(std::upper_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin());
    }

    [[nodiscard]] const Node* leftmostLeaf() const {
        const Node* current = root_.get();
        if (current == nullptr) {
            return nullptr;
        }
        while (!current->leaf) {
            current = current->children.front().get();
        }
        return current;
    }

    static Key firstKey(const Node* node) {
        const Node* current = node;
        while (!current->leaf) {
            current = current->children.front().get();
        }
        return current->keys.front();
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
        if (!is_root && node->keys.empty()) {
            return false;
        }
        if (node->keys.size() > maxKeysPerNode()) {
            return false;
        }
        if (node->leaf) {
            if (node->values.size() != node->keys.size() || !node->children.empty()) {
                return false;
            }
            for (const auto& key : node->keys) {
                if (lower.has_value() && key < lower.value()) {
                    return false;
                }
                if (upper.has_value() && !(key < upper.value())) {
                    return false;
                }
            }
            counted += node->keys.size();
            if (!leaf_depth.has_value()) {
                leaf_depth = depth;
            }
            return leaf_depth.value() == depth;
        }

        if (!node->values.empty() || node->children.size() != node->keys.size() + 1) {
            return false;
        }
        for (std::size_t i = 0; i < node->keys.size(); ++i) {
            if (node->children[i + 1]->keys.empty()) {
                return false;
            }
            if (!(node->keys[i] == firstKey(node->children[i + 1].get()))) {
                return false;
            }
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

    [[nodiscard]] bool validateLeafLinks() const {
        std::vector<Key> linked_keys;
        const Node* leaf = leftmostLeaf();
        while (leaf != nullptr) {
            if (!leaf->leaf) {
                return false;
            }
            linked_keys.insert(linked_keys.end(), leaf->keys.begin(), leaf->keys.end());
            leaf = leaf->next;
        }
        return linked_keys == keys();
    }

    std::size_t minimum_degree_;
    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

}  // namespace cc232::week13
