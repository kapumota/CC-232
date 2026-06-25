### Lectura17: Morin, Deng y ordenamiento

#### Propósito

Esta lectura ubica los algoritmos de ordenamiento dentro de la línea de estructuras de datos. No se estudian solo como rutinas de programación, sino como casos donde se conectan modelos de cómputo, invariantes, árboles, heaps, divide and conquer y límites inferiores.

#### Morin

Morin presenta el ordenamiento en el capítulo 11. La motivación es que QuickSort se relaciona con árboles binarios aleatorizados y HeapSort se relaciona con heaps. Además, muestra que MergeSort, QuickSort y HeapSort son algoritmos basados en comparaciones y que la barrera `Omega(n log n)` aparece cuando el algoritmo solo puede comparar elementos.

#### Deng

Deng presenta variantes de ordenamiento sobre estructuras lineales, especialmente vectores y listas. Su enfoque es útil para implementar y comparar:

- Bubble sort.
- Selection sort.
- Insertion sort.
- Merge sort.
- Quick sort.
- Heap sort.
- Shell sort.
- Radix sort.
- QuickSelect.

#### Lectura técnica

La lectura debe enfocarse en estas preguntas:

1. ¿Qué operación primitiva usa cada algoritmo?
2. ¿El algoritmo mueve elementos o intercambia referencias?
3. ¿El algoritmo conserva estabilidad?
4. ¿El algoritmo usa memoria auxiliar?
5. ¿Su peor caso coincide con su caso promedio?
6. ¿El algoritmo pertenece al modelo de comparación?

#### Clasificación sugerida

| Algoritmo | Modelo | Tiempo esperado | Peor caso | Estable | Memoria auxiliar |
|---|---|---:|---:|---|---:|
| Bubble sort | Comparación | `O(n^2)` | `O(n^2)` | Sí | `O(1)` |
| Selection sort | Comparación | `O(n^2)` | `O(n^2)` | No | `O(1)` |
| Insertion sort | Comparación | `O(n^2)` | `O(n^2)` | Sí | `O(1)` |
| MergeSort | Comparación | `O(n log n)` | `O(n log n)` | Sí | `O(n)` |
| QuickSort | Comparación | `O(n log n)` | `O(n^2)` | No | `O(log n)` esperado |
| HeapSort | Comparación | `O(n log n)` | `O(n log n)` | No | `O(1)` |
| ShellSort | Comparación | depende de gaps | depende de gaps | No | `O(1)` |
| IntroSort | Comparación | `O(n log n)` | `O(n log n)` | No | `O(log n)` |
| Counting sort | Indexación | `O(n + k)` | `O(n + k)` | Puede ser estable | `O(n + k)` |
| Radix sort | Dígitos | `O(d(n + b))` | `O(d(n + b))` | Sí si la pasada es estable | `O(n + b)` |

#### Cierre

El estudiante debe entender que no existe un único mejor algoritmo. La elección depende del modelo, del patrón de entrada, de la estabilidad requerida, del rango de claves y de la memoria disponible.
