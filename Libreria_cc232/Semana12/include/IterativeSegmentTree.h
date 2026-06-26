#ifndef CC232_SEMANA12_ITERATIVE_SEGMENT_TREE_H
#define CC232_SEMANA12_ITERATIVE_SEGMENT_TREE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class IterativeSegmentTree {
private:
    std::vector<long long> tree_;
    int n_ = 0;

public:
    IterativeSegmentTree() = default;

    explicit IterativeSegmentTree(const std::vector<long long>& values) {
        build(values);
    }

    void build(const std::vector<long long>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(2 * std::max(1, n_), 0);
        for (int i = 0; i < n_; ++i) {
            tree_[n_ + i] = values[i];
        }
        for (int i = n_ - 1; i > 0; --i) {
            tree_[i] = tree_[i << 1] + tree_[i << 1 | 1];
        }
    }

    void pointSet(int index, long long value) {
        if (index < 0 || index >= n_) {
            throw std::out_of_range("Indice invalido en IterativeSegmentTree");
        }
        int position = index + n_;
        tree_[position] = value;
        for (position >>= 1; position > 0; position >>= 1) {
            tree_[position] = tree_[position << 1] + tree_[position << 1 | 1];
        }
    }

    long long rangeSum(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en IterativeSegmentTree");
        }
        long long answer = 0;
        int l = left + n_;
        int r = right + n_ + 1;
        while (l < r) {
            if (l & 1) {
                answer += tree_[l++];
            }
            if (r & 1) {
                answer += tree_[--r];
            }
            l >>= 1;
            r >>= 1;
        }
        return answer;
    }
};

}  // namespace cc232::week12

#endif
