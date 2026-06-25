#include "CapituloGrafos.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace cc232;

int main() {
  AdjacencyListGraph graph(7, false);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 0);
  graph.addEdge(1, 3);
  graph.addEdge(3, 4);
  graph.addEdge(4, 5);
  graph.addEdge(5, 3);
  graph.addEdge(5, 6);

  const auto result = biconnectedComponents(graph);
  assert(!result.components.empty());
  assert(std::find(result.articulationPoints.begin(), result.articulationPoints.end(), 1) !=
         result.articulationPoints.end());
  assert(std::find(result.articulationPoints.begin(), result.articulationPoints.end(), 3) !=
         result.articulationPoints.end());
  assert(std::find(result.articulationPoints.begin(), result.articulationPoints.end(), 5) !=
         result.articulationPoints.end());

  std::cout << "Pruebas de componentes biconexas Semana9 completadas\n";
  return 0;
}
