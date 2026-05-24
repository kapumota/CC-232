### Ejercicios 6 - CC232

##### Ejercicio 14.1 - `replaceTop` en `PQ_ComplHeap`

Agrega a `PQ_ComplHeap` una operación:

```cpp
template<class T>
T replaceTop(const T& newValue);
```

La operación debe:

1. lanzar excepción si el heap está vacío,
2. guardar el máximo actual,
3. colocar `newValue` en la raíz,
4. reparar con `percolateDown`,
5. retornar el máximo anterior.

No debes implementar esta operación como `delMax()` seguido de `insert()`. La idea es modificar directamente la raíz.

Prueba con:

```cpp
{90, 70, 80, 10, 30, 20, 60}
replaceTop(50)
replaceTop(100)
replaceTop(5)
```

Entrega:

- código de `replaceTop`,
- demostración breve,
- prueba de propiedad heap después de cada reemplazo,
- explicación de por qué el costo es `O(log n)`.

##### Ejercicio 14.2 - `pushPop` en `PQ_ComplHeap`

Implementa:

```cpp
template<class T>
T pushPop(const T& x);
```

La operación debe insertar conceptualmente `x` y devolver el elemento de mayor prioridad, pero sin hacer siempre `insert()` y luego `delMax()`. Diseña una versión eficiente considerando estos casos:

1. heap vacío,
2. `x` tiene mayor prioridad que la raíz,
3. `x` tiene menor o igual prioridad que la raíz.

Entrega:

- implementación,
- al menos cinco casos de prueba,
- comparación razonada con `insert + delMax`,
- explicación de cuándo el costo puede ser `O(1)` y cuándo `O(log n)`.

##### Ejercicio 14.3 - Construcción desde rango

Agrega un constructor o método estático para construir un heap completo desde un rango de iteradores:

```cpp
template<class It>
static PQ_ComplHeap fromRange(It first, It last);
```

Debe usar `heapify` de Floyd, no inserciones sucesivas.

Prueba con:

```cpp
std::vector<int> data = {14, 3, 27, 1, 9, 40, 18, 40, 2};
```

Entrega:

- implementación,
- prueba con vector vacío,
- prueba con repetidos,
- demostración de que el resultado es heap válido,
- comparación con construcción por inserción.

##### Ejercicio 14.4 - Extracción de los `k` mayores

Implementa una función libre:

```cpp
template<class T, class Compare>
std::vector<T> kLargest(std::vector<T> data, std::size_t k, Compare comp);
```

Debe devolver los `k` elementos de mayor prioridad usando `PQ_ComplHeap` o `heapify` de Floyd. La función no debe modificar el vector original recibido por el usuario.

Casos obligatorios:

1. `k = 0`,
2. `k = 1`,
3. `k = n`,
4. `k > n`,
5. datos con repetidos.

Entrega:

- implementación,
- pruebas,
- complejidad en función de `n` y `k`,
- explicación de cuándo conviene frente a ordenar todo el vector.

##### Ejercicio 14.5 - Fusión de `k` secuencias ordenadas con cola de prioridad

Implementa:

```cpp
template<class T>
std::vector<T> mergeKSorted(const std::vector<std::vector<T>>& lists);
```

Cada lista de entrada ya está ordenada de menor a mayor. La salida debe quedar ordenada de menor a mayor. Usa una cola de prioridad para mantener el siguiente candidato de cada lista.

Ejemplo:

```cpp
{
    {1, 4, 9},
    {2, 2, 8, 10},
    {0, 7},
    {}
}
```

Salida esperada:

```cpp
{0, 1, 2, 2, 4, 7, 8, 9, 10}
```

Entrega:

- estructura auxiliar usada dentro del heap,
- implementación,
- prueba con listas vacías,
- prueba con repetidos,
- análisis `O(N log k)`.

##### Ejercicio 14.6 - Simulador de eventos con prioridad

Crea un demostración `demo_priority_events.cpp` con una estructura:

```cpp
struct Event {
    int time;
    int priority;
    std::string name;
};
```

La cola debe atender primero el evento con mayor `priority`. En caso de empate, debe atender primero el de menor `time`. En caso de nuevo empate, ordena por `name`.

Entrega:

- comparador personalizado,
- carga de al menos diez eventos,
- salida del orden de atención,
- explicación de cómo el comparador define la prioridad real.

##### Ejercicio 14.7 - Cola de prioridad estable

Implementa una envoltura que preserve orden de llegada entre elementos de igual prioridad:

```cpp
template<class T>
struct StableItem {
    T value;
    int priority;
    std::size_t arrival;
};
```

Luego usa `PQ_ComplHeap<StableItem<T>, Compare>` para que:

1. mayor prioridad salga primero,
2. si hay empate, menor `arrival` salga primero.

Entrega:

- comparador,
- demostración con empates,
- prueba de estabilidad,
- explicación de por qué un heap normal no es estable por defecto.

##### Ejercicio 14.8 - Verificador de arreglo heap y primer error

Además de `complHeapIsValid`, implementa una función que indique dónde falla el heap:

```cpp
template<class T, class Compare>
std::optional<std::tuple<std::size_t, std::size_t>>
firstHeapViolation(const std::vector<T>& heapArray, Compare comp);
```

Debe retornar el primer par `(parent, child)` que viola la propiedad de heap, o `std::nullopt` si el arreglo es válido.

Prueba con:

```cpp
{90, 70, 80, 10, 30, 20, 60}   // válido
{90, 70, 80, 10, 100, 20, 60}  // inválido
{1, 2, 3}                      // inválido para max-heap
```

Entrega:

- implementación,
- pruebas,
- explicación de por qué esta función ayuda a depurar `percolateUp` y `percolateDown`.

##### Ejercicio 14.9 - `heapSort` sobre objetos

Define:

```cpp
struct Student {
    std::string code;
    std::string name;
    double score;
};
```

Ordena un vector de `Student` usando `heapSort` bajo dos criterios:

1. por `score` descendente,
2. por `code` ascendente.

No uses `std::sort`.

Entrega:

- comparadores,
- salida antes y después,
- prueba con notas repetidas,
- explicación de por qué el algoritmo puede cambiar el orden relativo de alumnos con la misma nota.

##### Ejercicio 14.10 - Conteo de frecuencias con Huffman

Implementa una función que reciba un texto y construya automáticamente el alfabeto para Huffman:

```cpp
std::vector<HuffmanSymbol> buildAlphabetFromText(const std::string& text);
```

Luego usa `huffmanGenerateCodes` para codificar el texto.

Casos obligatorios:

1. texto vacío,
2. texto con un solo carácter repetido,
3. texto con espacios,
4. texto con letras repetidas,
5. texto con signos de puntuación.

Entrega:

- implementación,
- tabla de frecuencias,
- tabla de códigos,
- texto codificado,
- verificación de decodificación.

##### Ejercicio 14.11 - Medición de longitud promedio de Huffman

Agrega:

```cpp
double averageCodeLength(const std::vector<HuffmanSymbol>& alphabet,
                         const std::unordered_map<char, std::string>& codes);
```

Debe calcular la longitud promedio ponderada por frecuencia.

Prueba con dos alfabetos:

```cpp
{ {'A', 50}, {'B', 25}, {'C', 15}, {'D', 10} }
{ {'A', 25}, {'B', 25}, {'C', 25}, {'D', 25} }
```

Responde:

1. ¿En qué caso Huffman se beneficia más de frecuencias desiguales?
2. ¿Por qué símbolos más frecuentes deberían recibir códigos más cortos?
3. ¿Qué pasa cuando todas las frecuencias son iguales?.

Entrega:

- implementación,
- tabla de códigos,
- longitud promedio de cada alfabeto.

##### Ejercicio 14.12 - Validación fuerte de Huffman

Implementa una función:

```cpp
bool validateHuffmanRoundTrip(const std::string& text);
```

Debe:

1. construir el alfabeto,
2. generar códigos,
3. codificar el texto,
4. decodificarlo,
5. verificar que el resultado sea exactamente igual al original.

Entrega:

- implementación,
- pruebas con al menos cinco textos,
- manejo explícito del texto vacío,
- explicación de qué errores de Huffman detecta esta prueba.

##### Ejercicio 14.13 - `mergeAll` para heap izquierdista

Implementa una función que reciba varios heaps izquierdistas y los fusione:

```cpp
template<class T, class Compare>
PQ_LeftHeap<T, Compare> mergeAll(std::vector<PQ_LeftHeap<T, Compare>> heaps);
```

Debe usar repetidamente `merge`, no extraer todos los elementos para reinsertarlos uno por uno.

Entrega:

- implementación,
- demostración con cuatro heaps,
- validación del heap resultante,
- análisis de costo en términos del número de heaps y sus tamaños.

##### Ejercicio 14.14 - Conversión de `PQ_ComplHeap` a `PQ_LeftHeap`

Implementa una función de conversión educativa:

```cpp
template<class T, class Compare>
PQ_LeftHeap<T, Compare> toLeftHeap(PQ_ComplHeap<T, Compare> h);
```

Puedes extraer de `PQ_ComplHeap` e insertar en `PQ_LeftHeap`. Luego compara el orden de salida entre ambas estructuras.

Entrega:

- implementación,
- demostración,
- prueba de que ambas producen la misma secuencia de prioridades,
- explicación de por qué las formas internas no tienen por qué parecerse.

##### Ejercicio 14.15 - Operaciones ordenadas en `Treap`

Agrega al `Treap` una operación:

```cpp
std::vector<T> rangeQuery(const T& low, const T& high) const;
```

Debe devolver las claves `x` tales que `low <= x <= high`, en orden ascendente.

Prueba con claves:

```cpp
{50, 30, 70, 20, 40, 60, 80, 35, 45, 65}
```

y consultas:

```cpp
[30, 60]
[10, 25]
[65, 90]
[90, 100]
```

Entrega:

- implementación recursiva o iterativa,
- pruebas,
- explicación de por qué se usa la propiedad BST y no la prioridad.

##### Ejercicio 14.16 - `rank` en `Treap`

Modifica `Treap` para mantener en cada nodo el tamaño de su subárbol. Luego implementa:

```cpp
std::size_t rank(const T& x) const;
```

Debe retornar cuántas claves son estrictamente menores que `x`.

Casos:

```cpp
rank(20)
rank(35)
rank(50)
rank(90)
```

Entrega:

- cambios en `Node`,
- actualización de tamaños después de rotaciones,
- pruebas después de inserciones y eliminaciones,
- explicación de qué bug aparecería si olvidas actualizar tamaños durante una rotación.

##### Ejercicio 14.17 - `select` en `Treap`

Usando el tamaño de subárbol del ejercicio anterior, implementa:

```cpp
std::optional<T> select(std::size_t k) const;
```

Debe retornar la clave con rango `k`, usando indexación desde cero. Por ejemplo, `select(0)` retorna la mínima clave.

Entrega:

- implementación,
- prueba para `k = 0`, `k = n/2`, `k = n-1` y `k >= n`,
- explicación de por qué `select` cuesta `O(h)`.

##### Ejercicio 14.18 - Pruebas aleatorias controladas

Crea una prueba interna que genere secuencias pseudoaleatorias con semilla fija:

```cpp
std::mt19937 rng(232);
```

Debe probar al menos:

1. insertar 200 enteros en `PQ_ComplHeap` y validar después de cada inserción,
2. eliminar hasta vaciar y verificar que la salida no aumenta si es max-heap,
3. insertar 200 claves con prioridades fijas en `Treap`,
4. eliminar 100 claves y verificar `isTreap()` después de cada eliminación,
5. generar 20 textos pequeños y verificar Huffman por round-trip.

Entrega:

- prueba interna,
- salida de `ctest`,
- explicación de por qué se usa semilla fija.

##### Ejercicio 14.19 - Miniaplicación: planificador de tareas

Crea un programa `demo_task_scheduler.cpp` usando cola de prioridad.

Cada tarea tiene:

```cpp
struct Task {
    std::string name;
    int urgency;
    int duration;
    int deadline;
};
```

Diseña un comparador para atender primero:

1. mayor `urgency`,
2. menor `deadline`,
3. menor `duration`,
4. `name` lexicográficamente menor.

Entrega:

- comparador,
- al menos doce tareas,
- orden de ejecución,
- explicación de cada criterio de desempate,
- reflexión breve sobre por qué esto modela una cola de prioridad y no un BST.

##### Ejercicio 14.20 - Miniaplicación: autocompresor Huffman básico

Crea un demostración que reciba un texto constante dentro del código, genere códigos Huffman, codifique y decodifique.

Debe imprimir:

1. texto original,
2. tabla de frecuencias,
3. tabla de códigos,
4. longitud original en bits suponiendo 8 bits por carácter,
5. longitud codificada,
6. porcentaje aproximado de reducción,
7. texto decodificado,
8. verificación de igualdad.

Entrega:

- demostración,
- ejecución con tres textos distintos,
- explicación de por qué los resultados dependen de la distribución de frecuencias.


#### Bloque 15 - Reto integrador de codificación

Este bloque puede usarse como reto adicional o como sustituto de parte de los ejercicios del bloque anterior.

Implementa un archivo nuevo:

```text
Semana6/demos/demo_integrator.cpp
```

El programa debe usar, en una sola ejecución:

1. `PQ_ComplHeap` para atender eventos por prioridad,
2. `heapSort` para ordenar un resumen final,
3. `Huffman_PQ` para codificar los nombres de eventos atendidos,
4. `Treap` para mantener las claves de eventos ya procesados y responder consultas de rango,
5. al menos una validación de invariante después de cada fase.

Requisitos mínimos:

- usar al menos diez eventos,
- no usar `std::priority_queue`,
- no usar `std::sort`,
- imprimir una tabla final,
- incluir al menos tres pruebas públicas o internas asociadas.

Entrega:

- archivo nuevo de demostración,
- pruebas agregadas,
- salida completa,
- explicación de qué estructura se eligió para cada tarea y por qué.
