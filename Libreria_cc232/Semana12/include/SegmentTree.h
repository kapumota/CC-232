#ifndef CC232_SEMANA12_SEGMENT_TREE_H
#define CC232_SEMANA12_SEGMENT_TREE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class SegmentTree {
private:
    std::vector<long long> tree_;
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

    void pointSet(int node, int left, int right, int index, long long value) {
        if (left == right) {
            tree_[node] = value;
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            pointSet(node * 2, left, mid, index, value);
        } else {
            pointSet(node * 2 + 1, mid + 1, right, index, value);
        }
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    long long rangeSum(int node, int left, int right, int queryLeft, int queryRight) const {
        if (queryRight < left || right < queryLeft) {
            return 0;
        }
        if (queryLeft <= left && right <= queryRight) {
            return tree_[node];
        }
        int mid = (left + right) / 2;
        return rangeSum(node * 2, left, mid, queryLeft, queryRight) +
               rangeSum(node * 2 + 1, mid + 1, right, queryLeft, queryRight);
    }

public:
    SegmentTree() = default;

    explicit SegmentTree(const std::vector<long long>& values) {
        build(values);
    }

    void build(const std::vector<long long>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(std::max(1, 4 * n_), 0);
        if (n_ > 0) {
            build(values, 1, 0, n_ - 1);
        }
    }

    void pointSet(int index, long long value) {
        if (index < 0 || index >= n_) {
            throw std::out_of_range("Indice invalido en SegmentTree");
        }
        pointSet(1, 0, n_ - 1, index, value);
    }

    long long rangeSum(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en SegmentTree");
        }
        return rangeSum(1, 0, n_ - 1, left, right);
    }

    int size() const { return n_; }
};

}  // namespace cc232::week12

#endif
