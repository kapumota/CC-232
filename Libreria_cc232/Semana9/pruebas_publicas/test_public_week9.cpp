#include "CapituloGrafos.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace cc232;

void testBfsAndDfs() {
  AdjacencyListGraph graph(5, false);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 4);

  const auto bfsResult = bfs(graph, 0);
  assert((bfsResult.order == std::vector<int>{0, 1, 2, 3, 4}));
  assert(bfsResult.distance[4] == 2);
  assert(bfsResult.parent[3] == 1);

  const auto dfsResult = dfsRecursive(graph, 0);
  assert(dfsResult.order.front() == 0);
  assert(dfsResult.parent[1] == 0);
}

void testTopologicalSort() {
  AdjacencyListGraph dag(4, true);
  dag.addEdge(0, 1);
  dag.addEdge(0, 2);
  dag.addEdge(1, 3);
  dag.addEdge(2, 3);

  const auto order = topologicalSort(dag);
  std::vector<int> position(4);
  for (int i = 0; i < static_cast<int>(order.size()); ++i) {
    position[order[i]] = i;
  }
  assert(position[0] < position[1]);
  assert(position[0] < position[2]);
  assert(position[1] < position[3]);
  assert(position[2] < position[3]);
}

void testDijkstra() {
  AdjacencyListGraph graph(4, true);
  graph.addEdge(0, 1, 5);
  graph.addEdge(0, 2, 2);
  graph.addEdge(2, 1, 1);
  graph.addEdge(1, 3, 2);
  graph.addEdge(2, 3, 9);

  const auto result = dijkstra(graph, 0);
  assert(result.distance[0] == 0);
  assert(result.distance[1] == 3);
  assert(result.distance[3] == 5);
  assert(result.parent[3] == 1);
}

int main() {
  testBfsAndDfs();
  testTopologicalSort();
  testDijkstra();
  std::cout << "Pruebas publicas Semana9 completadas\n";
  return 0;
}
