#ifndef CC232_SEMANA12_LAZY_SEGMENT_TREE_H
#define CC232_SEMANA12_LAZY_SEGMENT_TREE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class LazySegmentTree {
private:
    std::vector<long long> tree_;
    std::vector<long long> lazy_;
    int n_ = 0;

    void build(const std::vector<long long>& values, int node, int left, int right) {
        if (left == right) {
            tree_[node] = values[left];
            return;
        }
        int mid = (left + right) / 2;
        build(values, node * 2, left, mid);
        build(values, node * 2 + 1, mid + 1, right);
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    void apply(int node, int left, int right, long long delta) {
        tree_[node] += delta * (right - left + 1);
        lazy_[node] += delta;
    }

    void push(int node, int left, int right) {
        if (lazy_[node] == 0 || left == right) {
            return;
        }
        int mid = (left + right) / 2;
        apply(node * 2, left, mid, lazy_[node]);
        apply(node * 2 + 1, mid + 1, right, lazy_[node]);
        lazy_[node] = 0;
    }

    void rangeAdd(int node, int left, int right, int queryLeft, int queryRight, long long delta) {
        if (queryRight < left || right < queryLeft) {
            return;
        }
        if (queryLeft <= left && right <= queryRight) {
            apply(node, left, right, delta);
            return;
        }
        push(node, left, right);
        int mid = (left + right) / 2;
        rangeAdd(node * 2, left, mid, queryLeft, queryRight, delta);
        rangeAdd(node * 2 + 1, mid + 1, right, queryLeft, queryRight, delta);
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    long long rangeSum(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft) {
            return 0;
        }
        if (queryLeft <= left && right <= queryRight) {
            return tree_[node];
        }
        push(node, left, right);
        int mid = (left + right) / 2;
        return rangeSum(node * 2, left, mid, queryLeft, queryRight) +
               rangeSum(node * 2 + 1, mid + 1, right, queryLeft, queryRight);
    }

public:
    LazySegmentTree() = default;

    explicit LazySegmentTree(const std::vector<long long>& values) {
        build(values);
    }

    void build(const std::vector<long long>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(std::max(1, 4 * n_), 0);
        lazy_.assign(std::max(1, 4 * n_), 0);
        if (n_ > 0) {
            build(values, 1, 0, n_ - 1);
        }
    }

    void rangeAdd(int left, int right, long long delta) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en LazySegmentTree");
        }
        rangeAdd(1, 0, n_ - 1, left, right, delta);
    }

    long long rangeSum(int left, int right) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en LazySegmentTree");
        }
        return rangeSum(1, 0, n_ - 1, left, right);
    }
};

}  // namespace cc232::week12

#endif
