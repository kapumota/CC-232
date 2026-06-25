#include "CapituloGrafos.h"

#include <cassert>
#include <iostream>

using namespace cc232;

int main() {
  AdjacencyListGraph graph(5, false);
  graph.addEdge(0, 1, 2);
  graph.addEdge(0, 3, 6);
  graph.addEdge(1, 2, 3);
  graph.addEdge(1, 3, 8);
  graph.addEdge(1, 4, 5);
  graph.addEdge(2, 4, 7);
  graph.addEdge(3, 4, 9);

  const auto prim = primMst(graph, 0);
  const auto kruskal = kruskalMst(graph);
  assert(prim.totalWeight == 16);
  assert(kruskal.totalWeight == 16);
  assert(prim.edges.size() == 4);
  assert(kruskal.edges.size() == 4);

  const auto shortest = dijkstra(graph, 0);
  assert(shortest.distance[4] == 7);
  assert(shortest.distance[3] == 6);

  std::cout << "Pruebas ponderadas Semana9 completadas\n";
  return 0;
}
