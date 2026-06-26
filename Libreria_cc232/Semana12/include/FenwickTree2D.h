#ifndef CC232_SEMANA12_FENWICK_TREE_2D_H
#define CC232_SEMANA12_FENWICK_TREE_2D_H

#include <stdexcept>
#include <vector>

namespace cc232::week12 {

class FenwickTree2D {
private:
    std::vector<std::vector<long long>> tree_;
    int rows_ = 0;
    int cols_ = 0;

public:
    FenwickTree2D() = default;

    FenwickTree2D(int rows, int cols) : tree_(rows + 1, std::vector<long long>(cols + 1, 0)), rows_(rows), cols_(cols) {
        if (rows < 0 || cols < 0) {
            throw std::invalid_argument("Dimensiones invalidas en FenwickTree2D");
        }
    }

    explicit FenwickTree2D(const std::vector<std::vector<long long>>& matrix) {
        rows_ = static_cast<int>(matrix.size());
        cols_ = rows_ == 0 ? 0 : static_cast<int>(matrix.front().size());
        tree_.assign(rows_ + 1, std::vector<long long>(cols_ + 1, 0));
        for (int i = 0; i < rows_; ++i) {
            if (static_cast<int>(matrix[i].size()) != cols_) {
                throw std::invalid_argument("La matriz debe ser rectangular");
            }
            for (int j = 0; j < cols_; ++j) {
                add(i, j, matrix[i][j]);
            }
        }
    }

    void add(int row, int col, long long delta) {
        if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
            throw std::out_of_range("Indice invalido en FenwickTree2D");
        }
        for (int i = row + 1; i <= rows_; i += i & -i) {
            for (int j = col + 1; j <= cols_; j += j & -j) {
                tree_[i][j] += delta;
            }
        }
    }

    long long prefixSum(int row, int col) const {
        if (row < 0 || col < 0) {
            return 0;
        }
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Indice invalido en prefixSum 2D");
        }
        long long sum = 0;
        for (int i = row + 1; i > 0; i -= i & -i) {
            for (int j = col + 1; j > 0; j -= j & -j) {
                sum += tree_[i][j];
            }
        }
        return sum;
    }

    long long rectangleSum(int row1, int col1, int row2, int col2) const {
        if (row1 < 0 || col1 < 0 || row2 < row1 || col2 < col1 || row2 >= rows_ || col2 >= cols_) {
            throw std::out_of_range("Rectangulo invalido en FenwickTree2D");
        }
        return prefixSum(row2, col2) - prefixSum(row1 - 1, col2) - prefixSum(row2, col1 - 1) + prefixSum(row1 - 1, col1 - 1);
    }
};

}  // namespace cc232::week12

#endif
