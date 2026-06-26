#ifndef CC232_SEMANA12_MAX_SUBARRAY_SEGMENT_TREE_H
#define CC232_SEMANA12_MAX_SUBARRAY_SEGMENT_TREE_H

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

struct MaxSubarrayNode {
    long long total = 0;
    long long bestPrefix = 0;
    long long bestSuffix = 0;
    long long bestSubarray = 0;
};

class MaxSubarraySegmentTree {
private:
    std::vector<MaxSubarrayNode> tree_;
    int n_ = 0;

    static MaxSubarrayNode makeLeaf(long long value) {
        return {value, value, value, value};
    }

    static MaxSubarrayNode combine(const MaxSubarrayNode& left, const MaxSubarrayNode& right) {
        MaxSubarrayNode result;
        result.total = left.total + right.total;
        result.bestPrefix = std::max(left.bestPrefix, left.total + right.bestPrefix);
        result.bestSuffix = std::max(right.bestSuffix, right.total + left.bestSuffix);
        result.bestSubarray = std::max({left.bestSubarray, right.bestSubarray, left.bestSuffix + right.bestPrefix});
        return result;
    }

    void build(const std::vector<long long>& values, int node, int left, int right) {
        if (left == right) {
            tree_[node] = makeLeaf(values[left]);
            return;
        }
        int mid = (left + right) / 2;
        build(values, node * 2, left, mid);
        build(values, node * 2 + 1, mid + 1, right);
        tree_[node] = combine(tree_[node * 2], tree_[node * 2 + 1]);
    }

    void pointSet(int node, int left, int right, int index, long long value) {
        if (left == right) {
            tree_[node] = makeLeaf(value);
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            pointSet(node * 2, left, mid, index, value);
        } else {
            pointSet(node * 2 + 1, mid + 1, right, index, value);
        }
        tree_[node] = combine(tree_[node * 2], tree_[node * 2 + 1]);
    }

    MaxSubarrayNode rangeQuery(int node, int left, int right, int queryLeft, int queryRight) const {
        if (queryLeft <= left && right <= queryRight) {
            return tree_[node];
        }
        int mid = (left + right) / 2;
        if (queryRight <= mid) {
            return rangeQuery(node * 2, left, mid, queryLeft, queryRight);
        }
        if (queryLeft > mid) {
            return rangeQuery(node * 2 + 1, mid + 1, right, queryLeft, queryRight);
        }
        return combine(rangeQuery(node * 2, left, mid, queryLeft, queryRight),
                       rangeQuery(node * 2 + 1, mid + 1, right, queryLeft, queryRight));
    }

public:
    MaxSubarraySegmentTree() = default;

    explicit MaxSubarraySegmentTree(const std::vector<long long>& values) {
        build(values);
    }

    void build(const std::vector<long long>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(std::max(1, 4 * n_), MaxSubarrayNode{});
        if (n_ > 0) {
            build(values, 1, 0, n_ - 1);
        }
    }

    void pointSet(int index, long long value) {
        if (index < 0 || index >= n_) {
            throw std::out_of_range("Indice invalido en MaxSubarraySegmentTree");
        }
        pointSet(1, 0, n_ - 1, index, value);
    }

    long long rangeMaxSubarray(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en MaxSubarraySegmentTree");
        }
        return rangeQuery(1, 0, n_ - 1, left, right).bestSubarray;
    }
};

}  // namespace cc232::week12

#endif
