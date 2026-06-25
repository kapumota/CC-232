#pragma once

#include "Graph.h"

#include <algorithm>
#include <vector>

namespace cc232 {

class EdgeListGraph final : public Graph {
 public:
  explicit EdgeListGraph(int vertices, bool directed = false)
      : vertices_(vertices), directed_(directed) {
    if (vertices < 0) {
      throw std::invalid_argument("Cantidad de vertices invalida");
    }
  }

  int vertexCount() const override { return vertices_; }

  bool isDirected() const override { return directed_; }

  void addEdge(int from, int to, int weight = 1) override {
    requireVertex(from, vertices_);
    requireVertex(to, vertices_);
    removeEdge(from, to);
    edgeList_.push_back({from, to, weight});
    if (!directed_ && from != to) {
      edgeList_.push_back({to, from, weight});
    }
  }

  void removeEdge(int from, int to) override {
    requireVertex(from, vertices_);
    requireVertex(to, vertices_);
    edgeList_.erase(std::remove_if(edgeList_.begin(), edgeList_.end(),
                                   [this, from, to](const Edge& edge) {
                                     if (directed_) {
                                       return edge.from == from && edge.to == to;
                                     }
                                     return (edge.from == from && edge.to == to) ||
                                            (edge.from == to && edge.to == from);
                                   }),
                    edgeList_.end());
  }

  bool hasEdge(int from, int to) const override {
    requireVertex(from, vertices_);
    requireVertex(to, vertices_);
    return std::any_of(edgeList_.begin(), edgeList_.end(), [from, to](const Edge& edge) {
      return edge.from == from && edge.to == to;
    });
  }

  int weight(int from, int to) const override {
    requireVertex(from, vertices_);
    requireVertex(to, vertices_);
    for (const auto& edge : edgeList_) {
      if (edge.from == from && edge.to == to) {
        return edge.weight;
      }
    }
    return GRAPH_INF;
  }

  std::vector<Neighbor> neighbors(int from) const override {
    requireVertex(from, vertices_);
    std::vector<Neighbor> result;
    for (const auto& edge : edgeList_) {
      if (edge.from == from) {
        result.push_back({edge.to, edge.weight});
      }
    }
    return result;
  }

  std::vector<Edge> edges() const override {
    if (directed_) {
      return edgeList_;
    }
    std::vector<Edge> result;
    for (const auto& edge : edgeList_) {
      if (edge.from <= edge.to) {
        result.push_back(edge);
      }
    }
    return result;
  }

 private:
  int vertices_{0};
  bool directed_{false};
  std::vector<Edge> edgeList_;
};

}  // namespace cc232
