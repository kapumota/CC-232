#pragma once

#include <limits>
#include <string>
#include <vector>

namespace cc232 {

constexpr int GRAPH_INF = std::numeric_limits<int>::max() / 4;

struct Neighbor {
  int to{};
  int weight{1};
};

struct Edge {
  int from{};
  int to{};
  int weight{1};
};

struct TraversalResult {
  std::vector<int> order;
  std::vector<int> parent;
  std::vector<int> distance;
  std::vector<int> entry;
  std::vector<int> exit;
};

struct ShortestPathResult {
  std::vector<int> distance;
  std::vector<int> parent;
};

struct PrioritySearchResult {
  std::vector<int> priority;
  std::vector<int> parent;
  std::vector<int> order;
  std::vector<bool> finalized;
};

struct MstResult {
  int totalWeight{0};
  std::vector<Edge> edges;
};

struct BiconnectedResult {
  std::vector<std::vector<Edge>> components;
  std::vector<int> articulationPoints;
};

inline std::string formatDistance(int value) {
  if (value >= GRAPH_INF / 2) {
    return "INF";
  }
  return std::to_string(value);
}

}  // namespace cc232
