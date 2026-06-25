#include "CapituloGrafos.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace cc232;

void testMatrixAndListConsistency() {
  AdjacencyMatrixGraph matrixGraph(4, false);
  AdjacencyListGraph listGraph(4, false);
  for (const auto& edge : std::vector<Edge>{{0, 1, 4}, {1, 2, 7}, {2, 3, 1}}) {
    matrixGraph.addEdge(edge.from, edge.to, edge.weight);
    listGraph.addEdge(edge.from, edge.to, edge.weight);
  }
  for (int from = 0; from < 4; ++from) {
    for (int to = 0; to < 4; ++to) {
      assert(matrixGraph.hasEdge(from, to) == listGraph.hasEdge(from, to));
      assert(matrixGraph.weight(from, to) == listGraph.weight(from, to));
    }
  }
}

void testCycleDetectionInTopologicalSort() {
  AdjacencyListGraph graph(3, true);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 0);

  bool detected = false;
  try {
    (void)topologicalSort(graph);
  } catch (const std::logic_error&) {
    detected = true;
  }
  assert(detected);
}

void testConnectedComponents() {
  AdjacencyListGraph graph(6, false);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(3, 4);
  const auto components = connectedComponents(graph);
  assert(components.size() == 3);
}

int main() {
  testMatrixAndListConsistency();
  testCycleDetectionInTopologicalSort();
  testConnectedComponents();
  std::cout << "Pruebas internas generales Semana9 completadas\n";
  return 0;
}
