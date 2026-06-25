### Ejercicios9-CC232 - Grafos

#### Ejercicio 1 - Matriz contra listas

Considere un grafo con `n` vértices y `m` aristas.

Explique el costo de memoria de matriz de adyacencia y listas de adyacencia. Luego indique en qué casos conviene cada representación.

Debe incluir un ejemplo con un grafo denso y otro con un grafo disperso.

#### Ejercicio 2 - BFS manual

Ejecute manualmente BFS desde el vértice `0` en el siguiente grafo no dirigido:

    0: 1, 2
    1: 0, 3, 4
    2: 0, 5
    3: 1
    4: 1, 5
    5: 2, 4

Debe entregar:

  * contenido de la cola en cada paso,
  * arreglo de distancias,
  * arreglo de padres,
  * árbol BFS resultante.

#### Ejercicio 3 - DFS y tiempos

Sobre el mismo grafo del ejercicio anterior, ejecute DFS recursivo desde `0`.

Debe entregar:

  * orden de descubrimiento,
  * tiempos de entrada,
  * tiempos de salida,
  * aristas de árbol,
  * aristas que no pertenecen al árbol DFS.

#### Ejercicio 4 - Orden topológico

Dado el grafo dirigido:

    5: 2, 0
    4: 0, 1
    2: 3
    3: 1

Encuentre un orden topológico válido y demuestre que respeta todas las aristas.

Luego agregue la arista `1, 5` y explique por qué aparece un ciclo.

#### Ejercicio 5 - Componentes conexas

Construya un grafo no dirigido con nueve vértices y exactamente tres componentes conexas. Ejecute BFS o DFS para encontrar cada componente.

Debe mostrar el arreglo de visitados después de terminar cada componente.

#### Ejercicio 6 - Componentes biconexas

Construya un grafo con dos triángulos conectados por un camino simple.

Debe encontrar:

  * puntos de articulación,
  * componentes biconexas,
  * valores `disc` y `low`,
  * explicación de por qué cada punto de articulación separa el grafo.

#### Ejercicio 7 - Prim paso a paso

Ejecute Prim desde el vértice `0` sobre el grafo ponderado:

    0-1 peso 2
    0-3 peso 6
    1-2 peso 3
    1-3 peso 8
    1-4 peso 5
    2-4 peso 7
    3-4 peso 9

Debe entregar una tabla con:

  * iteración,
  * vértice seleccionado,
  * prioridades,
  * padres,
  * arista agregada.

#### Ejercicio 8 - Kruskal paso a paso

Use el mismo grafo del ejercicio 7. Ordene las aristas por peso y ejecute Kruskal.

Debe mostrar:

  * aristas ordenadas,
  * estado de los conjuntos disjuntos,
  * aristas aceptadas,
  * aristas rechazadas,
  * peso final del MST.

#### Ejercicio 9 - Dijkstra paso a paso

Ejecute Dijkstra desde `0` sobre el grafo dirigido:

    0 a 1 peso 5
    0 a 2 peso 2
    2 a 1 peso 1
    1 a 3 peso 2
    2 a 3 peso 9

Debe entregar:

  * distancias iniciales,
  * vértice finalizado en cada iteración,
  * relajaciones realizadas,
  * distancias finales,
  * caminos mínimos desde `0`.

#### Ejercicio 10 - Clausura transitiva

Construya la matriz de alcanzabilidad para el grafo dirigido:

    0 a 1
    1 a 2
    2 a 3
    3 a 1

Debe explicar qué vértices son alcanzables desde `0` y qué vértices son alcanzables desde `3`.

#### Ejercicio 11 - Diseño de variante

Proponga una variante de representación o algoritmo no incluida en el núcleo de la semana. Algunas opciones son:

  * grafo con pesos `double`,
  * grafo con etiquetas de vértices tipo `string`,
  * detección de ciclo no dirigido,
  * BFS multi fuente,
  * orden topológico con grados de entrada.

Debe explicar qué archivos modificaría y qué pruebas agregaría.

#### Ejercicio 12 - Comparación final

Compare estos pares:

  * matriz de adyacencia contra listas de adyacencia,
  * BFS contra DFS,
  * Prim contra Kruskal,
  * Dijkstra contra BFS,
  * orden topológico contra DFS simple.

La respuesta debe incluir complejidad, supuestos y un caso donde cada técnica sea más apropiada.
