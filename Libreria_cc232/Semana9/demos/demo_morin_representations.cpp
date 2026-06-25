#include "CapituloGrafos.h"

#include <iostream>

using namespace cc232;

void printOrder(const TraversalResult& result) {
  for (int vertex : result.order) {
    std::cout << vertex << ' ';
  }
  std::cout << '\n';
}

int main() {
  AdjacencyMatrixGraph matrixGraph(6, false);
  AdjacencyListGraph listGraph(6, false);

  const std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 1}, {1, 3, 1},
                                  {2, 3, 1}, {3, 4, 1}, {4, 5, 1}};

  for (const auto& edge : edges) {
    matrixGraph.addEdge(edge.from, edge.to, edge.weight);
    listGraph.addEdge(edge.from, edge.to, edge.weight);
  }

  std::cout << "BFS con matriz de adyacencia: ";
  printOrder(bfs(matrixGraph, 0));

  std::cout << "BFS con listas de adyacencia: ";
  printOrder(bfs(listGraph, 0));

  std::cout << "DFS recursivo con listas: ";
  printOrder(dfsRecursive(listGraph, 0));

  return 0;
}
