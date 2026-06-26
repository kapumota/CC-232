#ifndef CC232_SEMANA12_RANGE_QUERY_ORACLE_H
#define CC232_SEMANA12_RANGE_QUERY_ORACLE_H

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class RangeQueryOracle {
private:
    std::vector<long long> values_;

    void checkRange(int left, int right) const {
        if (left < 0 || right < left || right >= static_cast<int>(values_.size())) {
            throw std::out_of_range("Rango invalido en oraculo ingenuo");
        }
    }

public:
    RangeQueryOracle() = default;
    explicit RangeQueryOracle(std::vector<long long> values) : values_(std::move(values)) {}

    void pointSet(int index, long long value) {
        if (index < 0 || index >= static_cast<int>(values_.size())) {
            throw std::out_of_range("Indice invalido en oraculo");
        }
        values_[index] = value;
    }

    void pointAdd(int index, long long delta) {
        if (index < 0 || index >= static_cast<int>(values_.size())) {
            throw std::out_of_range("Indice invalido en oraculo");
        }
        values_[index] += delta;
    }

    void rangeAdd(int left, int right, long long delta) {
        checkRange(left, right);
        for (int i = left; i <= right; ++i) {
            values_[i] += delta;
        }
    }

    void rangeAssign(int left, int right, long long value) {
        checkRange(left, right);
        for (int i = left; i <= right; ++i) {
            values_[i] = value;
        }
    }

    long long rangeSum(int left, int right) const {
        checkRange(left, right);
        long long sum = 0;
        for (int i = left; i <= right; ++i) {
            sum += values_[i];
        }
        return sum;
    }

    long long rangeMin(int left, int right) const {
        checkRange(left, right);
        return *std::min_element(values_.begin() + left, values_.begin() + right + 1);
    }

    long long rangeMax(int left, int right) const {
        checkRange(left, right);
        return *std::max_element(values_.begin() + left, values_.begin() + right + 1);
    }

    const std::vector<long long>& values() const { return values_; }
};

}  // namespace cc232::week12

#endif
