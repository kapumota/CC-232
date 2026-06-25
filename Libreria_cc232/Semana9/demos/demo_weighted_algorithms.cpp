#include "CapituloGrafos.h"

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
  std::cout << "Peso MST por Prim: " << prim.totalWeight << '\n';

  const auto kruskal = kruskalMst(graph);
  std::cout << "Peso MST por Kruskal: " << kruskal.totalWeight << '\n';

  const auto shortest = dijkstra(graph, 0);
  std::cout << "Distancias desde 0: ";
  for (int value : shortest.distance) {
    std::cout << formatDistance(value) << ' ';
  }
  std::cout << '\n';

  return 0;
}
