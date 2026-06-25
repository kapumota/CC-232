#include "CapituloGrafos.h"

#include <cassert>
#include <iostream>

using namespace cc232;

int main() {
  EdgeListGraph graph(4, true);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 3);

  const auto closure = transitiveClosure(graph);
  assert(closure[0][3]);
  assert(!closure[3][0]);

  auto grid = buildGridGraph(2, 3, false);
  const auto result = bfs(grid, 0);
  assert(result.order.size() == 6);
  assert(result.distance[5] == 3);

  std::cout << "Pruebas de variantes Semana9 completadas\n";
  return 0;
}
