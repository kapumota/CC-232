### Semana12: Fenwick Tree, Segment Tree, Sparse Table y consultas de rango

#### Propósito

Esta semana estudia estructuras de datos para responder consultas sobre rangos de una secuencia. El foco está en pasar de soluciones ingenuas a estructuras con garantías logarítmicas o constantes bajo supuestos específicos.

La semana complementa a Morin y Deng. Morin y Deng aportan la base de arreglos, árboles, análisis y diseño de ADT, pero Fenwick Tree, Segment Tree, lazy propagation y Sparse Table requieren material adicional moderno. Para esta unidad se usa como apoyo conceptual CP-Algorithms, USACO Guide, Algorithmica y problemas clásicos de consultas de rango.

#### Temas centrales

- Sumas de prefijo.
- Arreglo de diferencias.
- Fenwick Tree para suma y actualización puntual.
- Fenwick Tree con búsqueda por prefijo.
- Fenwick Tree para actualización de rango y consulta de rango.
- Fenwick Tree 2D básico.
- Segment Tree recursivo.
- Segment Tree iterativo.
- Segment Tree genérico con operación asociativa.
- Lazy propagation para suma de rango.
- Lazy propagation con asignación y suma.
- Range Minimum Query.
- Sparse Table para operaciones idempotentes.
- Sparse Table para mínimo, máximo y gcd.
- Segment Tree para máximo subarreglo.
- Comparación experimental entre estructuras.

#### Estructura

```txt
Semana12/
├── CMakeLists.txt
├── README.md
├── Resumen_Semana12.md
├── Actividad12-CC232.md
├── Ejercicios12-CC232.md
├── PATCH_ROOT_CMAKE.md
├── VALIDACION_LOCAL.txt
├── include/
├── demos/
├── lecturas/
├── pruebas_publicas/
├── pruebas_internas/
└── sustentacion/
```

#### Código principal

| Archivo | Contenido |
|---|---|
| `PrefixSums.h` | Sumas de prefijo 1D y 2D |
| `DifferenceArray.h` | Actualizaciones de rango offline |
| `FenwickTree.h` | BIT para suma, actualización y búsqueda por prefijo |
| `FenwickRange.h` | Dos BIT para actualización de rango y consulta de rango |
| `FenwickTree2D.h` | BIT 2D básico |
| `SegmentTree.h` | Segment Tree recursivo genérico |
| `IterativeSegmentTree.h` | Segment Tree iterativo |
| `LazySegmentTree.h` | Lazy propagation para suma |
| `AssignmentLazySegmentTree.h` | Lazy propagation con asignación y suma |
| `MonoidSegmentTree.h` | Segment Tree parametrizado por monoide |
| `MaxSubarraySegmentTree.h` | Segment Tree para máximo subarreglo |
| `SparseTable.h` | Sparse Table para operaciones idempotentes |
| `RangeQueryOracle.h` | Oráculo ingenuo para pruebas |
| `CapituloConsultasRango.h` | Header agregador |

#### Compilación aislada

```bash
cmake -S Libreria_cc232/Semana12 -B build_semana12
cmake --build build_semana12
ctest --test-dir build_semana12 --output-on-failure
```

#### Integración desde la raíz

Agregar en `Libreria_cc232/CMakeLists.txt`:

```cmake
add_subdirectory(Semana12)
```

Luego ejecutar:

```bash
cmake -S Libreria_cc232 -B build_libreria
cmake --build build_libreria
ctest --test-dir build_libreria --output-on-failure
```

#### Resultado esperado

El estudiante debe poder justificar qué estructura corresponde a cada combinación de operación:

| Operación | Estructura adecuada |
|---|---|
| Consultas estáticas de suma | Prefix sums |
| Actualizaciones offline de rango | Difference array |
| Point update y range sum | Fenwick Tree o Segment Tree |
| Range add y range sum | FenwickRange o LazySegmentTree |
| Range min estático | Sparse Table |
| Operación asociativa general | Segment Tree con monoide |
| Submatrices de suma | PrefixSums2D o FenwickTree2D |
