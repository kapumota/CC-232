#ifndef CC232_SEMANA12_MONOID_SEGMENT_TREE_H
#define CC232_SEMANA12_MONOID_SEGMENT_TREE_H

#include <functional>
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

template <typename T>
class MonoidSegmentTree {
private:
    std::vector<T> tree_;
    int n_ = 0;
    T identity_;
    std::function<T(const T&, const T&)> combine_;

public:
    MonoidSegmentTree() = default;

    MonoidSegmentTree(const std::vector<T>& values, T identity, std::function<T(const T&, const T&)> combine)
        : identity_(identity), combine_(std::move(combine)) {
        build(values);
    }

    void build(const std::vector<T>& values) {
        n_ = static_cast<int>(values.size());
        tree_.assign(2 * std::max(1, n_), identity_);
        for (int i = 0; i < n_; ++i) {
            tree_[n_ + i] = values[i];
        }
        for (int i = n_ - 1; i > 0; --i) {
            tree_[i] = combine_(tree_[i << 1], tree_[i << 1 | 1]);
        }
    }

    void pointSet(int index, T value) {
        if (index < 0 || index >= n_) {
            throw std::out_of_range("Indice invalido en MonoidSegmentTree");
        }
        int position = index + n_;
        tree_[position] = value;
        for (position >>= 1; position > 0; position >>= 1) {
            tree_[position] = combine_(tree_[position << 1], tree_[position << 1 | 1]);
        }
    }

    T rangeQuery(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en MonoidSegmentTree");
        }
        T answerLeft = identity_;
        T answerRight = identity_;
        int l = left + n_;
        int r = right + n_ + 1;
        while (l < r) {
            if (l & 1) {
                answerLeft = combine_(answerLeft, tree_[l++]);
            }
            if (r & 1) {
                answerRight = combine_(tree_[--r], answerRight);
            }
            l >>= 1;
            r >>= 1;
        }
        return combine_(answerLeft, answerRight);
    }
};

}  // namespace cc232::week12

#endif
