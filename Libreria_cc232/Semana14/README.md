### Semana14: Proyecto integrador, benchmarking y selección de estructuras

#### Propósito

Esta semana cierra la librería CC232 con un proyecto integrador. El objetivo ya no es implementar una estructura aislada, sino seleccionar estructuras de datos según una carga de trabajo, justificar la decisión con análisis y respaldarla con mediciones reproducibles.

#### Resultado esperado

Al terminar la semana, el estudiante debe poder responder con evidencia:

- qué estructura conviene para búsqueda exacta;
- qué estructura conviene para consultas por prefijo;
- qué estructura conviene para consultas de rango;
- qué estructura conviene para range scan en memoria externa;
- qué algoritmo conviene para ordenar según el patrón de datos;
- qué representación de grafo conviene según densidad y operaciones.

#### Componentes

- `WorkloadProfile`: descripción de carga de trabajo.
- `DataStructureAdvisor`: recomendador de estructuras.
- `BenchmarkStats`: resumen de mediciones.
- `BenchmarkReport`: reporte experimental en Markdown.
- `DictionaryBenchmark`: comparación básica de diccionarios.
- `RangeQueryBenchmark`: comparación de consultas de rango.
- `SortingBenchmark`: comparación de ordenamientos.
- `GraphBenchmark`: medición básica de BFS.
- `TextIndexBenchmark`: medición básica de búsqueda textual.

#### Validación

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

#### Alcance

La semana está diseñada para compilar de forma aislada. En el curso completo puede extenderse para invocar directamente implementaciones de semanas anteriores, como hash tables, tries, segment trees, B-Trees y grafos.
