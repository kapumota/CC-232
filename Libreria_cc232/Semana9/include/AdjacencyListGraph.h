#pragma once

#include "Graph.h"

#include <algorithm>
#include <vector>

namespace cc232 {

class AdjacencyListGraph final : public Graph {
 public:
  explicit AdjacencyListGraph(int vertices, bool directed = false)
      : adjacency_(vertices), directed_(directed) {
    if (vertices < 0) {
      throw std::invalid_argument("Cantidad de vertices invalida");
    }
  }

  int vertexCount() const override { return static_cast<int>(adjacency_.size()); }

  bool isDirected() const override { return directed_; }

  void addEdge(int from, int to, int weight = 1) override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    addDirectedEdge(from, to, weight);
    if (!directed_) {
      addDirectedEdge(to, from, weight);
    }
  }

  void removeEdge(int from, int to) override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    removeDirectedEdge(from, to);
    if (!directed_) {
      removeDirectedEdge(to, from);
    }
  }

  bool hasEdge(int from, int to) const override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    return std::any_of(adjacency_[from].begin(), adjacency_[from].end(),
                       [to](const Neighbor& edge) { return edge.to == to; });
  }

  int weight(int from, int to) const override {
    requireVertex(from, vertexCount());
    requireVertex(to, vertexCount());
    for (const auto& edge : adjacency_[from]) {
      if (edge.to == to) {
        return edge.weight;
      }
    }
    return GRAPH_INF;
  }

  std::vector<Neighbor> neighbors(int from) const override {
    requireVertex(from, vertexCount());
    return adjacency_[from];
  }

  std::vector<Edge> edges() const override {
    std::vector<Edge> result;
    for (int from = 0; from < vertexCount(); ++from) {
      for (const auto& edge : adjacency_[from]) {
        if (!directed_ && edge.to < from) {
          continue;
        }
        result.push_back({from, edge.to, edge.weight});
      }
    }
    return result;
  }

 private:
  void addDirectedEdge(int from, int to, int weight) {
    for (auto& edge : adjacency_[from]) {
      if (edge.to == to) {
        edge.weight = weight;
        return;
      }
    }
    adjacency_[from].push_back({to, weight});
  }

  void removeDirectedEdge(int from, int to) {
    auto& row = adjacency_[from];
    row.erase(std::remove_if(row.begin(), row.end(),
                             [to](const Neighbor& edge) { return edge.to == to; }),
              row.end());
  }

  std::vector<std::vector<Neighbor>> adjacency_;
  bool directed_{false};
};

}  // namespace cc232
