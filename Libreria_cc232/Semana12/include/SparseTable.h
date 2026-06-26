#ifndef CC232_SEMANA12_SPARSE_TABLE_H
#define CC232_SEMANA12_SPARSE_TABLE_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

template <typename T>
class SparseTable {
private:
    std::vector<std::vector<T>> table_;
    std::vector<int> logs_;
    std::function<T(const T&, const T&)> combine_;
    int n_ = 0;

public:
    SparseTable() = default;

    SparseTable(const std::vector<T>& values, std::function<T(const T&, const T&)> combine)
        : combine_(std::move(combine)) {
        build(values);
    }

    void build(const std::vector<T>& values) {
        n_ = static_cast<int>(values.size());
        logs_.assign(n_ + 1, 0);
        for (int i = 2; i <= n_; ++i) {
            logs_[i] = logs_[i / 2] + 1;
        }
        int levels = n_ == 0 ? 1 : logs_[n_] + 1;
        table_.assign(levels, std::vector<T>(std::max(1, n_)));
        if (n_ == 0) {
            return;
        }
        table_[0] = values;
        for (int k = 1; k < levels; ++k) {
            int length = 1 << k;
            int half = length >> 1;
            for (int i = 0; i + length <= n_; ++i) {
                table_[k][i] = combine_(table_[k - 1][i], table_[k - 1][i + half]);
            }
        }
    }

    T query(int left, int right) const {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en SparseTable");
        }
        int k = logs_[right - left + 1];
        return combine_(table_[k][left], table_[k][right - (1 << k) + 1]);
    }
};

inline SparseTable<long long> makeMinSparseTable(const std::vector<long long>& values) {
    return SparseTable<long long>(values, [](const long long& a, const long long& b) { return std::min(a, b); });
}

inline SparseTable<long long> makeMaxSparseTable(const std::vector<long long>& values) {
    return SparseTable<long long>(values, [](const long long& a, const long long& b) { return std::max(a, b); });
}

inline SparseTable<long long> makeGcdSparseTable(const std::vector<long long>& values) {
    return SparseTable<long long>(values, [](const long long& a, const long long& b) { return std::gcd(a, b); });
}

}  // namespace cc232::week12

#endif
