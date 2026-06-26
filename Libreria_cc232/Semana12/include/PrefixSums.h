#ifndef CC232_SEMANA12_PREFIX_SUMS_H
#define CC232_SEMANA12_PREFIX_SUMS_H

#include <stdexcept>
#include <vector>

namespace cc232::week12 {

inline std::vector<long long> buildPrefixSums(const std::vector<long long>& values) {
    std::vector<long long> prefix(values.size() + 1, 0);
    for (std::size_t i = 0; i < values.size(); ++i) {
        prefix[i + 1] = prefix[i] + values[i];
    }
    return prefix;
}

inline long long rangeSumFromPrefix(const std::vector<long long>& prefix, int left, int right) {
    if (left < 0 || right < left || right + 1 >= static_cast<int>(prefix.size())) {
        throw std::out_of_range("Rango invalido para suma de prefijos");
    }
    return prefix[right + 1] - prefix[left];
}

class PrefixSum2D {
private:
    std::vector<std::vector<long long>> prefix_;
    int rows_ = 0;
    int cols_ = 0;

public:
    PrefixSum2D() = default;

    explicit PrefixSum2D(const std::vector<std::vector<long long>>& matrix) {
        build(matrix);
    }

    void build(const std::vector<std::vector<long long>>& matrix) {
        rows_ = static_cast<int>(matrix.size());
        cols_ = rows_ == 0 ? 0 : static_cast<int>(matrix.front().size());
        for (const auto& row : matrix) {
            if (static_cast<int>(row.size()) != cols_) {
                throw std::invalid_argument("La matriz debe ser rectangular");
            }
        }
        prefix_.assign(rows_ + 1, std::vector<long long>(cols_ + 1, 0));
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                prefix_[i + 1][j + 1] = matrix[i][j] + prefix_[i][j + 1] + prefix_[i + 1][j] - prefix_[i][j];
            }
        }
    }

    long long rectangleSum(int row1, int col1, int row2, int col2) const {
        if (row1 < 0 || col1 < 0 || row2 < row1 || col2 < col1 || row2 >= rows_ || col2 >= cols_) {
            throw std::out_of_range("Rectangulo invalido");
        }
        return prefix_[row2 + 1][col2 + 1] - prefix_[row1][col2 + 1] - prefix_[row2 + 1][col1] + prefix_[row1][col1];
    }

    int rows() const { return rows_; }
    int cols() const { return cols_; }
};

}  // namespace cc232::week12

#endif
