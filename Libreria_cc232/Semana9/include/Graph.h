#pragma once

#include "GraphTypes.h"

#include <stdexcept>
#include <vector>

namespace cc232 {

class Graph {
 public:
  virtual ~Graph() = default;

  virtual int vertexCount() const = 0;
  virtual bool isDirected() const = 0;
  virtual void addEdge(int from, int to, int weight = 1) = 0;
  virtual void removeEdge(int from, int to) = 0;
  virtual bool hasEdge(int from, int to) const = 0;
  virtual int weight(int from, int to) const = 0;
  virtual std::vector<Neighbor> neighbors(int from) const = 0;
  virtual std::vector<Edge> edges() const = 0;

  static void requireVertex(int vertex, int n) {
    if (vertex < 0 || vertex >= n) {
      throw std::out_of_range("Vertice fuera de rango");
    }
  }
};

}  // namespace cc232
