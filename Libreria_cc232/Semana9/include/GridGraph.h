#pragma once

#include "AdjacencyListGraph.h"

namespace cc232 {

inline int gridId(int row, int column, int columns) {
  return row * columns + column;
}

inline AdjacencyListGraph buildGridGraph(int rows, int columns, bool directed = false) {
  if (rows <= 0 || columns <= 0) {
    throw std::invalid_argument("La grilla debe tener dimensiones positivas");
  }
  AdjacencyListGraph graph(rows * columns, directed);
  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      const int current = gridId(row, column, columns);
      if (row + 1 < rows) {
        graph.addEdge(current, gridId(row + 1, column, columns));
      }
      if (column + 1 < columns) {
        graph.addEdge(current, gridId(row, column + 1, columns));
      }
    }
  }
  return graph;
}

}  // namespace cc232
