#ifndef CC232_SEMANA12_FENWICK_RANGE_H
#define CC232_SEMANA12_FENWICK_RANGE_H

#include "FenwickTree.h"

#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class FenwickRange {
private:
    FenwickTree bit1_;
    FenwickTree bit2_;
    int n_ = 0;

    void internalAdd(FenwickTree& bit, int index, long long value) {
        if (index < n_) {
            bit.add(index, value);
        }
    }

    long long prefixSum(int index) const {
        if (index < 0) {
            return 0;
        }
        if (index >= n_) {
            throw std::out_of_range("Indice invalido en FenwickRange");
        }
        return bit1_.prefixSum(index) * (index + 1) - bit2_.prefixSum(index);
    }

public:
    FenwickRange() = default;

    explicit FenwickRange(int size) : bit1_(size), bit2_(size), n_(size) {}

    explicit FenwickRange(const std::vector<long long>& values) : FenwickRange(static_cast<int>(values.size())) {
        for (int i = 0; i < n_; ++i) {
            rangeAdd(i, i, values[i]);
        }
    }

    void rangeAdd(int left, int right, long long delta) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en FenwickRange");
        }
        internalAdd(bit1_, left, delta);
        internalAdd(bit1_, right + 1, -delta);
        internalAdd(bit2_, left, delta * left);
        internalAdd(bit2_, right + 1, -delta * (right + 1));
    }

    long long rangeSum(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en FenwickRange");
        }
        return prefixSum(right) - prefixSum(left - 1);
    }
};

}  // namespace cc232::week12

#endif
