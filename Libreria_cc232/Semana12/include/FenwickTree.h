#ifndef CC232_SEMANA12_FENWICK_TREE_H
#define CC232_SEMANA12_FENWICK_TREE_H

#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class FenwickTree {
private:
    std::vector<long long> tree_;
    int n_ = 0;

    void checkIndex(int index) const {
        if (index < 0 || index >= n_) {
            throw std::out_of_range("Indice invalido en FenwickTree");
        }
    }

public:
    FenwickTree() = default;

    explicit FenwickTree(int size) : tree_(size + 1, 0), n_(size) {
        if (size < 0) {
            throw std::invalid_argument("El tamano no puede ser negativo");
        }
    }

    explicit FenwickTree(const std::vector<long long>& values) : FenwickTree(static_cast<int>(values.size())) {
        for (int i = 0; i < n_; ++i) {
            add(i, values[i]);
        }
    }

    void add(int index, long long delta) {
        checkIndex(index);
        for (int i = index + 1; i <= n_; i += i & -i) {
            tree_[i] += delta;
        }
    }

    long long prefixSum(int index) const {
        if (index < 0) {
            return 0;
        }
        if (index >= n_) {
            throw std::out_of_range("Indice invalido en prefixSum");
        }
        long long sum = 0;
        for (int i = index + 1; i > 0; i -= i & -i) {
            sum += tree_[i];
        }
        return sum;
    }

    long long rangeSum(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en FenwickTree");
        }
        return prefixSum(right) - prefixSum(left - 1);
    }

    int lowerBoundPrefix(long long target) const {
        if (target <= 0) {
            return 0;
        }
        int index = 0;
        long long accumulated = 0;
        int bit = 1;
        while ((bit << 1) <= n_) {
            bit <<= 1;
        }
        for (; bit > 0; bit >>= 1) {
            int next = index + bit;
            if (next <= n_ && accumulated + tree_[next] < target) {
                index = next;
                accumulated += tree_[next];
            }
        }
        if (index >= n_) {
            return -1;
        }
        return index;
    }

    int size() const { return n_; }
};

}  // namespace cc232::week12

#endif
