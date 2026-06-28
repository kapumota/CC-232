### Lectura06: STL, iteradores y complejidad

#### Propósito

Esta lectura organiza el uso básico de la Standard Template Library en CC232.

La meta no es memorizar todos los contenedores, sino elegir una estructura adecuada según operaciones, costo esperado, invalidación de iteradores y claridad del código.

#### Resultado esperado

Al terminar esta lectura, el estudiante debe poder:

1. Elegir entre `std::vector`, `std::deque` y `std::list`.
2. Usar `std::stack`, `std::queue` y `std::priority_queue` como adaptadores.
3. Aplicar `std::sort`, `std::lower_bound`, `std::nth_element` y `std::partial_sort`.
4. Explicar cuándo se invalidan iteradores y referencias.
5. Relacionar una operación con su complejidad esperada.
6. Evitar errores comunes antes de implementar estructuras propias.

#### Por qué usar STL antes de implementar

La STL permite estudiar contratos, operaciones y complejidad antes de implementar estructuras desde cero.

En CC232 se usa con tres objetivos:

1. Comparar estructuras existentes con implementaciones propias.
2. Verificar resultados durante pruebas.
3. Razonar sobre costos de forma concreta.

#### `std::vector`

`std::vector` almacena elementos contiguos en memoria.

Ventajas principales:

1. Acceso por índice en tiempo constante.
2. Buena localidad de memoria.
3. Inserción eficiente al final en promedio.
4. Compatible con algoritmos que requieren iteradores de acceso aleatorio.

Costos típicos:

| Operación | Costo esperado |
|---|---|
| Acceso por índice | O(1) |
| Inserción al final | O(1) amortizado |
| Inserción al inicio | O(n) |
| Búsqueda lineal | O(n) |
| Ordenamiento con `std::sort` | O(n log n) |

#### Crecimiento de capacidad

Un vector tiene tamaño y capacidad.

El tamaño indica cuántos elementos contiene. La capacidad indica cuántos puede almacenar antes de reservar nueva memoria.

Cuando el vector necesita crecer, puede reubicar todos sus elementos. Esa reubicación puede invalidar iteradores, punteros y referencias.

#### `std::deque`

`std::deque` permite inserciones eficientes al inicio y al final.

Es útil cuando se necesita una cola doble, pero no necesariamente memoria contigua.

Costos típicos:

| Operación | Costo esperado |
|---|---|
| Acceso por índice | O(1) |
| Inserción al inicio | O(1) |
| Inserción al final | O(1) |
| Inserción en el medio | O(n) |

#### `std::list`

`std::list` es una lista doblemente enlazada.

Tiene inserciones y eliminaciones eficientes si ya se tiene el iterador correcto, pero pierde localidad de memoria y acceso por índice.

Costos típicos:

| Operación | Costo esperado |
|---|---|
| Avanzar al siguiente nodo | O(1) |
| Inserción con iterador conocido | O(1) |
| Eliminación con iterador conocido | O(1) |
| Acceso por posición | O(n) |
| Búsqueda lineal | O(n) |

#### Adaptadores de contenedores

Los adaptadores restringen la interfaz para representar una disciplina de acceso.

| Adaptador | Disciplina | Operaciones principales |
|---|---|---|
| `std::stack` | último en entrar, primero en salir | `push`, `pop`, `top` |
| `std::queue` | primero en entrar, primero en salir | `push`, `pop`, `front` |
| `std::priority_queue` | mayor prioridad primero | `push`, `pop`, `top` |

Estos adaptadores son importantes porque conectan directamente con pilas, colas, heaps, BFS, DFS, Dijkstra y simulaciones.

#### `std::sort`

`std::sort` ordena un rango con iteradores de acceso aleatorio.

Ejemplo conceptual:

```cpp
std::sort(values.begin(), values.end());
```

Su costo esperado es O(n log n).

#### `std::lower_bound`

`std::lower_bound` busca la primera posición donde un valor puede insertarse sin romper el orden.

Requisito: el rango debe estar ordenado.

Costo:

1. O(log n) comparaciones.
2. O(log n) pasos en contenedores de acceso aleatorio.
3. Puede ser más costoso en contenedores sin acceso aleatorio.

#### `std::nth_element`

`std::nth_element` coloca el elemento que quedaría en la posición `n` si el arreglo estuviera ordenado.

No ordena todo el rango. Es útil para encontrar medianas, percentiles y cortes.

Costo esperado: O(n).

#### `std::partial_sort`

`std::partial_sort` ordena solo una parte inicial del rango.

Es útil para obtener los `k` menores o los `k` mayores sin ordenar todo el arreglo.

Costo esperado: O(n log k).

#### Invalidación de iteradores

Un iterador se invalida cuando deja de apuntar de forma segura a un elemento válido.

Ejemplo típico en `std::vector`:

1. Se guarda un iterador.
2. El vector crece.
3. El vector reserva nueva memoria.
4. El iterador anterior deja de ser válido.

Regla práctica:

1. Si una operación puede reubicar memoria, no reutilices iteradores antiguos.
2. Si necesitas conservar una posición lógica, guarda un índice.
3. Después de modificar el contenedor, vuelve a obtener el iterador.

#### Tabla de referencia rápida

| Estructura o algoritmo | Uso principal | Costo clave |
|---|---|---|
| `std::vector` | arreglo dinámico | acceso O(1) |
| `std::deque` | inserción en extremos | inicio y final O(1) |
| `std::list` | nodos enlazados | inserción con iterador O(1) |
| `std::stack` | pila | `push` y `pop` O(1) |
| `std::queue` | cola | `push` y `pop` O(1) |
| `std::priority_queue` | heap | `push` y `pop` O(log n) |
| `std::sort` | ordenamiento completo | O(n log n) |
| `std::lower_bound` | búsqueda binaria | O(log n) |
| `std::nth_element` | selección | O(n) esperado |
| `std::partial_sort` | top parcial | O(n log k) |

#### Errores comunes

| Error | Consecuencia |
|---|---|
| Usar `std::list` esperando acceso rápido por índice | costo O(n) |
| Usar `lower_bound` en datos no ordenados | resultado incorrecto |
| Guardar iteradores de vector y luego hacer `push_back` | posible invalidación |
| Ordenar todo para obtener solo el elemento mediano | costo mayor al necesario |
| Medir rendimiento sin validar correctitud | conclusiones inválidas |

#### Relación con el resto del curso

Estos temas aparecen en:

1. Pilas y colas.
2. Heaps y colas de prioridad.
3. Ordenamiento y selección.
4. Tablas hash.
5. Grafos.
6. Estructuras de rango.
7. Proyecto integrador y benchmarking.

#### Ejercicios de lectura

1. Explica por qué `std::vector` tiene buena localidad de memoria.
2. Indica cuándo preferirías `std::deque` sobre `std::vector`.
3. Explica por qué `std::list` no debe usarse para acceso por índice.
4. Usa `std::lower_bound` sobre un vector ordenado y explica el resultado.
5. Compara `std::sort`, `std::nth_element` y `std::partial_sort`.
6. Explica un caso de invalidación de iteradores en `std::vector`.
