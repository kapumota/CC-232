#pragma once

#include "DisjointSet.h"
#include "Graph.h"
#include "GraphTypes.h"
#include "PriorityUpdaters.h"

#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <vector>

namespace cc232 {

inline TraversalResult bfs(const Graph& graph, int source) {
  Graph::requireVertex(source, graph.vertexCount());
  const int n = graph.vertexCount();
  TraversalResult result;
  result.parent.assign(n, -1);
  result.distance.assign(n, GRAPH_INF);
  result.entry.assign(n, -1);
  result.exit.assign(n, -1);

  std::queue<int> pending;
  result.distance[source] = 0;
  pending.push(source);

  while (!pending.empty()) {
    const int from = pending.front();
    pending.pop();
    result.order.push_back(from);
    for (const auto& edge : graph.neighbors(from)) {
      if (result.distance[edge.to] < GRAPH_INF / 2) {
        continue;
      }
      result.distance[edge.to] = result.distance[from] + 1;
      result.parent[edge.to] = from;
      pending.push(edge.to);
    }
  }
  return result;
}

inline void dfsRecursiveVisit(const Graph& graph, int from, TraversalResult& result,
                              std::vector<int>& color, int& clock) {
  color[from] = 1;
  result.entry[from] = clock++;
  result.order.push_back(from);
  for (const auto& edge : graph.neighbors(from)) {
    if (color[edge.to] != 0) {
      continue;
    }
    result.parent[edge.to] = from;
    result.distance[edge.to] = result.distance[from] + 1;
    dfsRecursiveVisit(graph, edge.to, result, color, clock);
  }
  color[from] = 2;
  result.exit[from] = clock++;
}

inline TraversalResult dfsRecursive(const Graph& graph, int source) {
  Graph::requireVertex(source, graph.vertexCount());
  const int n = graph.vertexCount();
  TraversalResult result;
  result.parent.assign(n, -1);
  result.distance.assign(n, GRAPH_INF);
  result.entry.assign(n, -1);
  result.exit.assign(n, -1);
  std::vector<int> color(n, 0);
  int clock = 0;
  result.distance[source] = 0;
  dfsRecursiveVisit(graph, source, result, color, clock);
  return result;
}

inline TraversalResult dfsIterative(const Graph& graph, int source) {
  Graph::requireVertex(source, graph.vertexCount());
  const int n = graph.vertexCount();
  TraversalResult result;
  result.parent.assign(n, -1);
  result.distance.assign(n, GRAPH_INF);
  result.entry.assign(n, -1);
  result.exit.assign(n, -1);
  std::vector<bool> visited(n, false);
  std::stack<int> pending;
  pending.push(source);
  result.distance[source] = 0;

  while (!pending.empty()) {
    const int from = pending.top();
    pending.pop();
    if (visited[from]) {
      continue;
    }
    visited[from] = true;
    result.order.push_back(from);
    auto next = graph.neighbors(from);
    std::reverse(next.begin(), next.end());
    for (const auto& edge : next) {
      if (visited[edge.to]) {
        continue;
      }
      if (result.parent[edge.to] == -1 && edge.to != source) {
        result.parent[edge.to] = from;
        result.distance[edge.to] = result.distance[from] + 1;
      }
      pending.push(edge.to);
    }
  }
  return result;
}

inline std::vector<int> topologicalSort(const Graph& graph) {
  if (!graph.isDirected()) {
    throw std::invalid_argument("El orden topologico requiere grafo dirigido");
  }
  const int n = graph.vertexCount();
  std::vector<int> color(n, 0);
  std::vector<int> order;
  bool hasCycle = false;

  std::function<void(int)> visit = [&](int from) {
    color[from] = 1;
    for (const auto& edge : graph.neighbors(from)) {
      if (color[edge.to] == 0) {
        visit(edge.to);
      } else if (color[edge.to] == 1) {
        hasCycle = true;
      }
    }
    color[from] = 2;
    order.push_back(from);
  };

  for (int vertex = 0; vertex < n; ++vertex) {
    if (color[vertex] == 0) {
      visit(vertex);
    }
  }
  if (hasCycle) {
    throw std::logic_error("El grafo contiene un ciclo");
  }
  std::reverse(order.begin(), order.end());
  return order;
}

inline std::vector<std::vector<int>> connectedComponents(const Graph& graph) {
  const int n = graph.vertexCount();
  std::vector<bool> visited(n, false);
  std::vector<std::vector<int>> components;

  for (int start = 0; start < n; ++start) {
    if (visited[start]) {
      continue;
    }
    std::vector<int> component;
    std::queue<int> pending;
    pending.push(start);
    visited[start] = true;
    while (!pending.empty()) {
      const int from = pending.front();
      pending.pop();
      component.push_back(from);
      for (const auto& edge : graph.neighbors(from)) {
        if (!visited[edge.to]) {
          visited[edge.to] = true;
          pending.push(edge.to);
        }
      }
    }
    components.push_back(component);
  }
  return components;
}

inline void bccVisit(const Graph& graph, int from, int root, std::vector<int>& disc,
                     std::vector<int>& low, std::vector<int>& parent, int& time,
                     std::vector<Edge>& stack, std::set<int>& articulation,
                     BiconnectedResult& result) {
  disc[from] = low[from] = ++time;
  int children = 0;

  for (const auto& neighbor : graph.neighbors(from)) {
    const int to = neighbor.to;
    if (disc[to] == 0) {
      ++children;
      parent[to] = from;
      stack.push_back({from, to, neighbor.weight});
      bccVisit(graph, to, root, disc, low, parent, time, stack, articulation, result);
      low[from] = std::min(low[from], low[to]);

      const bool isRootCut = (from == root && children > 1);
      const bool isInternalCut = (from != root && low[to] >= disc[from]);
      if (isRootCut || isInternalCut) {
        articulation.insert(from);
        std::vector<Edge> component;
        while (!stack.empty()) {
          Edge edge = stack.back();
          stack.pop_back();
          component.push_back(edge);
          if (edge.from == from && edge.to == to) {
            break;
          }
        }
        result.components.push_back(component);
      }
    } else if (to != parent[from] && disc[to] < disc[from]) {
      low[from] = std::min(low[from], disc[to]);
      stack.push_back({from, to, neighbor.weight});
    }
  }
}

inline BiconnectedResult biconnectedComponents(const Graph& graph) {
  if (graph.isDirected()) {
    throw std::invalid_argument("Componentes biconexas requieren grafo no dirigido");
  }
  const int n = graph.vertexCount();
  std::vector<int> disc(n, 0);
  std::vector<int> low(n, 0);
  std::vector<int> parent(n, -1);
  std::vector<Edge> stack;
  std::set<int> articulation;
  BiconnectedResult result;
  int time = 0;

  for (int vertex = 0; vertex < n; ++vertex) {
    if (disc[vertex] != 0) {
      continue;
    }
    bccVisit(graph, vertex, vertex, disc, low, parent, time, stack, articulation, result);
    if (!stack.empty()) {
      result.components.push_back(stack);
      stack.clear();
    }
  }
  result.articulationPoints.assign(articulation.begin(), articulation.end());
  return result;
}

template <typename PriorityUpdater>
PrioritySearchResult priorityFirstSearch(const Graph& graph, int source,
                                         PriorityUpdater updater) {
  Graph::requireVertex(source, graph.vertexCount());
  const int n = graph.vertexCount();
  PrioritySearchResult result;
  result.priority.assign(n, GRAPH_INF);
  result.parent.assign(n, -1);
  result.finalized.assign(n, false);
  result.priority[source] = 0;

  for (int step = 0; step < n; ++step) {
    int best = -1;
    for (int vertex = 0; vertex < n; ++vertex) {
      if (!result.finalized[vertex] &&
          (best == -1 || result.priority[vertex] < result.priority[best])) {
        best = vertex;
      }
    }
    if (best == -1 || result.priority[best] >= GRAPH_INF / 2) {
      break;
    }
    result.finalized[best] = true;
    result.order.push_back(best);
    for (const auto& edge : graph.neighbors(best)) {
      if (!result.finalized[edge.to]) {
        updater(graph, best, edge.to, result.priority, result.parent);
      }
    }
  }
  return result;
}

inline MstResult primMst(const Graph& graph, int source = 0) {
  if (graph.isDirected()) {
    throw std::invalid_argument("Prim requiere grafo no dirigido");
  }
  auto search = priorityFirstSearch(graph, source, PrimPriorityUpdater{});
  MstResult result;
  for (int vertex = 0; vertex < graph.vertexCount(); ++vertex) {
    if (search.parent[vertex] == -1) {
      continue;
    }
    const int w = graph.weight(search.parent[vertex], vertex);
    result.edges.push_back({search.parent[vertex], vertex, w});
    result.totalWeight += w;
  }
  return result;
}

inline ShortestPathResult dijkstra(const Graph& graph, int source) {
  auto search = priorityFirstSearch(graph, source, DijkstraPriorityUpdater{});
  return {search.priority, search.parent};
}

inline MstResult kruskalMst(const Graph& graph) {
  if (graph.isDirected()) {
    throw std::invalid_argument("Kruskal requiere grafo no dirigido");
  }
  std::vector<Edge> sorted = graph.edges();
  std::sort(sorted.begin(), sorted.end(), [](const Edge& a, const Edge& b) {
    if (a.weight != b.weight) {
      return a.weight < b.weight;
    }
    if (a.from != b.from) {
      return a.from < b.from;
    }
    return a.to < b.to;
  });
  DisjointSet ds(graph.vertexCount());
  MstResult result;
  for (const auto& edge : sorted) {
    if (ds.unite(edge.from, edge.to)) {
      result.edges.push_back(edge);
      result.totalWeight += edge.weight;
    }
  }
  return result;
}

inline std::vector<std::vector<bool>> transitiveClosure(const Graph& graph) {
  const int n = graph.vertexCount();
  std::vector<std::vector<bool>> reachable(n, std::vector<bool>(n, false));
  for (int from = 0; from < n; ++from) {
    reachable[from][from] = true;
    for (const auto& edge : graph.neighbors(from)) {
      reachable[from][edge.to] = true;
    }
  }
  for (int mid = 0; mid < n; ++mid) {
    for (int from = 0; from < n; ++from) {
      if (!reachable[from][mid]) {
        continue;
      }
      for (int to = 0; to < n; ++to) {
        reachable[from][to] = reachable[from][to] || reachable[mid][to];
      }
    }
  }
  return reachable;
}

}  // namespace cc232
