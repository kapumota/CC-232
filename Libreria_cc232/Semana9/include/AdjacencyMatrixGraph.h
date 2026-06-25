#pragma once

#include "Graph.h"

#include <algorithm>
#include <vector>

namespace cc232 {

class AdjacencyMatrixGraph final : public Graph {
 public:
  explicit AdjacencyMatrixGraph(int vertices, bool directed = false)
      : matrix_(vertices, std::vector<int>(vertices, GRAPH_INF)), directed_(directed) {
    if (vertices < 0) {
      throw std::invalid_argument("Cantidad de vertices invalida");
    }
  }

  int vertexCount() const override { return static_cast<int>(matrix_.size()); }

  bool isDirected() const override { return directed_; }

  void addEdge(int from, int to, int weight = 1) override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    matrix_[from][to] = weight;
    if (!directed_) {
      matrix_[to][from] = weight;
    }
  }

  void removeEdge(int from, int to) override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    matrix_[from][to] = GRAPH_INF;
    if (!directed_) {
      matrix_[to][from] = GRAPH_INF;
    }
  }

  bool hasEdge(int from, int to) const override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    return matrix_[from][to] < GRAPH_INF / 2;
  }

  int weight(int from, int to) const override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    return matrix_[from][to];
  }

  std::vector<Neighbor> neighbors(int from) const override {
    requireVertex(from, vertexCount());
    std::vector<Neighbor> result;
    for (int to = 0; to < vertexCount(); ++to) {
      if (hasEdge(from, to)) {
        result.push_back({to, matrix_[from][to]});
      }
    }
    return result;
  }

  std::vector<Edge> edges() const override {
    std::vector<Edge> result;
    for (int from = 0; from < vertexCount(); ++from) {
      for (int to = 0; to < vertexCount(); ++to) {
        if (!hasEdge(from, to)) {
          continue;
        }
        if (!directed_ && to < from) {
          continue;
        }
        result.push_back({from, to, matrix_[from][to]});
      }
    }
    return result;
  }

 private:
  std::vector<std::vector<int>> matrix_;
  bool directed_{false};
};

}  // namespace cc232
