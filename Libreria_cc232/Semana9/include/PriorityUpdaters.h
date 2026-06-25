#pragma once

#include "Graph.h"
#include "GraphTypes.h"

#include <vector>

namespace cc232 {

struct PrimPriorityUpdater {
  void operator()(const Graph& graph, int from, int to, std::vector<int>& priority,
                  std::vector<int>& parent) const {
    const int candidate = graph.weight(from, to);
    if (candidate < priority[to]) {
      priority[to] = candidate;
      parent[to] = from;
    }
  }
};

struct DijkstraPriorityUpdater {
  void operator()(const Graph& graph, int from, int to, std::vector<int>& priority,
                  std::vector<int>& parent) const {
    if (priority[from] >= GRAPH_INF / 2) {
      return;
    }
    const int candidate = priority[from] + graph.weight(from, to);
    if (candidate < priority[to]) {
      priority[to] = candidate;
      parent[to] = from;
    }
  }
};

}  // namespace cc232
