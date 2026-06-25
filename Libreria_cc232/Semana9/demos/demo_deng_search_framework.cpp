#include "CapituloGrafos.h"

#include <iostream>

using namespace cc232;

int main() {
  AdjacencyListGraph dag(6, true);
  dag.addEdge(5, 2);
  dag.addEdge(5, 0);
  dag.addEdge(4, 0);
  dag.addEdge(4, 1);
  dag.addEdge(2, 3);
  dag.addEdge(3, 1);

  const auto order = topologicalSort(dag);
  std::cout << "Orden topologico: ";
  for (int vertex : order) {
    std::cout << vertex << ' ';
  }
  std::cout << '\n';

  AdjacencyListGraph undirected(7, false);
  undirected.addEdge(0, 1);
  undirected.addEdge(1, 2);
  undirected.addEdge(2, 0);
  undirected.addEdge(1, 3);
  undirected.addEdge(3, 4);
  undirected.addEdge(4, 5);
  undirected.addEdge(5, 3);
  undirected.addEdge(5, 6);

  const auto bcc = biconnectedComponents(undirected);
  std::cout << "Componentes biconexas: " << bcc.components.size() << '\n';
  std::cout << "Puntos de articulacion: ";
  for (int vertex : bcc.articulationPoints) {
    std::cout << vertex << ' ';
  }
  std::cout << '\n';

  return 0;
}
