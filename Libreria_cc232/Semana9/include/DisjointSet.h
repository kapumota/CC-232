#pragma once

#include <numeric>
#include <stdexcept>
#include <vector>

namespace cc232 {

class DisjointSet {
 public:
  explicit DisjointSet(int n) : parent_(n), rank_(n, 0) {
    if (n < 0) {
      throw std::invalid_argument("Cantidad de elementos invalida");
    }
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int x) {
    if (x < 0 || x >= static_cast<int>(parent_.size())) {
      throw std::out_of_range("Elemento fuera de rango");
    }
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }
    return parent_[x];
  }

  bool unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) {
      return false;
    }
    if (rank_[rootA] < rank_[rootB]) {
      std::swap(rootA, rootB);
    }
    parent_[rootB] = rootA;
    if (rank_[rootA] == rank_[rootB]) {
      ++rank_[rootA];
    }
    return true;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

}  // namespace cc232
