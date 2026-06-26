#ifndef CC232_SEMANA12_ASSIGNMENT_LAZY_SEGMENT_TREE_H
#define CC232_SEMANA12_ASSIGNMENT_LAZY_SEGMENT_TREE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class AssignmentLazySegmentTree {
private:
    std::vector<long long> tree_;
    std::vector<long long> lazyAssign_;
    std::vector<bool> hasAssign_;
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

    void applyAssign(int node, int left, int right, long long value) {
        tree_[node] = value * (right - left + 1);
        lazyAssign_[node] = value;
        hasAssign_[node] = true;
    }

    void push(int node, int left, int right) {
        if (!hasAssign_[node] || left == right) {
            return;
        }
        int mid = (left + right) / 2;
        applyAssign(node * 2, left, mid, lazyAssign_[node]);
        applyAssign(node * 2 + 1, mid + 1, right, lazyAssign_[node]);
        hasAssign_[node] = false;
    }

    void rangeAssign(int node, int left, int right, int queryLeft, int queryRight, long long value) {
        if (queryRight < left || right < queryLeft) {
            return;
        }
        if (queryLeft <= left && right <= queryRight) {
            applyAssign(node, left, right, value);
            return;
        }
        push(node, left, right);
        int mid = (left + right) / 2;
        rangeAssign(node * 2, left, mid, queryLeft, queryRight, value);
        rangeAssign(node * 2 + 1, mid + 1, right, queryLeft, queryRight, value);
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
    AssignmentLazySegmentTree() = default;

    explicit AssignmentLazySegmentTree(const std::vector<long long>& values) {
        build(values);
    }

    void build(const std::vector<long long>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(std::max(1, 4 * n_), 0);
        lazyAssign_.assign(std::max(1, 4 * n_), 0);
        hasAssign_.assign(std::max(1, 4 * n_), false);
        if (n_ > 0) {
            build(values, 1, 0, n_ - 1);
        }
    }

    void rangeAssign(int left, int right, long long value) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en AssignmentLazySegmentTree");
        }
        rangeAssign(1, 0, n_ - 1, left, right, value);
    }

    long long rangeSum(int left, int right) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en AssignmentLazySegmentTree");
        }
        return rangeSum(1, 0, n_ - 1, left, right);
    }
};

}  // namespace cc232::week12

#endif
