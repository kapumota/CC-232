#include "CapituloGrafos.h"

#include <iostream>

using namespace cc232;

int main() {
  EdgeListGraph edgeList(4, true);
  edgeList.addEdge(0, 1);
  edgeList.addEdge(1, 2);
  edgeList.addEdge(2, 3);

  const auto closure = transitiveClosure(edgeList);
  std::cout << "Alcanzable 0 a 3: " << (closure[0][3] ? "si" : "no") << '\n';

  auto grid = buildGridGraph(2, 3, false);
  const auto traversal = bfs(grid, 0);
  std::cout << "BFS en grilla 2x3: ";
  for (int vertex : traversal.order) {
    std::cout << vertex << ' ';
  }
  std::cout << '\n';

  return 0;
}
