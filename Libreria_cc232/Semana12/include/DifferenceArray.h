#ifndef CC232_SEMANA12_DIFFERENCE_ARRAY_H
#define CC232_SEMANA12_DIFFERENCE_ARRAY_H

#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class DifferenceArray {
private:
    std::vector<long long> diff_;
    int n_ = 0;

public:
    DifferenceArray() = default;

    explicit DifferenceArray(int size) : diff_(size + 1, 0), n_(size) {
        if (size < 0) {
            throw std::invalid_argument("El tamano no puede ser negativo");
        }
    }

    explicit DifferenceArray(const std::vector<long long>& values) : diff_(values.size() + 1, 0), n_(static_cast<int>(values.size())) {
        long long previous = 0;
        for (int i = 0; i < n_; ++i) {
            diff_[i] = values[i] - previous;
            previous = values[i];
        }
    }

    void rangeAdd(int left, int right, long long delta) {
        if (left < 0 || right < left || right >= n_) {
            throw std::out_of_range("Rango invalido en DifferenceArray");
        }
        diff_[left] += delta;
        if (right + 1 < n_) {
            diff_[right + 1] -= delta;
        }
    }

    std::vector<long long> materialize() const {
        std::vector<long long> values(n_, 0);
        long long current = 0;
        for (int i = 0; i < n_; ++i) {
            current += diff_[i];
            values[i] = current;
        }
        return values;
    }

    int size() const { return n_; }
};

}  // namespace cc232::week12

#endif
