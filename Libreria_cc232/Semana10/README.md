### Semana 10: Ordenamiento, selección y cotas inferiores

#### Propósito

Esta semana continúa la línea de la librería `CC232` después de grafos. El objetivo es estudiar algoritmos de ordenamiento desde tres perspectivas complementarias:

1. Implementación en C++17.
2. Análisis de complejidad y estabilidad.
3. Límite inferior para ordenamiento basado en comparaciones.

La semana usa como base conceptual el capítulo 11 de Morin sobre algoritmos de ordenamiento y como base de implementación la tradición de Deng sobre ordenamiento en vectores y listas.

#### Contenido incluido

| Bloque | Archivos principales | Tema |
|---|---|---|
| Estadísticas | `include/SortingStats.h` | Conteo de comparaciones, movimientos, swaps, particiones y profundidad |
| Utilidades | `include/SortingUtils.h` | Verificación de orden, multiconjunto, estabilidad |
| Ordenamiento por comparación | `include/ComparisonSorts.h` | Bubble, selection, insertion, merge, quick, quick iterativo, heap, shell, intro |
| Ordenamiento lineal | `include/LinearSorts.h` | Counting sort, counting sort estable, radix sort LSD, radix con enteros con signo |
| Selección | `include/SelectionAlgorithms.h` | QuickSelect y `smallestK` |
| Lower bound | `include/LowerBound.h` | `log2(n!)`, aproximación de Stirling y árbol de decisión |
| Agregador | `include/CapituloOrdenamiento.h` | Inclusión unificada de la semana |

#### Relación con Morin

Morin presenta en el capítulo 11:

- MergeSort.
- QuickSort.
- HeapSort.
- Cota inferior para sorting basado en comparaciones.
- Counting sort.
- Radix sort.

Esta semana toma esa línea y la convierte en una librería educativa instrumentada.

#### Relación con Deng

Deng trabaja varias variantes sobre vectores y listas:

- Bubble sort.
- Selection sort.
- Insertion sort.
- Merge sort.
- Quick sort recursivo e iterativo.
- Heap sort.
- Shell sort.
- Radix sort.
- QuickSelect.

Esta semana conserva esas variantes, pero las reescribe en una interfaz homogénea para `CC232`.

#### Temas adicionales agregados

Además de Morin y Deng se agregan:

- Instrumentación de comparaciones y movimientos.
- Estabilidad de algoritmos.
- Conteo de inversiones con merge sort.
- IntroSort didáctico.
- Radix sort para enteros con signo.
- Pruebas de lower bound mediante `ceil(log2(n!))`.

#### Compilación aislada

Desde la raíz del repositorio:

```bash
cmake -S Libreria_cc232/Semana10 -B build_semana10
cmake --build build_semana10
ctest --test-dir build_semana10 --output-on-failure
```

#### Integración con la librería

Agregar en `Libreria_cc232/CMakeLists.txt`:

```cmake
add_subdirectory(Semana10)
```

Después ejecutar:

```bash
cmake -S Libreria_cc232 -B build_libreria
cmake --build build_libreria
ctest --test-dir build_libreria --output-on-failure
```

#### Demos

Los demos generados son:

```txt
sem10_demo_comparison_sorts
sem10_demo_lower_bound
sem10_demo_linear_sorts
sem10_demo_selection_and_intro
```

#### Pruebas

Las pruebas registradas son:

```txt
semana10_public
semana10_internal
semana10_stability_and_stats
semana10_lower_bound
semana10_linear_sorts
semana10_selection_intro
```
