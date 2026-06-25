### Semana 9 - Grafos, recorridos y algoritmos clásicos

Esta carpeta continúa el trabajo de `Semana8` dentro de `Libreria_cc232`. El objetivo principal es estudiar grafos desde dos líneas complementarias: la línea de Morin, centrada en representaciones simples y recorridos, y la línea de Deng, centrada en el ADT de grafo, el marco de búsqueda DFS y el marco de búsqueda por prioridad.

La semana separa con claridad seis ideas que suelen confundirse:

  * un grafo es una relación entre vértices mediante aristas,
  * una interfaz de grafo define operaciones abstractas,
  * una representación decide cómo guardar vértices y aristas,
  * un recorrido define cómo explorar los vértices,
  * un algoritmo sobre grafos agrega invariantes sobre el recorrido,
  * una variante de representación cambia costos, memoria y dificultad de implementación.

#### Relación con la semana anterior

`Semana8` estudia diccionarios no ordenados, hashing, colisiones y acceso esperado constante. `Semana9` cambia el foco desde claves aisladas hacia relaciones entre objetos. Esta transición es natural: muchas aplicaciones reales no solo preguntan si una clave existe, sino cómo se conecta con otras claves.

La relación conceptual puede leerse así:

    Semana5
    └── árboles, BST y búsqueda ordenada

    Semana6
    └── heaps, colas de prioridad y Huffman

    Semana7
    └── AVL, Red-Black Tree y balanceo

    Semana8
    └── hashing, diccionarios y acceso por clave

    Semana9
    └── grafos, recorridos, conectividad, prioridad y caminos mínimos

#### Contenido principal

La carpeta incluye los siguientes componentes:

  * `GraphTypes.h`: tipos comunes para vecinos, aristas, recorridos, caminos mínimos, MST y componentes biconexas.
  * `Graph.h`: interfaz abstracta del ADT de grafo.
  * `AdjacencyMatrixGraph.h`: grafo basado en matriz de adyacencia.
  * `AdjacencyListGraph.h`: grafo basado en listas de adyacencia.
  * `EdgeListGraph.h`: variante basada en lista global de aristas.
  * `GraphAlgorithms.h`: BFS, DFS, orden topológico, componentes conexas, componentes biconexas, búsqueda por prioridad, Prim, Dijkstra, Kruskal y clausura transitiva.
  * `PriorityUpdaters.h`: actualizadores de prioridad para Prim y Dijkstra.
  * `DisjointSet.h`: estructura auxiliar para Kruskal.
  * `GridGraph.h`: constructor de grafos tipo grilla para experimentos pequeños.
  * `CapituloGrafos.h`: header agregador de la semana.

#### Correspondencia con Morin

La línea de Morin se representa mediante:

  * matriz de adyacencia,
  * listas de adyacencia,
  * BFS,
  * DFS recursivo,
  * DFS iterativo.

Estos elementos aparecen en la carpeta mediante `AdjacencyMatrixGraph.h`, `AdjacencyListGraph.h` y `GraphAlgorithms.h`.

#### Correspondencia con Deng

La línea de Deng se representa mediante:

  * interfaz del ADT de grafo,
  * estructura de grafo basada en matriz de adyacencia,
  * algoritmo BFS,
  * algoritmo DFS,
  * ordenamiento topológico basado en DFS,
  * componentes biconexas basadas en DFS,
  * marco de búsqueda por prioridad,
  * actualizador de prioridad para Prim,
  * actualizador de prioridad para Dijkstra.

La correspondencia interna es la siguiente:

| Codigo | Tema | Archivo |
|---|---|---|
| Codigo 6.1 | Interfaz de operaciones del ADT de grafo | `include/Graph.h` |
| Codigo 6.2 | Grafo basado en matriz de adyacencia | `include/AdjacencyMatrixGraph.h` |
| Codigo 6.3 | BFS | `include/GraphAlgorithms.h` |
| Codigo 6.4 | DFS | `include/GraphAlgorithms.h` |
| Codigo 6.5 | Orden topologico | `include/GraphAlgorithms.h` |
| Codigo 6.6 | Componentes biconexas | `include/GraphAlgorithms.h` |
| Codigo 6.7 | Busqueda por prioridad | `include/GraphAlgorithms.h` |
| Codigo 6.8 | Actualizador de Prim | `include/PriorityUpdaters.h` |
| Codigo 6.9 | Actualizador de Dijkstra | `include/PriorityUpdaters.h` |

#### Variantes agregadas

Además del núcleo de Morin y Deng, la semana incluye variantes adicionales para elevar el nivel:

  * `AdjacencyListGraph`: representación eficiente para grafos dispersos.
  * `EdgeListGraph`: representación útil para algoritmos por aristas.
  * `Kruskal`: MST con `DisjointSet`.
  * `transitiveClosure`: clausura transitiva tipo Warshall.
  * `GridGraph`: generación de grafos de grilla para pruebas de recorrido.
  * `connectedComponents`: descomposición en componentes conexas.

Estas variantes permiten comparar representación, costo de memoria, costo de vecindad, costo de recorrido y facilidad para algoritmos ponderados.

#### Demos incluidos

Los demos principales son:

  * `demo_morin_representations.cpp`: compara matriz y listas con BFS y DFS.
  * `demo_deng_search_framework.cpp`: ejecuta orden topológico y componentes biconexas.
  * `demo_weighted_algorithms.cpp`: compara Prim, Kruskal y Dijkstra.
  * `demo_graph_variants.cpp`: usa lista de aristas, clausura transitiva y grafos de grilla.

#### Pruebas incluidas

La carpeta contiene pruebas públicas e internas:

  * `test_public_week9.cpp`: BFS, DFS, orden topológico y Dijkstra.
  * `test_internal_week9.cpp`: consistencia entre matriz y listas, detección de ciclos y componentes conexas.
  * `test_weighted_algorithms.cpp`: Prim, Kruskal y Dijkstra.
  * `test_biconnected_components.cpp`: componentes biconexas y puntos de articulación.
  * `test_graph_variants.cpp`: clausura transitiva y grillas.

#### Compilación desde la raíz de la librería

Para compilar siguiendo la forma de trabajo de la librería completa:

    cd Libreria_cc232
    cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
    cmake --build build-debug --target sem9_test_public
    ./build-debug/Semana9/sem9_test_public

Si `Semana9` todavía no está integrada al `CMakeLists.txt` principal de `Libreria_cc232`, agrega esta línea:

    add_subdirectory(Semana9)

#### Compilación directa de la semana

También se puede compilar únicamente esta carpeta:

    cd Libreria_cc232/Semana9
    cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
    cmake --build build-debug
    ctest --test-dir build-debug --output-on-failure

#### Nota de diseño

La implementación mantiene estilo header-only para facilitar lectura, pruebas y comparación. Las firmas de función usan inglés por convención de código, mientras que los mensajes y comentarios están en español para sostener la explicación docente.
