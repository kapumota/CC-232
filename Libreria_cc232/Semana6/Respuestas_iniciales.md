### Algunas respuestas de la Actividad 6 CC232
#### Bloque 2 - Utilidades de heap completo

El **Bloque 2** pide modificar `PQ_ComplHeap_macro.h` agregando utilidades `constexpr` sin macros, y luego actualizar 
`PQ_ComplHeap_percolateDown.h` para usar esas funciones auxiliares. 
El objetivo es que las pruebas de frontera del heap implícito sean más legibles y menos propensas a errores. 

#### 1. Modificación en `PQ_ComplHeap_macro.h`

Agrega estas funciones al final del archivo, antes de cerrar el `namespace ods`.

```cpp
// MOD-A6-B2: utilidades auxiliares para frontera en heap completo.
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqInHeap(pqLeftChild(i), n);
}

// MOD-A6-B2: verifica si existe hijo derecho en la representacion implicita.
inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqInHeap(pqRightChild(i), n);
}

// MOD-A6-B2: una hoja pertenece al heap y no tiene hijo izquierdo.
inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && !pqHasLeftChild(i, n);
}

// MOD-A6-B2: un nodo interno pertenece al heap y tiene al menos hijo izquierdo.
inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqHasLeftChild(i, n);
}
```

El archivo ya tenía funciones como `pqParent`, `pqLeftChild`, `pqRightChild`, `pqInHeap`, `pqHasParent` y `pqLastInternal`,  estas nuevas 
funciones completan la abstracción para consultar hijos, hojas y nodos internos. 

#### 2. Modificación en `PQ_ComplHeap_percolateDown.h`

Reemplaza la función `complHeapPercolateDown` por esta versión:

```cpp
template <typename T, typename Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a,
                                   std::size_t n,
                                   std::size_t i,
                                   Compare comp) {
    // MOD-A6-B2: se usa pqIsInternal para expresar que solo se baja si hay hijo izquierdo.
    while (pqIsInternal(i, n)) {
        std::size_t c = pqLeftChild(i);

        // MOD-A6-B2: si existe hijo derecho, se compara contra el hijo izquierdo.
        if (pqHasRightChild(i, n)) {
            const std::size_t r = pqRightChild(i);
            if (comp(a[c], a[r])) {
                c = r;
            }
        }

        if (!comp(a[i], a[c])) {
            break;
        }

        std::swap(a[i], a[c]);
        i = c;
    }

    return i;
}
```

La versión original ya hacía la bajada mientras existiera hijo izquierdo y, si existía hijo derecho, elegía el hijo dominante antes de intercambiar. 
La nueva versión conserva la misma lógica, pero expresa esas condiciones mediante `pqIsInternal` y `pqHasRightChild`.

#### 3. Respuestas del Bloque 2

**1. ¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?**

Porque la representación del heap completo es implícita: no hay nodos enlazados, sino posiciones en un `vector`. Las relaciones estructurales se calculan con índices:

```cpp
parent(i) = (i - 1) / 2
left(i)   = 2 * i + 1
right(i)  = 2 * i + 2
```

Si estas fórmulas se repiten manualmente en muchas partes, aumentan los errores de frontera. Al moverlas a funciones pequeñas, el código queda más legible, reusable y fácil de probar.

**2. ¿Qué ventaja tiene `constexpr` frente a macros?**

`constexpr` respeta tipos, namespaces y reglas del compilador de C++. Una macro solo sustituye texto antes de compilar, por lo que puede producir errores difíciles de rastrear. Además, `constexpr` permite evaluación en tiempo de compilación cuando los argumentos son constantes, pero sigue funcionando como una función normal cuando los valores se conocen en ejecución.

**3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?**

En un heap completo puede ocurrir que un nodo tenga hijo izquierdo pero no hijo derecho. En ese caso, `percolateDown` no debe intentar leer `a[right(i)]`. La solución es asumir primero que el hijo dominante es el izquierdo:

```cpp
std::size_t c = pqLeftChild(i);
```

y solo comparar con el derecho si existe:

```cpp
if (pqHasRightChild(i, n)) { ... }
```

**4. ¿Qué condición identifica una hoja en la representación implícita?**

Una posición `i` es hoja si pertenece al heap y no tiene hijo izquierdo:

```cpp
pqInHeap(i, n) && !pqHasLeftChild(i, n)
```

En un heap binario completo, si un nodo no tiene hijo izquierdo, tampoco puede tener hijo derecho. Por eso basta revisar el hijo izquierdo.

**5. ¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?**

Cambió la forma de expresar las condiciones, no el algoritmo. Antes se escribía directamente:

```cpp
while (pqInHeap(pqLeftChild(i), n))
```

Ahora se escribe:

```cpp
while (pqIsInternal(i, n))
```

Esto comunica mejor la intención: "mientras el nodo sea interno, puede bajar". También se reemplaza la prueba directa del hijo derecho por `pqHasRightChild(i, n)`.

#### 4. Complejidad

La complejidad **no cambia**.

`percolateDown` sigue bajando como máximo una rama del heap. Como un heap binario completo con `n` elementos tiene altura `O(log n)`, la operación sigue costando:

```text
O(log n)
```

Las nuevas funciones auxiliares ejecutan operaciones aritméticas y comparaciones constantes, por lo que cuestan:

```text
O(1)
```

Entonces el costo total sigue siendo:

```text
O(log n) * O(1) = O(log n)
```



#### 5. Evidencia de compilación

En un entorno mínimo con `g++`, esta modificación compila y cubre los casos de hijo izquierdo único y de dos hijos:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```

Salida obtenida:

```text
OK Bloque 2: utilidades constexpr y percolateDown compilan y funcionan.
```

Para el repositorio completo, la evidencia que debes generar desde `Semana6` o desde la raíz configurada por el proyecto es:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

La entrega del Bloque 2 puede quedar como: código modificado en `PQ_ComplHeap_macro.h`, código modificado en `PQ_ComplHeap_percolateDown.h`, respuestas anteriores y salida de compilación.

#### Bloque 3 - Modificación de `percolateUp`: conteo de intercambios

El **Bloque 3** pide agregar una función nueva que haga lo mismo que `complHeapPercolateUp`, pero retornando cuántos intercambios realizó. 
También pide una demostración con la secuencia `{40, 10, 70, 30, 90, 20, 80, 60}` mostrando elemento insertado, número de intercambios, arreglo interno 
y validación de propiedad heap.

En el código actual, `complHeapPercolateUp` sube el elemento mientras tenga padre y mientras el comparador indique que el padre tiene menor
prioridad que el hijo, si se cumple, intercambia padre e hijo y continúa hacia arriba.
La inserción actual hace `push_back` y luego llama a `complHeapPercolateUp`, por lo que no conviene romper esa función existente.

#### 1. Archivo modificado: `include/PQ_ComplHeap_percolateUp.h`

Agrega esta función debajo de `complHeapPercolateUp`, sin eliminar la función original.

```cpp
#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>
#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateUp(std::vector<T>& a, std::size_t i, Compare comp) {
    while (pqHasParent(i)) {
        const std::size_t p = pqParent(i);

        if (!comp(a[p], a[i])) {
            break;
        }

        std::swap(a[p], a[i]);
        i = p;
    }

    return i;
}

// MOD-A6-B3: version instrumentada de percolateUp.
// Realiza los mismos intercambios que complHeapPercolateUp,
// pero retorna la cantidad de intercambios ejecutados.
template <class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a,
                                      std::size_t i,
                                      Compare comp) {
    std::size_t swaps = 0;

    while (pqHasParent(i)) {
        const std::size_t p = pqParent(i);

        if (!comp(a[p], a[i])) {
            break;
        }

        std::swap(a[p], a[i]);
        i = p;
        ++swaps;
    }

    return swaps;
}

} // namespace ods
```

La función mantiene exactamente el mismo criterio de subida: si `comp(a[p], a[i])` es verdadero, el hijo debe subir. 
En un max-heap con `std::less<int>`, eso significa que si `a[p] < a[i]`, se intercambian.

#### 2. Demostración nueva: `demos/demo_percolateup_count.cpp`

Puedes crear una demostración separada para no alterar demasiado `demo_pq_complheap_basico.cpp`.

```cpp
#include <functional>
#include <iostream>
#include <vector>

#include "PQ_ComplHeap_percolateUp.h"

namespace {

template <class T>
void printVector(const std::vector<T>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }

        std::cout << values[i];
    }

    std::cout << "]";
}

template <class T, class Compare>
bool isValidHeap(const std::vector<T>& values, Compare comp) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < values.size() && comp(values[i], values[left])) {
            return false;
        }

        if (right < values.size() && comp(values[i], values[right])) {
            return false;
        }
    }

    return true;
}

} // namespace

int main() {
    std::vector<int> heap;
    const std::vector<int> input = {40, 10, 70, 30, 90, 20, 80, 60};
    const std::less<int> comp;

    std::cout << "Bloque 3 - conteo de intercambios en percolateUp\n";
    std::cout << "Convencion: max-heap usando std::less<int>\n\n";

    for (const int value : input) {
        heap.push_back(value);

        const std::size_t swaps =
            ods::complHeapPercolateUpCount(heap, heap.size() - 1, comp);

        const bool valid = isValidHeap(heap, comp);

        std::cout << "insertado=" << value
                  << " | intercambios=" << swaps
                  << " | heap=";

        printVector(heap);

        std::cout << " | propiedad_heap="
                  << (valid ? "verdadero" : "falso")
                  << "\n";
    }

    return 0;
}
```

#### 3. Modificación opcional en `CMakeLists.txt`

El `CMakeLists.txt` ya define una función auxiliar `cc232_add_sem6_target` para crear ejecutables de demostraciones y enlazarlos con los headers de Semana 6.  Agrega esta línea junto a las otras demostraciones:

```cmake
cc232_add_sem6_target(sem6_demo_percolateup_count "demos/demo_percolateup_count.cpp")
```

Luego compila con:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_percolateup_count
ctest --test-dir build --output-on-failure
```

#### 4. Salida esperada de la demostración

La salida esperada para la secuencia del bloque es:

```text
Bloque 3 - conteo de intercambios en percolateUp
Convencion: max-heap usando std::less<int>

insertado=40 | intercambios=0 | heap=[40] | propiedad_heap=verdadero
insertado=10 | intercambios=0 | heap=[40, 10] | propiedad_heap=verdadero
insertado=70 | intercambios=1 | heap=[70, 10, 40] | propiedad_heap=verdadero
insertado=30 | intercambios=1 | heap=[70, 30, 40, 10] | propiedad_heap=verdadero
insertado=90 | intercambios=2 | heap=[90, 70, 40, 10, 30] | propiedad_heap=verdadero
insertado=20 | intercambios=0 | heap=[90, 70, 40, 10, 30, 20] | propiedad_heap=verdadero
insertado=80 | intercambios=1 | heap=[90, 70, 80, 10, 30, 20, 40] | propiedad_heap=verdadero
insertado=60 | intercambios=1 | heap=[90, 70, 80, 60, 30, 20, 40, 10] | propiedad_heap=verdadero
```

Esta salida es la traza esperada por simulación del algoritmo. Debe verificarse en tu máquina con la compilación del repositorio.

#### 5. Respuestas del Bloque 3

#### 1. ¿En qué casos `percolateUp` hace cero intercambios?

Hace cero intercambios cuando el elemento insertado no tiene padre, como ocurre al insertar el primer elemento, o cuando el padre ya tiene prioridad mayor 
o igual que el hijo.

En un max-heap con `std::less<int>`, eso ocurre cuando:

```cpp
a[parent] >= a[child]
```

Por ejemplo, al insertar `10` después de `40`, no se intercambia porque `40` ya domina a `10`.

#### 2. ¿En qué casos puede hacer `O(log n)` intercambios?

Puede hacer `O(log n)` intercambios cuando el elemento insertado tiene mayor prioridad que todos sus ancestros y debe subir desde una hoja hasta la raíz.

Ejemplo de la traza:

```text
insertado=90 | intercambios=2 | heap=[90, 70, 40, 10, 30]
```

El `90` entra al final, sube sobre `30` y luego sobre `70`. En un heap más grande, podría subir por toda la altura del árbol.


#### 3. ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?

La inserción coloca primero el nuevo elemento al final del arreglo. Esa posición corresponde a la siguiente hoja disponible del árbol binario completo. 
Desde esa hoja, `percolateUp` solo puede subir por el camino hacia la raíz.

Por eso, el número máximo de intercambios está acotado por la altura del heap:

```text
altura = O(log n)
```

No puede recorrer ramas laterales ni visitar todos los nodos.


#### 4. ¿Por qué el arreglo interno no necesariamente queda ordenado?

Porque el heap no mantiene orden total en el arreglo. Mantiene una propiedad local entre padres e hijos.

En un max-heap se garantiza que cada padre sea mayor o igual que sus hijos, pero no se garantiza que:

```text
a[0] >= a[1] >= a[2] >= a[3] ...
```

Por ejemplo, este arreglo final es heap válido:

```text
[90, 70, 80, 60, 30, 20, 40, 10]
```

pero no está ordenado de forma descendente, porque `80` aparece después de `70`, y `40` aparece después de `20`.

#### 5. ¿Qué propiedad sí queda garantizada?

Queda garantizada la **propiedad heap**:

```text
Para todo nodo i:
a[i] tiene prioridad mayor o igual que sus hijos.
```

En max-heap con `std::less<int>`:

```text
a[i] >= a[left(i)]
a[i] >= a[right(i)]
```

cuando esos hijos existen.

#### 6. Argumento de costo

`complHeapPercolateUpCount` realiza las mismas operaciones estructurales que `complHeapPercolateUp`, pero agrega un contador `swaps`. 
Ese contador solo cuesta `O(1)` por intercambio.

En el peor caso, el elemento insertado sube desde una hoja hasta la raíz. La altura de un heap binario completo con `n` elementos es:

```text
O(log n)
```

Por tanto:

```text
Tiempo peor caso: O(log n)
Tiempo mejor caso: O(1)
Espacio adicional: O(1)
```

#### Bloque 4 - Modificación de `percolateDown`: elección del hijo dominante

El **Bloque 4** pide instrumentar `percolateDown` para observar cuántos intercambios realiza al reparar el heap después de eliminar el máximo. 
En el código actual, `delMax` toma el máximo de la raíz, mueve el último elemento a la raíz, elimina la última posición y luego llama 
a `complHeapPercolateDown` desde el índice `0`.

La función original `complHeapPercolateDown` baja el elemento mientras exista hijo izquierdo, elige el hijo dominante comparando izquierdo y derecho, y
luego intercambia si el hijo domina al nodo actual. 

#### 1. Código modificado: `include/PQ_ComplHeap_percolateDown.h`

Agrega esta función debajo de `complHeapPercolateDown`, sin eliminar la original.

```cpp
#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a,
                                   std::size_t n,
                                   std::size_t i,
                                   Compare comp) {
    while (pqInHeap(pqLeftChild(i), n)) {
        std::size_t c = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);

        if (pqInHeap(r, n) && comp(a[c], a[r])) {
            c = r;
        }

        if (!comp(a[i], a[c])) {
            break;
        }

        std::swap(a[i], a[c]);
        i = c;
    }

    return i;
}

// MOD-A6-B4: version instrumentada de percolateDown.
// Repara el heap desde el indice i y retorna la cantidad de intercambios.
template <class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a,
                                        std::size_t n,
                                        std::size_t i,
                                        Compare comp) {
    std::size_t swaps = 0;

    while (pqInHeap(pqLeftChild(i), n)) {
        std::size_t c = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);

        // MOD-A6-B4: se elige el hijo dominante.
        // En max-heap con std::less<T>, domina el hijo con mayor valor.
        if (pqInHeap(r, n) && comp(a[c], a[r])) {
            c = r;
        }

        // MOD-A6-B4: si el nodo actual ya domina a su hijo dominante,
        // la propiedad heap queda restaurada.
        if (!comp(a[i], a[c])) {
            break;
        }

        std::swap(a[i], a[c]);
        i = c;
        ++swaps;
    }

    return swaps;
}

} // namespace ods
```

Esta versión conserva el mismo algoritmo, pero agrega un contador. La complejidad no cambia: sigue siendo `O(log n)` en el peor caso.

#### 2. Demostración nueva: `demos/demo_percolatedown_count.cpp`

```cpp
#include <functional>
#include <iostream>
#include <vector>

#include "PQ_ComplHeap_insert.h"
#include "PQ_ComplHeap_percolateDown.h"

namespace {

template <class T>
void printVector(const std::vector<T>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }

        std::cout << values[i];
    }

    std::cout << "]";
}

template <class T, class Compare>
bool isValidHeap(const std::vector<T>& values, Compare comp) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < values.size() && comp(values[i], values[left])) {
            return false;
        }

        if (right < values.size() && comp(values[i], values[right])) {
            return false;
        }
    }

    return true;
}

} // namespace

int main() {
    std::vector<int> heap;
    const std::vector<int> input = {40, 10, 70, 30, 90, 20, 80, 60};
    const std::less<int> comp;

    for (const int value : input) {
        ods::complHeapInsert(heap, value, comp);
    }

    std::cout << "Bloque 4 - conteo de intercambios en percolateDown\n";
    std::cout << "Convencion: max-heap usando std::less<int>\n\n";

    std::cout << "heap inicial=";
    printVector(heap);
    std::cout << " | propiedad_heap="
              << (isValidHeap(heap, comp) ? "verdadero" : "falso")
              << "\n\n";

    while (!heap.empty()) {
        const int maxValue = heap.front();

        heap.front() = heap.back();
        heap.pop_back();

        const std::vector<int> beforeRepair = heap;

        std::size_t swaps = 0;
        if (!heap.empty()) {
            swaps = ods::complHeapPercolateDownCount(heap, heap.size(), 0, comp);
        }

        std::cout << "maximo_eliminado=" << maxValue
                  << " | antes_reparar=";
        printVector(beforeRepair);

        std::cout << " | intercambios=" << swaps
                  << " | despues_reparar=";
        printVector(heap);

        std::cout << " | propiedad_heap="
                  << (isValidHeap(heap, comp) ? "verdadero" : "falso")
                  << "\n";
    }

    return 0;
}
```

#### 3. Agregar target al `CMakeLists.txt`

Agrega la demostración junto a los otros targets de Semana 6.

```cmake
cc232_add_sem6_target(sem6_demo_percolatedown_count "demos/demo_percolatedown_count.cpp")
```

Comandos:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_percolatedown_count
ctest --test-dir build --output-on-failure
```

#### 4. Salida esperada

La salida esperada con la entrada `{40, 10, 70, 30, 90, 20, 80, 60}` es:

```text
Bloque 4 - conteo de intercambios en percolateDown
Convencion: max-heap usando std::less<int>

heap inicial=[90, 70, 80, 60, 30, 20, 40, 10] | propiedad_heap=verdadero

maximo_eliminado=90 | antes_reparar=[10, 70, 80, 60, 30, 20, 40] | intercambios=2 | despues_reparar=[80, 70, 40, 60, 30, 20, 10] | propiedad_heap=verdadero
maximo_eliminado=80 | antes_reparar=[10, 70, 40, 60, 30, 20] | intercambios=2 | despues_reparar=[70, 60, 40, 10, 30, 20] | propiedad_heap=verdadero
maximo_eliminado=70 | antes_reparar=[20, 60, 40, 10, 30] | intercambios=2 | despues_reparar=[60, 30, 40, 10, 20] | propiedad_heap=verdadero
maximo_eliminado=60 | antes_reparar=[20, 30, 40, 10] | intercambios=1 | despues_reparar=[40, 30, 20, 10] | propiedad_heap=verdadero
maximo_eliminado=40 | antes_reparar=[10, 30, 20] | intercambios=1 | despues_reparar=[30, 10, 20] | propiedad_heap=verdadero
maximo_eliminado=30 | antes_reparar=[20, 10] | intercambios=0 | despues_reparar=[20, 10] | propiedad_heap=verdadero
maximo_eliminado=20 | antes_reparar=[10] | intercambios=0 | despues_reparar=[10] | propiedad_heap=verdadero
maximo_eliminado=10 | antes_reparar=[] | intercambios=0 | despues_reparar=[] | propiedad_heap=verdadero
```

#### 5. Trazado manual de una eliminación

Tomemos la primera eliminación.

Heap inicial:

```text
[90, 70, 80, 60, 30, 20, 40, 10]
```

El máximo es `90`, porque está en la raíz.

Primero se reemplaza la raíz con el último elemento, `10`, y se elimina la última posición:

```text
[10, 70, 80, 60, 30, 20, 40]
```

Ahora la raíz viola la propiedad de max-heap, porque `10` es menor que sus hijos `70` y `80`.

Primer paso de `percolateDown`:

```text
hijo izquierdo = 70
hijo derecho   = 80
hijo dominante = 80
```

Se intercambia `10` con `80`:

```text
[80, 70, 10, 60, 30, 20, 40]
```

Segundo paso:

```text
nodo actual    = 10
hijo izquierdo = 20
hijo derecho   = 40
hijo dominante = 40
```

Se intercambia `10` con `40`:

```text
[80, 70, 40, 60, 30, 20, 10]
```

Ahora `10` queda como hoja. La reparación termina. Se realizaron `2` intercambios.

#### 6. Respuestas del Bloque 4

#### 1. ¿Por qué después de `delMax` se mueve el último elemento a la raíz?

Porque en un heap binario completo la forma del árbol debe seguir siendo completa. Si se eliminara directamente la raíz, quedaría un hueco en la parte superior. Para conservar la representación compacta en arreglo, se toma el último elemento, que está en la última posición válida, se coloca en la raíz y luego se elimina la última celda del vector.

Así se conserva la propiedad estructural de árbol completo. Lo único que puede quedar roto es la propiedad heap.

#### 2. ¿Por qué la reparación baja y no sube?

Después de mover el último elemento a la raíz, ese elemento no tiene padre. Por tanto, no puede subir. La posible violación está entre la nueva raíz y sus hijos.

Por eso la reparación debe comparar hacia abajo. Si el nuevo elemento tiene menor prioridad que alguno de sus hijos, debe intercambiarse con el hijo dominante. Ese proceso continúa hasta que el nodo domine a sus hijos o llegue a una hoja.

#### 3. ¿Cómo se decide entre hijo izquierdo e hijo derecho?

Se elige el hijo con mayor prioridad según el comparador.

En un max-heap con `std::less<int>`, el hijo dominante es el mayor:

```cpp
if (pqInHeap(r, n) && comp(a[c], a[r])) {
    c = r;
}
```

Aquí `comp(a[c], a[r])` equivale a `a[c] < a[r]`. Si el hijo derecho es mayor que el izquierdo, se elige el derecho. Si no, se mantiene el izquierdo.

#### 4. ¿Qué pasa si el nodo actual tiene un solo hijo?

En un heap completo, si un nodo tiene un solo hijo, ese hijo necesariamente es el izquierdo. En ese caso, `percolateDown` no debe leer el hijo derecho. 
Solo compara el nodo actual con el hijo izquierdo.

Si el hijo izquierdo domina al nodo actual, intercambia. Si no, termina.

#### 5. ¿Por qué `delMax` tiene costo `O(log n)`?

`delMax` hace tres cosas:

```text
1. leer la raíz: O(1)
2. mover el último elemento a la raíz y hacer pop_back: O(1)
3. ejecutar percolateDown: O(log n)
```

La parte dominante es `percolateDown`, porque en el peor caso el elemento movido a la raíz baja desde la raíz hasta una hoja. 
La altura de un heap binario completo con `n` elementos es `O(log n)`. Por eso:

```text
delMax = O(log n)
```


El Bloque 4 muestra que `delMax` no destruye el heap de forma arbitraria. Primero conserva la forma completa del árbol moviendo el último elemento a la raíz. 
Luego repara la propiedad heap con una bajada local. 
La elección del hijo dominante es esencial: si se intercambiara con el hijo incorrecto, el máximo local podría quedar debajo y la propiedad heap seguiría rota.

La modificación no cambia la complejidad del algoritmo,  solo agrega instrumentación para medir cuántas reparaciones locales fueron necesarias.

#### Bloque 5 - Validación explícita de la propiedad heap

El **Bloque 5** pide agregar una validación explícita para `PQ_ComplHeap`, cubrir seis casos de prueba y justificar el invariante, el costo y 
el uso en pruebas. El repositorio ya tiene un método `isHeap()` dentro de `PQ_ComplHeap`, pero para resolver el bloque de forma más clara 
conviene agregar una función libre `complHeapIsValid(...)` y hacer que `PQ_ComplHeap::isValidHeap()` la use. Así no duplicamos lógica y mantenemos compatibilidad con las pruebas existentes que ya llaman `isHeap()`. 


#### 1. Crear archivo nuevo: `include/PQ_ComplHeap_validate.h`

```cpp
#pragma once

#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

// MOD-A6-B5: valida explicitamente la propiedad heap en un arreglo implicito.
// La convencion es: si comp(padre, hijo) es true, entonces el hijo domina al padre
// y la propiedad heap esta rota.
template <class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        const std::size_t left = pqLeftChild(i);
        const std::size_t right = pqRightChild(i);

        if (left < a.size() && comp(a[i], a[left])) {
            return false;
        }

        if (right < a.size() && comp(a[i], a[right])) {
            return false;
        }
    }

    return true;
}

} // namespace ods
```

Esta función valida la propiedad local padre-hijo. Con `std::less<int>`, la estructura se comporta como **max-heap**, porque si `padre < hijo`, entonces el hijo tiene mayor prioridad y el heap es inválido.

#### 2. Modificar `include/PQ_ComplHeap.h`

Agrega el include:

```cpp
#include "PQ_ComplHeap_validate.h"
```

Luego reemplaza el método actual `isHeap()` por esta versión con `isValidHeap()`:

```cpp
bool isValidHeap() const {
    // MOD-A6-B5: validacion explicita de la propiedad heap.
    return complHeapIsValid(data_, comp_);
}

bool isHeap() const {
    // MOD-A6-B5: se mantiene compatibilidad con las pruebas existentes.
    return isValidHeap();
}
```

La clase ya expone `data()`, `heapify()`, `insert()`, `delMax()` y `isHeap()`, así que esta modificación encaja directamente con el diseño  existente de `PQ_ComplHeap`. 

#### 3. Pruebas agregadas en `pruebas_publicas/test_public_week6.cpp`

Agrega esta función antes de `main()`:

```cpp
static void testBloque5ValidacionHeapPublica() {
    // MOD-A6-B5: caso 1 - heap vacio.
    ods::PQ_ComplHeap<int> emptyHeap;
    assert(emptyHeap.empty());
    assert(emptyHeap.isValidHeap());
    assert(emptyHeap.isHeap());

    // MOD-A6-B5: caso 2 - heap con un elemento.
    ods::PQ_ComplHeap<int> oneElementHeap;
    oneElementHeap.insert(42);
    assert(oneElementHeap.size() == 1);
    assert(oneElementHeap.getMax() == 42);
    assert(oneElementHeap.isValidHeap());

    // MOD-A6-B5: caso 3 - heap con elementos repetidos.
    ods::PQ_ComplHeap<int> repeatedHeap;
    for (int x : {5, 5, 5, 3, 3, 8, 8, 1}) {
        repeatedHeap.insert(x);
        assert(repeatedHeap.isValidHeap());
    }
    assert(repeatedHeap.getMax() == 8);

    // MOD-A6-B5: caso 4 - heap construido por inserciones.
    ods::PQ_ComplHeap<int> insertedHeap;
    for (int x : {40, 10, 70, 30, 90, 20, 80, 60}) {
        insertedHeap.insert(x);
        assert(insertedHeap.isValidHeap());
    }
    assert(insertedHeap.getMax() == 90);

    // MOD-A6-B5: caso 5 - heap construido por heapify mediante constructor.
    ods::PQ_ComplHeap<int> heapifiedHeap{4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89};
    assert(heapifiedHeap.isValidHeap());
    assert(heapifiedHeap.getMax() == 90);

    // MOD-A6-B5: caso 6 - heap despues de varias llamadas a delMax.
    int previous = heapifiedHeap.delMax();
    assert(previous == 90);
    assert(heapifiedHeap.isValidHeap());

    while (!heapifiedHeap.empty()) {
        const int current = heapifiedHeap.delMax();

        // En max-heap, las extracciones deben salir en orden no creciente.
        assert(previous >= current);
        previous = current;

        assert(heapifiedHeap.isValidHeap());
    }
}
```

Después, llama la función al inicio o al final de `main()`:

```cpp
int main() {
    testBloque5ValidacionHeapPublica();

    ods::PQ_ComplHeap<int> h{4, 10, 7, 1, 3, 9};

    assert(h.isHeap());
    assert(h.isValidHeap());

    assert(h.getMax() == 10);

    h.insert(12);

    assert(h.isHeap());
    assert(h.isValidHeap());

    assert(h.delMax() == 12);

    assert(h.isHeap());
    assert(h.isValidHeap());

    // Resto del main existente...
}
```

El archivo de pruebas públicas actual usa `assert`, no un framework tipo Catch2 o GoogleTest, por lo que esta forma mantiene el estilo del repositorio. 

#### 4. Pruebas agregadas en `pruebas_internas/test_internal_week6.cpp`

Agrega una prueba un poco más fuerte para validar también la función libre:

```cpp
static void testBloque5ValidacionHeapInterna() {
    // MOD-A6-B5: validacion directa de arreglo max-heap.
    const std::vector<int> validMaxHeap{90, 55, 89, 34, 17, 21, 8, 13, 4, 2, 1, 3};
    assert(ods::complHeapIsValid(validMaxHeap, std::less<int>{}));

    // MOD-A6-B5: arreglo invalido para max-heap, porque 100 domina a 1.
    const std::vector<int> invalidMaxHeap{1, 100, 2};
    assert(!ods::complHeapIsValid(invalidMaxHeap, std::less<int>{}));

    // MOD-A6-B5: validacion con comparador inverso. Esto representa min-heap.
    const std::vector<int> validMinHeap{1, 2, 3, 4, 5, 6};
    assert(ods::complHeapIsValid(validMinHeap, std::greater<int>{}));

    // MOD-A6-B5: repetidos no rompen el heap porque no hay dominancia estricta.
    const std::vector<int> repeatedValues{8, 8, 8, 5, 5, 8};
    assert(ods::complHeapIsValid(repeatedValues, std::less<int>{}));

    // MOD-A6-B5: validacion despues de inserciones y eliminaciones mezcladas.
    ods::PQ_ComplHeap<int> pq;

    for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13, 14}) {
        pq.insert(x);
        assert(pq.isValidHeap());
    }

    assert(pq.getMax() == 14);

    for (int i = 0; i < 4; ++i) {
        pq.delMax();
        assert(pq.isValidHeap());
    }

    pq.insert(100);
    assert(pq.isValidHeap());
    assert(pq.getMax() == 100);

    while (!pq.empty()) {
        pq.delMax();
        assert(pq.isValidHeap());
    }
}
```

Luego llama esta función dentro de `main()`:

```cpp
int main() {
    testBloque5ValidacionHeapInterna();

    // Resto del main existente...
}
```

Las pruebas internas ya validan una secuencia completa de inserciones y extracciones en `PQ_ComplHeap`, verificando `isHeap()` después de 
cada operación, este bloque refuerza esa idea con `isValidHeap()` y con la función libre `complHeapIsValid(...)`.

#### 5. Evidencia de compilación y pruebas

Desde `Libreria_cc232/Semana6`:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Salida esperada:

```text
Test project .../Semana6/build
    Start 1: semana6_public
1/2 Test #1: semana6_public ............   Passed
    Start 2: semana6_internal
2/2 Test #2: semana6_internal ..........   Passed

100% tests passed, 0 tests failed out of 2
```

El `CMakeLists.txt` define los ejecutables `sem6_test_public` y `sem6_test_internal`, y los registra como pruebas `semana6_public` y `semana6_internal`. 

#### 6. Respuestas del Bloque 5

#### 1. ¿Qué invariante verifica la función?

Verifica la **propiedad heap**. Para cada posición `i`, si existen sus hijos `left(i)` y `right(i)`, el padre debe tener prioridad mayor o igual que cada 
hijo según el comparador.

Con `std::less<int>`:

```text
a[i] >= a[left(i)]
a[i] >= a[right(i)]
```

Con `std::greater<int>`, la interpretación se invierte y se valida una estructura tipo min-heap.

#### 2. ¿Por qué basta revisar relaciones padre-hijo?

Porque la propiedad heap es local. Si cada padre domina a sus hijos, entonces por transitividad también domina a los nodos que están debajo de esos hijos
en la ruta correspondiente.

No se necesita comparar la raíz con todos los nodos ni cada nodo con todos sus descendientes. El heap no exige orden total, exige dominancia local entre padre e hijos.

#### 3. ¿Por qué no es necesario comparar cada nodo con todos sus descendientes?

Porque eso sería redundante y más costoso. Si se cumple:

```text
padre domina a hijo
hijo domina a nieto
nieto domina a bisnieto
```

entonces la dominancia se propaga por cada camino del árbol. Revisar padre-hijo en cada arista del árbol ya cubre toda la estructura.

Además, un heap completo representado en arreglo tiene como máximo `n - 1` relaciones padre-hijo reales. Validar esas relaciones basta.

#### 4. ¿Cuál es el costo de validar todo el heap?

El costo es:

```text
O(n)
```

La función recorre el arreglo una vez. Para cada índice calcula como máximo dos hijos y hace como máximo dos comparaciones. 
Cada paso cuesta `O(1)`, por eso validar `n` elementos cuesta `O(n)`.

El espacio adicional es:

```text
O(1)
```

porque solo usa índices auxiliares.


#### 5. ¿Por qué esta función es útil en pruebas pero no necesariamente en producción?

Es útil en pruebas porque detecta errores en `insert`, `delMax`, `heapify`, `percolateUp` y `percolateDown`.Si una operación deja mal ubicada una clave, `isValidHeap()` lo detecta inmediatamente.

Pero en producción no siempre conviene llamarla después de cada operación, porque agregaría un costo `O(n)` a operaciones que normalmente cuestan `O(log n)` o `O(1)`. Por ejemplo:

```text
insert: O(log n)
delMax: O(log n)
getMax: O(1)
isValidHeap: O(n)
```

Entonces, en pruebas es una herramienta de verificación, en producción debe usarse solo en modo diagnóstico, depuración o validaciones excepcionales.

#### Bloque 6 - Construcción de heap: inserciones sucesivas vs Floyd

El **Bloque 6** pide comparar dos formas de construir el mismo heap binario completo a partir de la entrada:

```cpp
{ 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 }
```

La **Construcción A** inserta uno por uno usando `complHeapInsert`, que internamente hace `push_back` y luego `percolateUp`. La **Construcción B** copia el vector original y aplica `complHeapHeapifyFloyd`, que llama a `percolateDown` desde los últimos nodos internos hacia la raíz. Esto corresponde exactamente a los archivos indicados por la actividad: `PQ_ComplHeap_heapifyFloyd.h`, `PQ_ComplHeap_insert.h` y `demo_heapify_floyd.cpp`. 


#### 1. Modificación recomendada: `demos/demo_heapify_floyd.cpp`

Reemplaza el contenido de `demo_heapify_floyd.cpp` por esta versión. Asume que ya resolviste los bloques anteriores y tienes disponibles:

* `complHeapPercolateUpCount`
* `complHeapPercolateDownCount`
* `complHeapIsValid` o `isValidHeap`

Para que la demostración sea autocontenida, aquí uso una función local `isValidHeap`.

```cpp
#include <functional>
#include <iostream>
#include <vector>

#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_ComplHeap_insert.h"
#include "PQ_ComplHeap_percolateUp.h"
#include "PQ_ComplHeap_percolateDown.h"

namespace {

template <class T>
void printVector(const std::vector<T>& xs, const char* label) {
    std::cout << label << ": [";

    for (std::size_t i = 0; i < xs.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }

        std::cout << xs[i];
    }

    std::cout << "]\n";
}

template <class T, class Compare>
bool isValidHeap(const std::vector<T>& values, Compare comp) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < values.size() && comp(values[i], values[left])) {
            return false;
        }

        if (right < values.size() && comp(values[i], values[right])) {
            return false;
        }
    }

    return true;
}

template <class T, class Compare>
std::size_t buildByInsertions(const std::vector<T>& input,
                              std::vector<T>& output,
                              Compare comp) {
    output.clear();

    std::size_t totalSwaps = 0;

    for (const T& value : input) {
        output.push_back(value);

        // MOD-A6-B6: se usa la version instrumentada del Bloque 3.
        totalSwaps += ods::complHeapPercolateUpCount(
            output,
            output.size() - 1,
            comp
        );
    }

    return totalSwaps;
}

template <class T, class Compare>
std::size_t buildByFloydCount(std::vector<T>& values, Compare comp) {
    if (values.size() < 2) {
        return 0;
    }

    std::size_t totalSwaps = 0;

    // MOD-A6-B6: Floyd procesa desde el ultimo nodo interno hasta la raiz.
    for (std::size_t i = values.size() / 2; i-- > 0;) {
        totalSwaps += ods::complHeapPercolateDownCount(
            values,
            values.size(),
            i,
            comp
        );
    }

    return totalSwaps;
}

} // namespace

int main() {
    const std::vector<int> input = {
        4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89
    };

    const std::less<int> comp;

    std::vector<int> heapByInsertions;
    std::vector<int> heapByFloyd = input;

    const std::size_t swapsInsertions =
        buildByInsertions(input, heapByInsertions, comp);

    const std::size_t swapsFloyd =
        buildByFloydCount(heapByFloyd, comp);

    std::cout << "Bloque 6 - construccion de heap\n";
    std::cout << "Convencion: max-heap usando std::less<int>\n\n";

    printVector(input, "arreglo inicial");
    printVector(heapByInsertions, "heap por inserciones");
    printVector(heapByFloyd, "heap por Floyd");

    std::cout << "\n";

    std::cout << "intercambios por inserciones: "
              << swapsInsertions << "\n";

    std::cout << "intercambios por Floyd: "
              << swapsFloyd << "\n";

    std::cout << "heap por inserciones valido: "
              << (isValidHeap(heapByInsertions, comp) ? "verdadero" : "falso")
              << "\n";

    std::cout << "heap por Floyd valido: "
              << (isValidHeap(heapByFloyd, comp) ? "verdadero" : "falso")
              << "\n";

    std::cout << "\nInterpretacion: ambos arreglos representan heaps validos, "
              << "aunque no necesariamente tienen la misma forma interna.\n";

    return 0;
}
```

#### 2. Versión alternativa si no quieres depender de contadores previos

Si todavía no agregaste `complHeapPercolateUpCount` y `complHeapPercolateDownCount`, puedes construir la comparación sin contar intercambios:

```cpp
std::vector<int> heapByInsertions;
for (int value : input) {
    ods::complHeapInsert(heapByInsertions, value, std::less<int>{});
}

std::vector<int> heapByFloyd = input;
ods::complHeapHeapifyFloyd(heapByFloyd, std::less<int>{});
```

En ese caso, en la tabla coloca "no instrumentado" en la columna de intercambios. Pero para resolver completamente el bloque, conviene usar los contadores de los bloques 3 y 4.

#### 3. Agregar o mantener el target en `CMakeLists.txt`

Si el target ya existe, no cambies nada. Si no existe, agrega:

```cmake
cc232_add_sem6_target(sem6_demo_heapify_floyd "demos/demo_heapify_floyd.cpp")
```

Comandos de compilación:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_heapify_floyd
ctest --test-dir build --output-on-failure
```

#### 4. Salida esperada

Con la entrada indicada, usando max-heap con `std::less<int>`, la salida esperada es:

```text
Bloque 6 - construccion de heap
Convencion: max-heap usando std::less<int>

arreglo inicial: [4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]
heap por inserciones: [90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]
heap por Floyd: [90, 55, 89, 34, 4, 21, 8, 13, 17, 2, 1, 3]

intercambios por inserciones: 9
intercambios por Floyd: 7
heap por inserciones valido: verdadero
heap por Floyd valido: verdadero

Interpretacion: ambos arreglos representan heaps validos, aunque no necesariamente tienen la misma forma interna.
```

#### 5. Tabla comparativa del Bloque 6

| Criterio             |                         Inserciones sucesivas |                              Heapify de Floyd |
| -------------------- | --------------------------------------------: | --------------------------------------------: |
| Entrada              | `[4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]` | `[4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]` |
| Operación usada      |                      `insert` + `percolateUp` |          `percolateDown` desde nodos internos |
| Arreglo final        | `[90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]` | `[90, 55, 89, 34, 4, 21, 8, 13, 17, 2, 1, 3]` |
| Intercambios medidos |                                           `9` |                                           `7` |
| Propiedad heap       |                                        válida |                                        válida |
| Costo peor caso      |                                  `O(n log n)` |                                        `O(n)` |
| Cuándo conviene      |              cuando llegan elementos en línea |              cuando ya tienes todos los datos |

#### 6. Trazado de las inserciones sucesivas

La construcción por inserciones empieza con un heap vacío. Cada elemento entra al final del vector y sube con `percolateUp` si domina a su padre.

| Elemento insertado | Intercambios | Arreglo interno después de insertar           |
| -----------------: | -----------: | --------------------------------------------- |
|                `4` |          `0` | `[4]`                                         |
|               `17` |          `1` | `[17, 4]`                                     |
|                `3` |          `0` | `[17, 4, 3]`                                  |
|               `90` |          `2` | `[90, 17, 3, 4]`                              |
|               `55` |          `1` | `[90, 55, 3, 4, 17]`                          |
|               `21` |          `1` | `[90, 55, 21, 4, 17, 3]`                      |
|                `8` |          `0` | `[90, 55, 21, 4, 17, 3, 8]`                   |
|               `13` |          `1` | `[90, 55, 21, 13, 17, 3, 8, 4]`               |
|               `34` |          `1` | `[90, 55, 21, 34, 17, 3, 8, 4, 13]`           |
|                `2` |          `0` | `[90, 55, 21, 34, 17, 3, 8, 4, 13, 2]`        |
|                `1` |          `0` | `[90, 55, 21, 34, 17, 3, 8, 4, 13, 2, 1]`     |
|               `89` |          `2` | `[90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]` |

Total: `9` intercambios.

#### 7. Trazado de Floyd

Floyd no inserta elementos. Parte del arreglo completo y repara subárboles desde abajo hacia arriba. Para `n = 12`, los índices internos son:

```text
0, 1, 2, 3, 4, 5
```

Floyd los procesa en orden inverso:

```text
5, 4, 3, 2, 1, 0
```

Trazado:

| Índice procesado | Intercambios | Arreglo después de reparar ese índice         |
| ---------------: | -----------: | --------------------------------------------- |
|              `5` |          `1` | `[4, 17, 3, 90, 55, 89, 8, 13, 34, 2, 1, 21]` |
|              `4` |          `0` | `[4, 17, 3, 90, 55, 89, 8, 13, 34, 2, 1, 21]` |
|              `3` |          `0` | `[4, 17, 3, 90, 55, 89, 8, 13, 34, 2, 1, 21]` |
|              `2` |          `2` | `[4, 17, 89, 90, 55, 21, 8, 13, 34, 2, 1, 3]` |
|              `1` |          `2` | `[4, 90, 89, 34, 55, 21, 8, 13, 17, 2, 1, 3]` |
|              `0` |          `2` | `[90, 55, 89, 34, 4, 21, 8, 13, 17, 2, 1, 3]` |

Total: `7` intercambios.

#### 8. Respuestas del Bloque 6

#### 1. ¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?

Porque un heap no exige un orden total del arreglo. Solo exige una relación local entre cada padre y sus hijos.

En un max-heap:

```text
padre >= hijo izquierdo
padre >= hijo derecho
```

mientras esos hijos existan.

Por eso estos dos arreglos son distintos:

```text
[90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]
[90, 55, 89, 34, 4, 21, 8, 13, 17, 2, 1, 3]
```

pero ambos son heaps válidos. El heap no determina una única representación para el mismo conjunto de claves.


#### 2. ¿Por qué insertar `n` elementos puede costar `O(n log n)`?

Cada inserción agrega un elemento al final y puede subirlo hasta la raíz con `percolateUp`.

En el peor caso, una inserción cuesta:

```text
O(log n)
```

Si se insertan `n` elementos uno por uno, el costo acumulado puede ser:

```text
O(log 1) + O(log 2) + ... + O(log n) = O(n log n)
```

Esto ocurre cuando muchos elementos nuevos tienen prioridad alta y suben varios niveles.

#### 3. ¿Por qué Floyd puede construir el heap en `O(n)`?

Porque Floyd no trata cada elemento como una inserción independiente. Parte del arreglo completo y solo llama a `percolateDown` en nodos internos.

La clave del análisis es que la mayoría de nodos están cerca de las hojas y bajan poco o nada. Hay muchos nodos con altura pequeña y pocos nodos con altura grande.

La suma real de trabajo queda acotada linealmente:

```text
muchos nodos bajan 0 o 1 nivel
pocos nodos bajan muchos niveles
costo total = O(n)
```

Por eso Floyd es más eficiente cuando ya tenemos todos los datos desde el inicio.

#### 4. ¿Qué nodos procesa Floyd primero?

Procesa primero el último nodo interno, luego avanza hacia atrás hasta la raíz.

En un vector de tamaño `n`, las hojas empiezan aproximadamente en `n / 2`. Por eso el último nodo interno está en:

```cpp
n/2 - 1
```

La implementación del repositorio usa este patrón:

```cpp
for (std::size_t i = a.size() / 2; i-- > 0;) {
    complHeapPercolateDown(a, a.size(), i, comp);
}
```

Ese ciclo procesa:

```text
n/2 - 1, n/2 - 2, ..., 1, 0
```

En la entrada del bloque, con `n = 12`, procesa:

```text
5, 4, 3, 2, 1, 0
```

#### 5. ¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?

Porque una hoja ya es un heap válido de tamaño 1. No tiene hijos, así que no puede violar la propiedad padre-hijo.

Llamar a `percolateDown` desde una hoja no cambiaría nada. Por eso Floyd empieza desde el último nodo interno. Cuando procesa un nodo interno, sus subárboles hijos ya fueron reparados o son hojas. Entonces puede reparar el subárbol completo con una sola bajada local.

#### 9. Explicación de complejidad

#### Construcción por inserciones

Cada elemento puede subir desde una hoja hasta la raíz.

```text
Costo por inserción: O(log n)
Número de inserciones: n
Costo total: O(n log n)
Espacio adicional: O(1), además del vector del heap
```

Esta estrategia es adecuada cuando los datos llegan en streaming o no se conocen todos al inicio.

#### Construcción por Floyd

Floyd trabaja desde abajo hacia arriba.

```text
Costo total: O(n)
Espacio adicional: O(1)
```

Es preferible cuando ya se tiene el arreglo completo y se quiere convertirlo en heap de forma eficiente.

Evidencia esperada:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_heapify_floyd
ctest --test-dir build --output-on-failure
```

El resultado debe mostrar que ambas construcciones producen heaps válidos, aunque los arreglos finales no sean idénticos.

#### Bloque 7 - Modificación de `heapSort`

El **Bloque 7** pide modificar `vector_heapSort.h` para que `heapSort` pueda ordenar en sentido **ascendente** o **descendente**, manteniendo la idea de **heapsort in situ** y sin usar `std::sort`. La actividad indica probar con `{5, 1, 5, 3, 8, 2, 8, 0}` y mostrar repetidos. 

El archivo actual `vector_heapSort.h` ya construye un heap con Floyd y luego intercambia la raíz con el final del rango activo, reduciendo progresivamente el tamaño del heap.

#### 1. Archivo modificado: `include/vector_heapSort.h`

Reemplaza el contenido por esta versión:

```cpp
#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

namespace detail {

template <class T, class Compare>
void heapSortWithComparator(std::vector<T>& a, Compare comp) {
    if (a.size() < 2) {
        return;
    }

    // MOD-A6-B7: construir el heap inicial usando Floyd.
    complHeapHeapifyFloyd(a, comp);

    // MOD-A6-B7: mover repetidamente la raiz al final del rango activo.
    for (std::size_t n = a.size(); n > 1; --n) {
        std::swap(a[0], a[n - 1]);
        complHeapPercolateDown(a, n - 1, 0, comp);
    }
}

} // namespace detail

template <class T, class Compare = std::less<T>>
void heapSort(std::vector<T>& a,
              Compare comp = Compare{},
              bool ascending = true) {
    if (ascending) {
        // MOD-A6-B7: con std::less<T> se construye max-heap y queda ascendente.
        detail::heapSortWithComparator(a, comp);
        return;
    }

    // MOD-A6-B7: para descendente se invierte la relacion de prioridad.
    auto reversedComp = [comp](const T& left, const T& right) mutable -> bool {
        return comp(right, left);
    };

    detail::heapSortWithComparator(a, reversedComp);
}

template <class T, class Compare = std::less<T>>
std::vector<T> heapSorted(std::vector<T> a,
                          Compare comp = Compare{},
                          bool ascending = true) {
    heapSort(a, comp, ascending);
    return a;
}

} // namespace ods
```

La firma nueva conserva compatibilidad con llamadas antiguas como:

```cpp
ods::heapSort(a);
```

y permite llamadas nuevas:

```cpp
ods::heapSort(a, std::less<int>{}, true);   // ascendente
ods::heapSort(a, std::less<int>{}, false);  // descendente
```

#### 2. Demostración actualizada: `demos/demo_heapsort.cpp`

La demostración actual solo muestra una entrada y una salida ascendente. Reemplázalo por esta versión:

```cpp
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "Capitulo6.h"

namespace {

template <class T>
void printVector(const std::vector<T>& xs, const char* label) {
    std::cout << label << ": [";

    for (std::size_t i = 0; i < xs.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }

        std::cout << xs[i];
    }

    std::cout << "]\n";
}

template <class T>
std::map<T, int> countValues(const std::vector<T>& xs) {
    std::map<T, int> counts;

    for (const T& value : xs) {
        ++counts[value];
    }

    return counts;
}

template <class T>
void printCounts(const std::vector<T>& xs, const char* label) {
    const std::map<T, int> counts = countValues(xs);

    std::cout << label << ": {";

    bool first = true;
    for (const auto& entry : counts) {
        if (!first) {
            std::cout << ", ";
        }

        first = false;
        std::cout << entry.first << " -> " << entry.second;
    }

    std::cout << "}\n";
}

} // namespace

int main() {
    const std::vector<int> input{5, 1, 5, 3, 8, 2, 8, 0};

    std::vector<int> ascending = input;
    std::vector<int> descending = input;

    ods::heapSort(ascending, std::less<int>{}, true);
    ods::heapSort(descending, std::less<int>{}, false);

    std::cout << "Bloque 7 - heapSort ascendente y descendente\n\n";

    printVector(input, "entrada");
    printVector(ascending, "salida ascendente");
    printVector(descending, "salida descendente");

    std::cout << "\nEvidencia de repetidos\n";
    printCounts(input, "conteo entrada");
    printCounts(ascending, "conteo ascendente");
    printCounts(descending, "conteo descendente");

    std::cout << "\nInterpretacion: los valores repetidos no se eliminan. "
              << "Aparecen dos 5 y dos 8 en ambas salidas.\n";

    return 0;
}
```

#### 3. Salida esperada

```text
Bloque 7 - heapSort ascendente y descendente

entrada: [5, 1, 5, 3, 8, 2, 8, 0]
salida ascendente: [0, 1, 2, 3, 5, 5, 8, 8]
salida descendente: [8, 8, 5, 5, 3, 2, 1, 0]

Evidencia de repetidos
conteo entrada: {0 -> 1, 1 -> 1, 2 -> 1, 3 -> 1, 5 -> 2, 8 -> 2}
conteo ascendente: {0 -> 1, 1 -> 1, 2 -> 1, 3 -> 1, 5 -> 2, 8 -> 2}
conteo descendente: {0 -> 1, 1 -> 1, 2 -> 1, 3 -> 1, 5 -> 2, 8 -> 2}

Interpretacion: los valores repetidos no se eliminan. Aparecen dos 5 y dos 8 en ambas salidas.
```

#### 4. CMake

Si el target ya existe, no cambies nada. Si no existe, agrega en `CMakeLists.txt`:

```cmake
cc232_add_sem6_target(sem6_demo_heapsort "demos/demo_heapsort.cpp")
```

Ejecuta:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_heapsort
ctest --test-dir build --output-on-failure
```

#### 5. Respuestas del Bloque 7

#### 1. ¿Por qué heapsort puede ordenar in situ?

Porque usa el mismo `vector` como dos zonas:

```text
[ heap activo | zona ya ordenada ]
```

Primero convierte todo el arreglo en heap. Luego intercambia la raíz con la última posición del heap activo. Esa última posición queda fija como parte de la zona ordenada. Después reduce el tamaño lógico del heap y repara desde la raíz con `percolateDown`.

No necesita una estructura auxiliar de tamaño `n`. Solo usa intercambios dentro del mismo arreglo.

#### 2. ¿Qué parte del algoritmo destruye gradualmente el heap?

Esta parte:

```cpp
for (std::size_t n = a.size(); n > 1; --n) {
    std::swap(a[0], a[n - 1]);
    complHeapPercolateDown(a, n - 1, 0, comp);
}
```

Cada iteración extrae conceptualmente la raíz del heap, la coloca al final del rango activo y reduce `n`. El heap queda restringido a `[0, n - 2]`. La parte final `[n - 1, size - 1]` ya no se considera heap: es la zona ordenada.

#### 3. ¿Por qué heapsort cuesta `O(n log n)`?

Tiene dos fases:

```text
1. heapify de Floyd: O(n)
2. n - 1 extracciones implícitas: cada una cuesta O(log n)
```

La segunda fase domina:

```text
O(n) + O(n log n) = O(n log n)
```

Por eso heapsort tiene costo `O(n log n)` en peor caso, promedio y mejor caso asintótico.

#### 4. ¿Es heapsort estable? Justifica con un ejemplo.

No. Heapsort **no es estable** en su forma clásica.

Un algoritmo estable conserva el orden relativo de elementos con claves iguales. Por ejemplo, si entran estos elementos:

```text
(5, A), (1, X), (5, B), (3, Y)
```

y se ordena por la primera componente, una salida estable debería mantener:

```text
(5, A) antes de (5, B)
```

Pero heapsort puede producir:

```text
(1, X), (3, Y), (5, B), (5, A)
```

Los dos elementos con clave `5` cambiaron su orden relativo. Esto ocurre porque heapsort realiza intercambios de larga distancia entre la raíz y el final del rango activo.

#### 5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?

`heapSort` trabaja **in situ** sobre el mismo vector. No necesita construir una cola de prioridad separada ni almacenar todas las extracciones en otro arreglo.

En cambio, extraer todos los elementos con `delMax` normalmente implica:

```text
1. construir una estructura PQ_ComplHeap,
2. llamar delMax repetidamente,
3. guardar las salidas en otro contenedor si se quiere conservar el resultado ordenado.
```

Ambos enfoques tienen costo `O(n log n)`, pero su intención es distinta:

```text
heapSort: ordenar un arreglo.
PQ + delMax: consumir elementos por prioridad.
```

Además, `delMax` es más natural cuando la prioridad se usa dinámicamente, por ejemplo cuando se intercalan inserciones y extracciones. `heapSort` es más adecuado cuando ya se tiene todo el arreglo y se quiere dejarlo ordenado.

#### 6. Trazado breve del algoritmo con la entrada del bloque

Entrada:

```text
[5, 1, 5, 3, 8, 2, 8, 0]
```

Para ascendente con `std::less<int>`:

```text
1. Se construye un max-heap.
2. La raíz contiene uno de los máximos: 8.
3. Se intercambia la raíz con el final del rango activo.
4. Se reduce el heap activo.
5. Se repara con percolateDown.
6. Se repite hasta que el arreglo queda ascendente.
```

Resultado:

```text
[0, 1, 2, 3, 5, 5, 8, 8]
```

Para descendente, la implementación invierte el comparador y construye el heap equivalente para colocar progresivamente los menores al final. Resultado:

```text
[8, 8, 5, 5, 3, 2, 1, 0]
```

#### Bloque 8 - Heap izquierdista: validación de `merge`

El **Bloque 8** pide agregar `isValidLeftHeap()`, validar `merge`, modificar la demostración y explicar por qué `merge` es la operación central del heap izquierdista. En el código actual, `PQ_LeftHeap` ya implementa `insert`, `delMax`, `merge`, `levelOrder()` e `isLeftistHeap()`. Internamente cada nodo almacena `value`, `npl`, `left` y `right`; `insert` mezcla la raíz actual con un nodo nuevo; `delMax` elimina la raíz y mezcla sus dos subárboles; `merge` une dos heaps y vacía el segundo.

#### 1. Explicación técnica: ¿qué es un heap izquierdista?

Un **heap izquierdista** es una cola de prioridad implementada como árbol binario enlazado. Mantiene dos propiedades:

1. **Propiedad heap**
   En un max-heap, cada padre debe tener prioridad mayor o igual que sus hijos. Con `std::less<int>`, eso equivale a:

```text
padre >= hijo_izquierdo
padre >= hijo_derecho
```

2. **Propiedad izquierdista**
   El camino más corto hacia un nodo nulo debe estar preferentemente por la derecha. Para eso se usa `npl`, normalmente entendido como *null path length*. En esta implementación:

```text
npl(nullptr) = 0
npl(nodo) = npl(nodo->right) + 1
```

y debe cumplirse:

```text
npl(left) >= npl(right)
```

La idea es que el subárbol derecho sea el más corto. Como `merge` avanza principalmente por la derecha, esa propiedad evita que la fusión se vuelva lineal en casos comunes.


#### 2. Modificación principal en `include/PQ_LeftHeap.h`

La versión actual ya tiene `isLeftistHeap()`, pero su validación no comprueba explícitamente la consistencia de `size()` contra la cantidad real de nodos. El Bloque 8 pide validar al menos: propiedad heap, propiedad izquierdista, tamaño y consistencia de `npl`.

Reemplaza la parte de validación interna por esta versión. La modificación conserva `isLeftistHeap()` para compatibilidad y agrega `isValidLeftHeap()`.

```cpp
// Dentro de la clase PQ_LeftHeap, en la zona publica:

bool isValidLeftHeap() const {
    // MOD-A6-B8: validacion completa de heap izquierdista.
    const Check result = check(root_);
    return result.ok && result.count == n_;
}

bool isLeftistHeap() const {
    // MOD-A6-B8: se conserva compatibilidad con codigo previo.
    return isValidLeftHeap();
}
```

Ahora reemplaza la estructura `Check` y la función `check` privadas por esta versión:

```cpp
// Dentro de la zona privada:

struct Check {
    bool ok;
    int npl;
    std::size_t count;
};

Check check(Node* u) const {
    if (!u) {
        return {true, 0, 0};
    }

    const Check l = check(u->left);
    const Check r = check(u->right);

    // MOD-A6-B8: propiedad heap para max-heap segun el comparador.
    const bool heapOk =
        (!u->left || !comp_(u->value, u->left->value)) &&
        (!u->right || !comp_(u->value, u->right->value));

    // MOD-A6-B8: propiedad izquierdista.
    const bool leftistOk = l.npl >= r.npl;

    // MOD-A6-B8: consistencia del npl almacenado.
    const int expectedNpl = r.npl + 1;
    const bool nplOk = u->npl == expectedNpl;

    const std::size_t subtreeCount = 1 + l.count + r.count;

    return {
        l.ok && r.ok && heapOk && leftistOk && nplOk,
        expectedNpl,
        subtreeCount
    };
}
```

Con esto se valida:

| Requisito del bloque   | Dónde se valida      |
| ---------------------- | -------------------- |
| Propiedad heap         | `heapOk`             |
| Propiedad izquierdista | `leftistOk`          |
| Consistencia de tamaño | `result.count == n_` |
| Consistencia de `npl`  | `nplOk`              |


#### 3. Por qué no se debe romper `merge`

La operación actual de fusión hace tres cosas importantes: si una raíz tiene menor prioridad que la otra, intercambia raíces; luego mezcla recursivamente por la derecha; finalmente intercambia hijos si el lado derecho quedó con mayor `npl` que el izquierdo y actualiza `npl`. Esa lógica aparece en `mergeNodes`: compara raíces, fusiona `a->right` con `b`, aplica el intercambio izquierdo/derecho cuando corresponde y recalcula `a->npl`. 

Por eso la validación anterior debe comprobar exactamente esos efectos.


#### 4. Demostración modificada: `demos/demo_left_heap_merge.cpp`

Reemplaza el demo por esta versión. El demo original construye dos heaps, muestra recorridos por niveles, ejecuta `merge`, inserta `10` y luego extrae por prioridad.  Esta versión agrega validación después de cada paso.

```cpp
#include <iostream>
#include <vector>

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
    std::cout << label << ": [";

    for (std::size_t i = 0; i < xs.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }

        std::cout << xs[i];
    }

    std::cout << "]\n";
}

template <typename Heap>
void printValidation(const Heap& heap, const char* label) {
    std::cout << label
              << " | size=" << heap.size()
              << " | valido=" << std::boolalpha
              << heap.isValidLeftHeap()
              << "\n";
}

} // namespace

int main() {
    ods::PQ_LeftHeap<int> a{7, 2, 9};
    ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

    std::cout << "Bloque 8 - Heap izquierdista y validacion de merge\n\n";

    printVector(a.levelOrder(), "heap A antes del merge");
    printValidation(a, "validacion A");

    printVector(b.levelOrder(), "heap B antes del merge");
    printValidation(b, "validacion B");

    std::cout << "\nEjecutando A.merge(B)\n";
    a.merge(b);

    printVector(a.levelOrder(), "heap A despues del merge");
    printValidation(a, "validacion A despues del merge");

    std::cout << "B queda vacio: " << std::boolalpha << b.empty() << "\n";
    std::cout << "size de B: " << b.size() << "\n";
    printValidation(b, "validacion B despues del merge");

    std::cout << "\nEjecutando A.insert(10)\n";
    a.insert(10);

    printVector(a.levelOrder(), "A despues de insert(10)");
    printValidation(a, "validacion A despues de insert(10)");

    std::cout << "\nExtracciones con delMax: ";
    while (!a.empty()) {
        const int value = a.delMax();
        std::cout << value << ' ';

        if (!a.isValidLeftHeap()) {
            std::cout << "\nError: heap izquierdista invalido despues de delMax\n";
            return 1;
        }
    }

    std::cout << "\n";
    printValidation(a, "validacion A al final");
}
```

#### 5. Salida esperada

Con la lógica actual de `mergeNodes`, una salida esperada es:

```text
Bloque 8 - Heap izquierdista y validacion de merge

heap A antes del merge: [9, 7, 2]
validacion A | size=3 | valido=true
heap B antes del merge: [11, 8, 1, 3]
validacion B | size=4 | valido=true

Ejecutando A.merge(B)
heap A despues del merge: [11, 8, 9, 1, 3, 7, 2]
validacion A despues del merge | size=7 | valido=true
B queda vacio: true
size de B: 0
validacion B despues del merge | size=0 | valido=true

Ejecutando A.insert(10)
A despues de insert(10): [11, 8, 10, 1, 3, 9, 7, 2]
validacion A despues de insert(10) | size=8 | valido=true

Extracciones con delMax: 11 10 9 8 7 3 2 1
validacion A al final | size=0 | valido=true
```

La forma exacta del recorrido por niveles puede variar si cambia el criterio de empate o la forma de inserción, pero la secuencia de `delMax` debe salir en orden no creciente para `std::less<int>`.

#### 6. Pruebas sugeridas

Agrega estas pruebas en `pruebas_publicas/test_public_week6.cpp` o en `pruebas_internas/test_internal_week6.cpp`.

```cpp
static void testBloque8LeftHeapValidacionMerge() {
    ods::PQ_LeftHeap<int> a{7, 2, 9};
    ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

    assert(a.isValidLeftHeap());
    assert(b.isValidLeftHeap());
    assert(a.size() == 3);
    assert(b.size() == 4);

    a.merge(b);

    assert(a.isValidLeftHeap());
    assert(b.isValidLeftHeap());
    assert(a.size() == 7);
    assert(b.size() == 0);
    assert(b.empty());
    assert(a.getMax() == 11);

    a.insert(10);
    assert(a.isValidLeftHeap());
    assert(a.size() == 8);
    assert(a.getMax() == 11);

    int previous = a.delMax();
    assert(previous == 11);
    assert(a.isValidLeftHeap());

    while (!a.empty()) {
        const int current = a.delMax();
        assert(previous >= current);
        previous = current;
        assert(a.isValidLeftHeap());
    }

    assert(a.empty());
    assert(a.size() == 0);
    assert(a.isValidLeftHeap());
}
```

Llama a la prueba desde `main()`:

```cpp
int main() {
    testBloque8LeftHeapValidacionMerge();

    // Resto de pruebas existentes...
}
```
#### 7. Evidencia de compilación

Desde `Libreria_cc232/Semana6`:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_left_heap_merge
ctest --test-dir build --output-on-failure
```

Salida esperada de pruebas:

```text
100% tests passed, 0 tests failed out of 2
```
#### 8. Trazado de una fusión pequeña

Supongamos:

```text
A = [9, 4]
B = [8, 3, 2]
```

Como es max-heap, la raíz final debe ser `9`.

Paso 1:

```text
merge(9, 8)
```

`9` domina a `8`, entonces `9` queda como raíz.

Paso 2:

```text
9.right = merge(9.right, 8)
```

Si `9.right` era nulo, entonces `8` queda temporalmente como hijo derecho de `9`.

Paso 3:

Se revisa la propiedad izquierdista:

```text
npl(left) >= npl(right)
```

Si el lado derecho tiene mayor `npl` que el izquierdo, se intercambian hijos.

Resultado posible por niveles:

```text
[9, 8, 4, 3, 2]
```

El árbol no busca quedar completo como un heap binario en arreglo. Busca mantener el camino derecho corto para que futuras fusiones sean eficientes.


#### 9. Respuestas del Bloque 8

#### 1. ¿Por qué `merge` es la operación central del heap izquierdista?

Porque casi todo se reduce a mezclar heaps. En un heap izquierdista, no se inserta "subiendo" como en un heap binario completo, ni se elimina "bajando" con índices. La operación básica es fusionar dos árboles que ya cumplen las propiedades.

Por eso:

```text
insert(x) = merge(heap_actual, heap_de_un_solo_nodo_x)
delMax() = merge(subarbol_izquierdo_de_la_raiz, subarbol_derecho_de_la_raiz)
```

El código actual hace justamente eso: `insert` llama a `mergeNodes(root_, new Node(e))`, y `delMax` elimina la raíz y luego asigna `root_ = mergeNodes(a, b)`. 

#### 2. ¿Cómo se implementa `insert` usando `merge`?

Se crea un nodo nuevo que por sí solo ya es un heap izquierdista válido. Luego se fusiona con la raíz actual:

```cpp
void insert(const T& e) override {
    root_ = mergeNodes(root_, new Node(e));
    ++n_;
}
```

Conceptualmente:

```text
insertar x = mezclar heap actual con heap {x}
```

El costo depende del largo del camino derecho, no de una posición final en arreglo.

#### 3. ¿Cómo se implementa `delMax` usando `merge`?

En un max-heap, el máximo está en la raíz. Para eliminarlo:

1. Se guarda `root_->value`.
2. Se separan `root_->left` y `root_->right`.
3. Se elimina la raíz antigua.
4. Se fusionan los dos subárboles.

Conceptualmente:

```text
delMax() = borrar raiz y hacer merge(left, right)
```

Eso también está implementado en el código actual: después de borrar la raíz, el nuevo `root_` se obtiene mezclando los dos subárboles. 

#### 4. ¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?

El heap binario completo mantiene una **propiedad de forma completa**: todos los niveles están llenos salvo quizá el último, y se representa eficientemente en un vector.

El heap izquierdista no exige ser completo. Su propiedad adicional es:

```text
npl(left) >= npl(right)
```

Esto fuerza que el camino derecho sea corto. Por eso se adapta mejor a `merge`.

#### 5. ¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?

La ventaja conceptual es que el heap izquierdista tiene `merge` como operación natural. En un heap binario completo, fusionar dos heaps no es una operación estructural directa: normalmente tendrías que juntar arreglos y aplicar `heapify`, o insertar los elementos de un heap en otro.

En cambio, en un heap izquierdista:

```text
merge = operación fundamental
insert = caso particular de merge
delMax = otro caso particular de merge
```

Por eso es una estructura muy buena para estudiar **heaps mezclables**.

#### 10. Complejidad

| Operación         |                                                     Heap izquierdista |
| ----------------- | --------------------------------------------------------------------: |
| `getMax`          |                                                                `O(1)` |
| `merge`           | `O(log n)` esperado/garantizado por la propiedad izquierdista clásica |
| `insert`          |                                         `O(log n)` porque usa `merge` |
| `delMax`          |                            `O(log n)` porque usa `merge(left, right)` |
| `isValidLeftHeap` |                                                                `O(n)` |
| `levelOrder`      |                                                                `O(n)` |

La validación cuesta `O(n)` porque recorre todos los nodos. Es adecuada para pruebas, no para ejecutarla después de cada operación en producción.

Con esto el Bloque 8 queda completo: se valida no solo que el árbol "parece funcionar", sino que conserva simultáneamente propiedad heap, propiedad izquierdista, tamaño real y consistencia de `npl`.

#### Bloque 9 - Huffman: desempate y caso de un símbolo

El **Bloque 9** pide trabajar sobre `Huffman_PQ.h`, `Huffman_PQ_generateTree.h` y `demo_huffman.cpp`. El objetivo es modificar o probar explícitamente el **desempate entre símbolos con igual frecuencia**, usar el alfabeto `{A:5, B:5, C:10, D:10, E:20}` y cubrir el caso extremo `{X:100}`. La actividad también exige tabla de códigos y verificación de prefijo libre. 

En el código actual, Huffman ya se construye usando una cola de prioridad: se crea un bosque con símbolos de frecuencia positiva, luego se extraen repetidamente dos nodos, se fusionan y se reinserta el nodo combinado.  Además, el caso de un único símbolo ya está tratado en `huffmanCollectCodes`, porque si el prefijo está vacío asigna `"0"`. 

#### 1. ¿Qué es Huffman y cómo se relaciona con el tema?

La codificación de **Huffman** construye un árbol binario de prefijos para asignar códigos cortos a símbolos frecuentes y códigos más largos a símbolos raros. Cada hoja representa un símbolo. El camino desde la raíz hasta la hoja define su código: normalmente izquierda es `0` y derecha es `1`.

Su relación con Semana 6 es directa:

| Tema de Semana 6 | Relación con Huffman                                                                          |
| ---------------- | --------------------------------------------------------------------------------------------- |
| `PQ`             | Huffman necesita extraer repetidamente los dos nodos de menor frecuencia.                     |
| `PQ_ComplHeap`   | Puede implementar esa cola de prioridad con heap binario completo.                            |
| `PQ_LeftHeap`    | También puede implementar la cola de prioridad con heap izquierdista.                         |
| `merge`          | Conceptualmente, Huffman fusiona dos árboles pequeños en un árbol mayor.                      |
| Árbol binario    | El resultado final es un árbol binario de codificación.                                       |
| Prefijo libre    | Ningún código debe ser prefijo de otro, porque las hojas están al final de caminos completos. |

Por eso Huffman es una aplicación perfecta de colas de prioridad: no se busca una estructura ordenada tipo BST, sino una estructura capaz de entregar siempre los dos pesos mínimos disponibles.

#### 2. Modificación recomendada en `include/Huffman_PQ.h`

El código actual desempata por `symbol` cuando las frecuencias son iguales.  Eso funciona para hojas, pero los nodos internos tienen `symbol = '\0'`, lo que hace menos explícito el criterio cuando empatan nodos internos contra símbolos reales. Para documentar mejor el desempate, conviene agregar un campo `minSymbol`, que representa el menor símbolo contenido en el subárbol.

Modifica `HuffmanNode` así:

```cpp
struct HuffmanNode {
    char symbol{};
    int frequency{};
    char minSymbol{};
    std::shared_ptr<HuffmanNode> left{};
    std::shared_ptr<HuffmanNode> right{};

    HuffmanNode(char s, int f)
        : symbol(s),
          frequency(f),
          minSymbol(s) {}

    HuffmanNode(std::shared_ptr<HuffmanNode> a, std::shared_ptr<HuffmanNode> b)
        : symbol('\0'),
          frequency(a->frequency + b->frequency),
          left(std::move(a)),
          right(std::move(b)) {
        // MOD-A6-B9: desempate determinista para nodos internos.
        // El subarbol se identifica por el menor simbolo que contiene.
        minSymbol = std::min(left->minSymbol, right->minSymbol);
    }

    bool leaf() const noexcept {
        return !left && !right;
    }
};
```

Luego modifica el comparador:

```cpp
struct HuffmanLowerFrequencyFirst {
    bool operator()(const std::shared_ptr<HuffmanNode>& a,
                    const std::shared_ptr<HuffmanNode>& b) const {
        if (a->frequency != b->frequency) {
            // MOD-A6-B9: menor frecuencia tiene mayor prioridad.
            return a->frequency > b->frequency;
        }

        // MOD-A6-B9: si hay empate, gana el subarbol cuyo menor simbolo
        // sea lexicograficamente menor. Ejemplo: A antes que B.
        return static_cast<unsigned char>(a->minSymbol) >
               static_cast<unsigned char>(b->minSymbol);
    }
};
```

También puedes hacer más clara la traza de nodos internos:

```cpp
inline std::string huffmanNodeLabel(const std::shared_ptr<HuffmanNode>& u) {
    if (!u) {
        return "null";
    }

    if (u->leaf()) {
        return std::string(1, u->symbol);
    }

    // MOD-A6-B9: etiqueta visible para documentar el desempate.
    return "*" + std::string(1, u->minSymbol);
}
```

Finalmente, deja explícito el caso de un solo símbolo:

```cpp
inline void huffmanCollectCodes(const std::shared_ptr<HuffmanNode>& u,
                                const std::string& prefix,
                                std::unordered_map<char, std::string>& out) {
    if (!u) {
        return;
    }

    if (u->leaf()) {
        // MOD-A6-B9: caso extremo de un solo simbolo.
        // Sin este caso, el codigo quedaria como cadena vacia.
        out[u->symbol] = prefix.empty() ? "0" : prefix;
        return;
    }

    huffmanCollectCodes(u->left, prefix + "0", out);
    huffmanCollectCodes(u->right, prefix + "1", out);
}
```

#### 3. Demostración completa: `demos/demo_huffman.cpp`

Reemplaza el demo por esta versión. El demo original ya imprime fusiones, códigos, codificación, decodificación y prefijo libre.  Esta versión se enfoca en el bloque pedido.

```cpp
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Capitulo6.h"

namespace {

void printTrace(const std::vector<ods::HuffmanBuildStep>& steps) {
    std::cout << "Fusiones durante la construccion:\n";

    for (const auto& s : steps) {
        std::cout << "  (" << s.leftLabel << ':' << s.leftFrequency << ") + "
                  << "(" << s.rightLabel << ':' << s.rightFrequency << ") -> "
                  << s.mergedFrequency << '\n';
    }
}

void printCodeTable(const std::vector<ods::HuffmanSymbol>& alphabet,
                    const std::unordered_map<char, std::string>& codes) {
    std::cout << "\nTabla simbolo, frecuencia, codigo, longitud:\n";
    std::cout << "  simbolo  frecuencia  codigo  longitud\n";

    for (const auto& s : alphabet) {
        const std::string& code = codes.at(s.symbol);

        std::cout << "  " << std::setw(7) << s.symbol
                  << "  " << std::setw(10) << s.frequency
                  << "  " << std::setw(6) << code
                  << "  " << std::setw(8) << code.size()
                  << '\n';
    }
}

} // namespace

int main() {
    const std::vector<ods::HuffmanSymbol> alphabet{
        {'A', 5},
        {'B', 5},
        {'C', 10},
        {'D', 10},
        {'E', 20}
    };

    std::cout << "Bloque 9 - Huffman con desempate determinista\n\n";

    const auto steps = ods::huffmanBuildTrace(alphabet);
    printTrace(steps);

    const auto codes = ods::huffmanGenerateCodes(alphabet);
    const auto tree = ods::huffmanGenerateTree(alphabet);

    printCodeTable(alphabet, codes);

    std::cout << "\nPrefijo libre: "
              << std::boolalpha
              << ods::huffmanIsPrefixFree(codes)
              << '\n';

    std::cout << "Costo ponderado total: "
              << ods::huffmanWeightedPathLength(alphabet, codes)
              << '\n';

    const std::string text = "ABCDE";
    const std::string bits = ods::huffmanEncode(text, codes);
    const std::string decoded = ods::huffmanDecode(bits, tree);

    std::cout << "\nTexto original: " << text << '\n';
    std::cout << "Codificado: " << bits << '\n';
    std::cout << "Decodificado: " << decoded << '\n';

    assert(decoded == text);
    assert(ods::huffmanIsPrefixFree(codes));
    assert(ods::huffmanWeightedPathLength(alphabet, codes) == 110);

    const std::vector<ods::HuffmanSymbol> singleSymbol{{'X', 100}};
    const auto singleCodes = ods::huffmanGenerateCodes(singleSymbol);
    const auto singleTree = ods::huffmanGenerateTree(singleSymbol);

    std::cout << "\nCaso de un solo simbolo:\n";
    std::cout << "  X -> " << singleCodes.at('X') << '\n';

    const std::string singleText = "XXX";
    const std::string singleBits = ods::huffmanEncode(singleText, singleCodes);
    const std::string singleDecoded = ods::huffmanDecode(singleBits, singleTree);

    std::cout << "  texto original: " << singleText << '\n';
    std::cout << "  codificado: " << singleBits << '\n';
    std::cout << "  decodificado: " << singleDecoded << '\n';
    std::cout << "  prefijo libre: "
              << ods::huffmanIsPrefixFree(singleCodes)
              << '\n';

    assert(singleCodes.at('X') == "0");
    assert(singleDecoded == singleText);
    assert(ods::huffmanIsPrefixFree(singleCodes));
}
```

#### 4. Salida esperada

Con el desempate propuesto, una salida esperada es:

```text
Bloque 9 - Huffman con desempate determinista

Fusiones durante la construccion:
  (A:5) + (B:5) -> 10
  (*A:10) + (C:10) -> 20
  (D:10) + (*A:20) -> 30
  (E:20) + (*A:30) -> 50

Tabla simbolo, frecuencia, codigo, longitud:
  simbolo  frecuencia  codigo  longitud
        A           5    1100         4
        B           5    1101         4
        C          10     111         3
        D          10      10         2
        E          20       0         1

Prefijo libre: true
Costo ponderado total: 110

Texto original: ABCDE
Codificado: 11001101111100
Decodificado: ABCDE

Caso de un solo simbolo:
  X -> 0
  texto original: XXX
  codificado: 000
  decodificado: XXX
  prefijo libre: true
```

La forma exacta de los códigos puede variar si cambias el criterio de desempate, pero debe mantenerse la propiedad de prefijo libre y el costo ponderado óptimo para ese conjunto de frecuencias.

#### 5. Prueba pública o interna para agregar

Agrega esta función a `pruebas_publicas/test_public_week6.cpp` o a `pruebas_internas/test_internal_week6.cpp`. Las pruebas existentes ya verifican codificación, decodificación y prefijo libre para el ejemplo clásico `a, b, c, d, e, f`.  También existe una prueba interna que compara el costo ponderado usando heap completo y leftist heap. 

```cpp
static void testBloque9HuffmanDesempateYUnSimbolo() {
    const std::vector<ods::HuffmanSymbol> alphabet{
        {'A', 5},
        {'B', 5},
        {'C', 10},
        {'D', 10},
        {'E', 20}
    };

    const auto codes = ods::huffmanGenerateCodes(alphabet);
    const auto tree = ods::huffmanGenerateTree(alphabet);

    assert(ods::huffmanIsPrefixFree(codes));
    assert(ods::huffmanWeightedPathLength(alphabet, codes) == 110);

    // MOD-A6-B9: estos codigos documentan el desempate elegido.
    assert(codes.at('A') == "1100");
    assert(codes.at('B') == "1101");
    assert(codes.at('C') == "111");
    assert(codes.at('D') == "10");
    assert(codes.at('E') == "0");

    const std::string text = "ABCDE";
    const std::string bits = ods::huffmanEncode(text, codes);
    assert(ods::huffmanDecode(bits, tree) == text);

    const std::vector<ods::HuffmanSymbol> singleSymbol{{'X', 100}};
    const auto singleCodes = ods::huffmanGenerateCodes(singleSymbol);
    const auto singleTree = ods::huffmanGenerateTree(singleSymbol);

    assert(singleCodes.size() == 1);
    assert(singleCodes.at('X') == "0");
    assert(ods::huffmanIsPrefixFree(singleCodes));

    const std::string repeated = "XXX";
    const std::string encoded = ods::huffmanEncode(repeated, singleCodes);
    assert(encoded == "000");
    assert(ods::huffmanDecode(encoded, singleTree) == repeated);
}
```

Luego llama la función dentro de `main()`:

```cpp
int main() {
    testBloque9HuffmanDesempateYUnSimbolo();

    // Resto de pruebas existentes...
}
```

#### 6. Verificación de prefijo libre

El código ya tiene `huffmanIsPrefixFree`, que compara cada par de códigos y devuelve `false` si uno empieza con el otro.  Para la tabla anterior:

| Símbolo | Frecuencia | Código | Longitud |
| ------- | ---------: | -----: | -------: |
| `A`     |          5 | `1100` |        4 |
| `B`     |          5 | `1101` |        4 |
| `C`     |         10 |  `111` |        3 |
| `D`     |         10 |   `10` |        2 |
| `E`     |         20 |    `0` |        1 |

Verificación conceptual:

* `0` no es prefijo de ningún otro código, porque todos los demás empiezan con `1`.
* `10` no es prefijo de `1100`, `1101` ni `111`.
* `111` no es prefijo de `1100` ni `1101`.
* `1100` y `1101` solo difieren en el último bit.

Por tanto, el conjunto es libre de prefijos.

#### 7. Costo ponderado

El costo ponderado se calcula como:

```text
suma(frecuencia_simbolo * longitud_codigo)
```

Para la tabla:

```text
A: 5  * 4 = 20
B: 5  * 4 = 20
C: 10 * 3 = 30
D: 10 * 2 = 20
E: 20 * 1 = 20
Total = 110
```

El código del repositorio tiene una función `huffmanWeightedPathLength` que hace esa suma para cada símbolo con frecuencia positiva. 

#### 8. Respuestas del Bloque 9

#### 1. ¿Por qué Huffman necesita una cola de prioridad?

Porque en cada paso debe seleccionar los **dos árboles de menor frecuencia**. Una cola de prioridad permite extraer esos mínimos eficientemente. En esta librería se reutiliza `PQ_ComplHeap` y también existe una variante con `PQ_LeftHeap`, lo cual conecta Huffman con las estructuras principales de Semana 6. 

#### 2. ¿Qué elementos se extraen repetidamente?

Se extraen dos nodos raíz del bosque actual. Al inicio esos nodos son hojas, una por símbolo. Después pueden ser nodos internos que representan subárboles ya fusionados.

#### 3. ¿Qué nodo se vuelve a insertar?

Se vuelve a insertar un nodo interno cuya frecuencia es la suma de las dos frecuencias extraídas:

```text
frecuencia_nueva = frecuencia_izquierda + frecuencia_derecha
```

Ese nodo interno representa un árbol parcial de Huffman.

#### 4. ¿Por qué el caso de un solo símbolo requiere cuidado especial?

Porque si solo existe una hoja, el camino desde la raíz hasta esa hoja tiene longitud cero. Sin tratamiento especial, el código del símbolo sería la cadena vacía. Para que la codificación sea práctica y verificable, se asigna un código como `"0"`. El código actual ya implementa esa decisión con `prefix.empty() ? "0" : prefix`. 

#### 5. ¿Qué significa que el conjunto de códigos sea libre de prefijos?

Significa que ningún código completo es prefijo de otro. Por ejemplo, si `A = 0`, no puede existir otro símbolo con código `01` o `011`. Esta propiedad permite decodificar de izquierda a derecha sin separadores.

#### 6. ¿Cómo afecta el desempate a la forma del árbol?

Si dos símbolos o subárboles tienen la misma frecuencia, cualquiera de ellos puede extraerse primero sin violar la estrategia greedy. Sin embargo, el orden elegido cambia qué nodo queda a la izquierda o a la derecha, y por eso puede cambiar los bits exactos de los códigos.

Por ejemplo, con `A:5` y `B:5`, si `A` se toma primero, podría recibir el prefijo `0` dentro de su subárbol, si se toma primero `B`, los bits de ambos podrían invertirse. El costo puede seguir siendo el mismo, pero la tabla de códigos cambia.

#### 7. ¿El desempate cambia necesariamente la longitud total ponderada?

No necesariamente. El desempate puede cambiar la **forma exacta** del árbol y los bits asignados, pero si los empates son entre frecuencias iguales, normalmente no cambia el costo ponderado total. En el ejemplo propuesto, diferentes desempates válidos pueden seguir dando costo `110`, aunque produzcan códigos distintos.

#### 8. Evidencia de compilación

Desde `Libreria_cc232/Semana6`:

```bash
cmake -S . -B build
cmake --build build
./build/sem6_demo_huffman
ctest --test-dir build --output-on-failure
```

Salida esperada de pruebas:

```text
100% tests passed, 0 tests failed out of 2
```
#### Bloque 10 - Treap: rotaciones, invariantes, búsqueda ordenada y pruebas

El **Bloque 10** pide intervenir `Treap.h`, extender `demo_treap_basico.cpp` y agregar pruebas específicas. El punto central es que el `Treap` combina dos invariantes simultáneos: **propiedad BST sobre `key`** y **propiedad heap sobre `priority`**. En la implementación de Semana 6, una prioridad menor sube más cerca de la raíz, por eso `bubbleUp` rota mientras el padre tiene prioridad mayor que el nodo insertado. 

El código actual ya tiene `Node` con `key`, `priority`, `parent`, `left` y `right`, también tiene `findEQ`, `lowerBound`, `upperBound`, `addWithPriority`, `remove`, `rotateLeft`, `rotateRight`, `bubbleUp`, `trickleDown`, `inorderKeys`, `levelOrderKeys`, `asciiArt`, `isBST`, `isHeapByPriority` e `isTreap`. 

#### 1. Explicación técnica del Treap

Un **Treap** es una estructura híbrida:

| Propiedad  | Qué ordena      | Qué garantiza                                                              |
| ---------- | --------------- | -------------------------------------------------------------------------- |
| BST        | `key`           | Búsqueda ordenada, `findEQ`, `lowerBound`, `upperBound`, recorrido inorden |
| Heap       | `priority`      | Las prioridades menores quedan más cerca de la raíz                        |
| Rotaciones | Forma del árbol | Corrigen prioridad sin romper el orden BST                                 |

La clave se usa para decidir izquierda o derecha. La prioridad se usa para decidir quién debe estar arriba. Por eso el recorrido **inorden** siempre debe salir ordenado por claves, aunque las prioridades cambien la forma del árbol.

#### 2. Código modificado en `include/Treap.h`

Agrega estas funciones dentro de la sección `public:` de la clase `Treap`, junto a `addWithPriority` y `remove`.

```cpp
// MOD-A6-B10: insercion instrumentada con prioridad fija.
// Retorna la cantidad de rotaciones hechas por bubbleUp.
std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);

    if (!addNode(u)) {
        delete u;
        return 0;
    }

    return bubbleUpCount(u);
}

// MOD-A6-B10: eliminacion instrumentada.
// Retorna la cantidad de rotaciones hechas por trickleDown.
std::size_t removeCount(const T& x) {
    Node* u = findEQ(x);

    if (!u) {
        return 0;
    }

    const std::size_t rotations = trickleDownCount(u);
    splice(u);
    delete u;

    return rotations;
}

// MOD-A6-B10: validacion explicita de enlaces parent.
bool hasValidParentLinks() const {
    return checkParents(root_, nullptr);
}
```

Ahora reemplaza internamente `bubbleUp` y `trickleDown` por versiones que reutilicen las funciones instrumentadas:

```cpp
// MOD-A6-B10: version instrumentada de bubbleUp.
std::size_t bubbleUpCount(Node* u) {
    std::size_t rotations = 0;

    while (u->parent && u->parent->priority > u->priority) {
        if (u->isRightChild()) {
            rotateLeft(u->parent);
        } else {
            rotateRight(u->parent);
        }

        ++rotations;
    }

    if (!u->parent) {
        root_ = u;
    }

    return rotations;
}

void bubbleUp(Node* u) {
    static_cast<void>(bubbleUpCount(u));
}

// MOD-A6-B10: version instrumentada de trickleDown.
std::size_t trickleDownCount(Node* u) {
    std::size_t rotations = 0;

    while (u->left || u->right) {
        if (!u->left) {
            rotateLeft(u);
        } else if (!u->right) {
            rotateRight(u);
        } else if (u->left->priority < u->right->priority) {
            rotateRight(u);
        } else {
            rotateLeft(u);
        }

        ++rotations;

        if (root_ == u) {
            root_ = u->parent;
        }
    }

    return rotations;
}

void trickleDown(Node* u) {
    static_cast<void>(trickleDownCount(u));
}
```

El comportamiento de `add` y `addWithPriority` no cambia: `addWithPriority` sigue insertando y llamando a `bubbleUp`, `remove` sigue buscando, aplicando `trickleDown`, haciendo `splice` y eliminando el nodo. Eso coincide con la lógica original del archivo. 

#### 3. Parte A - Construcción determinística con prioridades fijas

Reemplaza `demos/demo_treap_basico.cpp` por una versión más completa. La demostración actual ya inserta claves con prioridades fijas y elimina algunos nodos, pero el bloque pide imprimir más evidencia después de cada operación. 

```cpp
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Capitulo6.h"

namespace {

template <class T>
void printVector(const std::vector<T>& xs, const std::string& label) {
    std::cout << label << ": [";

    for (std::size_t i = 0; i < xs.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }

        std::cout << xs[i];
    }

    std::cout << "]\n";
}

void printState(const ods::Treap<int>& t, const std::string& label) {
    std::cout << "\n" << label << "\n";

    printVector(t.inorderKeys(), "inorden");
    printVector(t.levelOrderKeys(), "niveles");

    if (t.root()) {
        std::cout << "raiz: " << t.root()->key
                  << " | prioridad: " << t.root()->priority << "\n";
    } else {
        std::cout << "raiz: null\n";
    }

    std::cout << "isBST: " << std::boolalpha << t.isBST() << "\n";
    std::cout << "isHeapByPriority: " << t.isHeapByPriority() << "\n";
    std::cout << "isTreap: " << t.isTreap() << "\n";
    std::cout << "parent_links: " << t.hasValidParentLinks() << "\n";
}

void printSearchResult(const std::string& name, const ods::Treap<int>::Node* node) {
    std::cout << name << ": ";

    if (node) {
        std::cout << node->key << " | prioridad=" << node->priority << "\n";
    } else {
        std::cout << "null\n";
    }
}

} // namespace

int main() {
    ods::Treap<int> t(232);

    const std::vector<std::pair<int, std::uint64_t>> fixed{
        {50, 50}, {30, 30}, {70, 70},
        {20, 20}, {40, 40}, {60, 60}, {80, 80}
    };

    std::cout << "Bloque 10 - Parte A: Treap con prioridades fijas\n";

    for (const auto& [key, priority] : fixed) {
        t.addWithPriority(key, priority);

        std::cout << "\ninsertada clave=" << key
                  << " prioridad=" << priority << "\n";

        printState(t, "estado despues de insertar");
    }

    std::cout << "\nArbol final Parte A:\n";
    std::cout << t.asciiArt() << "\n";

    std::cout << "\nBloque 10 - Parte B: bubbleUpCount\n";

    ods::Treap<int> b(232);
    const std::vector<std::pair<int, std::uint64_t>> bubbleSeq{
        {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60}
    };

    for (const auto& [key, priority] : bubbleSeq) {
        const std::size_t rotations = b.addWithPriorityCount(key, priority);

        std::cout << "clave=" << key
                  << " prioridad=" << priority
                  << " rotaciones=" << rotations
                  << " raiz=" << b.root()->key << "\n";

        printVector(b.levelOrderKeys(), "niveles");
    }

    std::cout << "\nBloque 10 - Parte C: trickleDownCount y removeCount\n";

    ods::Treap<int> c(232);
    for (const auto& [key, priority] : fixed) {
        c.addWithPriority(key, priority);
    }

    for (int key : {50, 20, 70}) {
        const std::size_t rotations = c.removeCount(key);

        std::cout << "\neliminada clave=" << key
                  << " rotaciones=" << rotations << "\n";

        printState(c, "estado despues de eliminar");
    }

    std::cout << "\nBloque 10 - Parte D: busqueda ordenada\n";

    ods::Treap<int> d(232);
    for (const auto& [key, priority] : fixed) {
        d.addWithPriority(key, priority);
    }

    printSearchResult("findEQ(40)", d.findEQ(40));
    printSearchResult("findEQ(35)", d.findEQ(35));
    printSearchResult("lowerBound(35)", d.lowerBound(35));
    printSearchResult("lowerBound(40)", d.lowerBound(40));
    printSearchResult("upperBound(40)", d.upperBound(40));
    printSearchResult("upperBound(75)", d.upperBound(75));

    return 0;
}
```

#### 4. Salida esperada de la Parte A

Con la secuencia:

```cpp
{ {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80} }
```

la forma esperada es una cadena hacia la derecha, porque las claves aumentan hacia la derecha y las prioridades también aumentan. Como prioridad menor significa subir, el nodo `20` termina como raíz.

Tabla resumida:

| Insertado | Prioridad | Raíz | Inorden                        | Niveles                        |
| --------: | --------: | ---: | ------------------------------ | ------------------------------ |
|        50 |        50 |   50 | `[50]`                         | `[50]`                         |
|        30 |        30 |   30 | `[30, 50]`                     | `[30, 50]`                     |
|        70 |        70 |   30 | `[30, 50, 70]`                 | `[30, 50, 70]`                 |
|        20 |        20 |   20 | `[20, 30, 50, 70]`             | `[20, 30, 50, 70]`             |
|        40 |        40 |   20 | `[20, 30, 40, 50, 70]`         | `[20, 30, 40, 50, 70]`         |
|        60 |        60 |   20 | `[20, 30, 40, 50, 60, 70]`     | `[20, 30, 40, 50, 60, 70]`     |
|        80 |        80 |   20 | `[20, 30, 40, 50, 60, 70, 80]` | `[20, 30, 40, 50, 60, 70, 80]` |

Dibujo final aproximado:

```text
│                       ┌── 80|p=80
│                   ┌── 70|p=70
│               ┌── 60|p=60
│           ┌── 50|p=50
│       ┌── 40|p=40
│   ┌── 30|p=30
└── 20|p=20
```

El recorrido inorden sale ordenado porque las rotaciones preservan la relación BST. La raíz no necesariamente es la primera clave insertada; termina siendo el nodo con prioridad menor que logra subir mediante `bubbleUp`.

#### 5. Parte B - Instrumentación de `bubbleUp`

`bubbleUp` se ejecuta después de insertar el nodo como en un BST. Si el nodo tiene prioridad menor que su padre, rota con el padre. Si el nodo es hijo derecho, aplica rotación izquierda sobre el padre; si es hijo izquierdo, aplica rotación derecha sobre el padre. Esa lógica ya existe en el código original. 

Secuencia solicitada:

```cpp
{ {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60} }
```

Tabla esperada:

| Clave | Prioridad | Rotaciones | Raíz después de insertar | Niveles                 |
| ----: | --------: | ---------: | -----------------------: | ----------------------- |
|   100 |       100 |          0 |                      100 | `[100]`                 |
|    90 |        90 |          1 |                       90 | `[90, 100]`             |
|    80 |        80 |          1 |                       80 | `[80, 90, 100]`         |
|    70 |        70 |          1 |                       70 | `[70, 80, 90, 100]`     |
|    60 |        60 |          1 |                       60 | `[60, 70, 80, 90, 100]` |

Esta secuencia produce rotaciones repetidas porque cada nuevo nodo tiene prioridad menor que su padre inmediato. En esta forma concreta, cada nuevo nodo se inserta como hijo izquierdo de la raíz actual y sube una vez. En otros casos, si se inserta profundo y su prioridad es menor que la de varios ancestros, puede subir varios niveles.

Respuestas de la Parte B:

1. **¿Por qué esta secuencia tiende a producir rotaciones repetidas?**
   Porque cada nuevo nodo tiene una prioridad menor que la prioridad de su padre. Eso viola la propiedad heap por prioridad y obliga a `bubbleUp`.

2. **¿Cuándo `bubbleUpCount` retorna cero?**
   Retorna cero cuando el nodo insertado queda como raíz o cuando su padre ya tiene prioridad menor o igual.

3. **¿Cuál es el peor caso de rotaciones durante una inserción?**
   En una inserción individual puede haber tantas rotaciones como altura tenga el árbol, es decir `O(h)`. En un treap con prioridades aleatorias, la altura esperada es `O(log n)`, pero no está garantizada determinísticamente.

4. **¿Por qué una rotación no rompe la propiedad BST?**
   Porque solo cambia relaciones locales padre-hijo conservando los rangos de claves. En una rotación izquierda sobre `u`, el hijo derecho `w` sube, `u` pasa a la izquierda de `w`, y el subárbol intermedio conserva claves mayores que `u` y menores que `w`.

5. **¿Por qué el treap busca altura esperada logarítmica, no garantizada?**
   Porque su balance depende de prioridades aleatorias o asignadas. Si las prioridades se comportan como una permutación aleatoria, la forma esperada es buena. Pero si las prioridades son adversarias, puede degenerar.

#### 6. Parte C - `trickleDown`, eliminación y `splice`

La eliminación en Treap no debe borrar directamente un nodo con dos hijos, porque podría romper el invariante heap por prioridad. El código original primero encuentra el nodo, luego aplica `trickleDown`, después hace `splice` y finalmente elimina el nodo. 

La idea es:

1. Buscar el nodo por clave, como en BST.
2. Rotarlo hacia abajo con `trickleDown`.
3. En cada paso, rotar con el hijo de menor prioridad.
4. Cuando tiene a lo más un hijo, retirarlo con `splice`.
5. Verificar `isBST`, `isHeapByPriority` e `isTreap`.

Usando el treap de la Parte A y eliminando `50`, `20`, `70`, se espera:

| Eliminado | Rotaciones | Inorden después            | Niveles después            | Raíz |
| --------: | ---------: | -------------------------- | -------------------------- | ---: |
|        50 |          1 | `[20, 30, 40, 60, 70, 80]` | `[20, 30, 40, 60, 70, 80]` |   20 |
|        20 |          1 | `[30, 40, 60, 70, 80]`     | `[30, 40, 60, 70, 80]`     |   30 |
|        70 |          1 | `[30, 40, 60, 80]`         | `[30, 40, 60, 80]`         |   30 |

Trazado manual de eliminar `50`:

Antes de eliminar, alrededor del nodo `50` se tiene:

```text
40
  \
   50
     \
      60
        \
         70
           \
            80
```

Como `50` tiene hijo derecho y no tiene hijo izquierdo, `trickleDown(50)` aplica una rotación izquierda sobre `50`. Entonces `60` sube y `50` baja a la izquierda de `60`. Ahora `50` queda sin hijos y puede retirarse con `splice`.

Después:

```text
40
  \
   60
     \
      70
        \
         80
```

Respuestas de la Parte C:

1. **¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?**
   Porque además de mantener el orden por clave, se debe conservar la propiedad heap por prioridad. Borrar directamente un nodo con dos hijos puede dejar prioridades incorrectas.

2. **¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?**
   Porque en esta implementación la prioridad menor debe estar más arriba. Si el nodo a eliminar baja, debe subir el hijo que mejor respeta la propiedad heap.

3. **¿Qué ocurre si el nodo tiene solo hijo izquierdo?**
   Se aplica rotación derecha. El hijo izquierdo sube y el nodo eliminado baja hacia la derecha.

4. **¿Qué ocurre si el nodo tiene solo hijo derecho?**
   Se aplica rotación izquierda. El hijo derecho sube y el nodo eliminado baja hacia la izquierda.

5. **¿Qué invariantes deben seguir siendo verdaderos después de `splice`?**
   Deben mantenerse el orden BST, la propiedad heap por prioridad, los enlaces `parent` correctos, la raíz correcta y `size()` disminuido exactamente en uno.

#### 7. Parte D - Búsqueda ordenada en Treap

La búsqueda ordenada depende de la propiedad BST, no de la prioridad heap. El código de `lowerBound` y `upperBound` recorre izquierda o derecha comparando claves y guardando un candidato, igual que en un BST. 

Con las claves `{20, 30, 40, 50, 60, 70, 80}`:

| Operación        | Resultado esperado | Explicación            |
| ---------------- | -----------------: | ---------------------- |
| `findEQ(40)`     |               `40` | La clave existe        |
| `findEQ(35)`     |             `null` | La clave no existe     |
| `lowerBound(35)` |               `40` | Primera clave `>= 35`  |
| `lowerBound(40)` |               `40` | La clave exacta existe |
| `upperBound(40)` |               `50` | Primera clave `> 40`   |
| `upperBound(75)` |               `80` | Primera clave `> 75`   |

Comparación Treap vs `BinarySearchTree`:

| Operación       | Treap                                  | BinarySearchTree                                       |
| --------------- | -------------------------------------- | ------------------------------------------------------ |
| `findEQ`        | Usa claves como BST                    | Usa claves                                             |
| `lowerBound`    | Usa orden BST                          | Usa orden BST                                          |
| `upperBound`    | Usa orden BST                          | Usa orden BST                                          |
| Forma del árbol | Depende de prioridades                 | Depende del orden de inserción o del balance si existe |
| Balance         | Esperado si prioridades son aleatorias | No garantizado en BST simple                           |
| Inorden         | Ordenado                               | Ordenado                                               |

Respuestas de la Parte D:

1. **¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?**
   Porque buscan sucesores por clave. La prioridad solo decide la forma vertical, no el orden semántico de las claves.

2. **¿Qué parte del treap se comporta igual que un BST?**
   `findEQ`, `findLast`, `lowerBound`, `upperBound` y el recorrido inorden.

3. **¿Qué parte del treap se comporta como heap?**
   La relación padre-hijo sobre `priority`, validada por `isHeapByPriority`.

4. **¿Por qué el treap no reemplaza directamente a una cola de prioridad si solo quieres extraer máximos o mínimos repetidamente?**
   Porque una cola de prioridad pura, como un heap binario, está optimizada para `getMax` y `delMax`. El Treap guarda orden por clave y prioridad estructural, no está diseñado principalmente para consumir máximos repetidamente.

5. **¿Cuándo sí conviene usar Treap?**
   Cuando se necesita búsqueda ordenada, inserción, eliminación, sucesores, predecesores y balance esperado sin implementar invariantes deterministas más complejos como AVL o Red-Black.

#### 8. Parte E - Pruebas específicas para Treap

Agrega estas pruebas en `pruebas_internas/test_internal_week6.cpp` o en `pruebas_publicas/test_public_week6.cpp`. El bloque pide cubrir treap vacío, prioridades fijas, duplicados, inorden, heap por prioridad, búsquedas, eliminaciones de hoja, nodo con un hijo, nodo con dos hijos, raíz, enlaces `parent`, `size()` e invariantes después de secuencias largas. 

```cpp
static void testBloque10TreapCompleto() {
    // MOD-A6-B10: treap vacio.
    ods::Treap<int> empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.isBST());
    assert(empty.isHeapByPriority());
    assert(empty.isTreap());
    assert(empty.hasValidParentLinks());

    // MOD-A6-B10: insercion con prioridades fijas.
    ods::Treap<int> t(232);

    assert(t.addWithPriority(50, 50));
    assert(t.addWithPriority(30, 30));
    assert(t.addWithPriority(70, 70));
    assert(t.addWithPriority(20, 20));
    assert(t.addWithPriority(40, 40));
    assert(t.addWithPriority(60, 60));
    assert(t.addWithPriority(80, 80));

    assert(t.size() == 7);
    assert(t.root() != nullptr);
    assert(t.root()->key == 20);
    assert(t.isBST());
    assert(t.isHeapByPriority());
    assert(t.isTreap());
    assert(t.hasValidParentLinks());

    // MOD-A6-B10: rechazo de duplicados.
    assert(!t.addWithPriority(40, 5));
    assert(t.size() == 7);
    assert(t.isTreap());

    // MOD-A6-B10: inorden ordenado.
    assert((t.inorderKeys() == std::vector<int>{20, 30, 40, 50, 60, 70, 80}));

    // MOD-A6-B10: lowerBound y upperBound.
    assert(t.findEQ(40) != nullptr);
    assert(t.findEQ(35) == nullptr);

    assert(t.lowerBound(35) != nullptr);
    assert(t.lowerBound(35)->key == 40);

    assert(t.lowerBound(40) != nullptr);
    assert(t.lowerBound(40)->key == 40);

    assert(t.upperBound(40) != nullptr);
    assert(t.upperBound(40)->key == 50);

    assert(t.upperBound(75) != nullptr);
    assert(t.upperBound(75)->key == 80);

    assert(t.upperBound(80) == nullptr);

    // MOD-A6-B10: eliminacion de hoja.
    assert(t.remove(80));
    assert(t.size() == 6);
    assert(t.isTreap());
    assert(t.hasValidParentLinks());
    assert((t.inorderKeys() == std::vector<int>{20, 30, 40, 50, 60, 70}));

    // MOD-A6-B10: eliminacion de nodo con un hijo.
    assert(t.remove(70));
    assert(t.size() == 5);
    assert(t.isTreap());
    assert(t.hasValidParentLinks());
    assert((t.inorderKeys() == std::vector<int>{20, 30, 40, 50, 60}));

    // MOD-A6-B10: reconstruccion para eliminar nodo con dos hijos.
    ods::Treap<int> twoChildren(232);
    assert(twoChildren.addWithPriority(50, 50));
    assert(twoChildren.addWithPriority(30, 30));
    assert(twoChildren.addWithPriority(70, 70));
    assert(twoChildren.addWithPriority(20, 20));
    assert(twoChildren.addWithPriority(40, 40));
    assert(twoChildren.addWithPriority(60, 60));
    assert(twoChildren.addWithPriority(80, 80));

    assert(twoChildren.remove(30));
    assert(twoChildren.size() == 6);
    assert(twoChildren.isTreap());
    assert(twoChildren.hasValidParentLinks());
    assert((twoChildren.inorderKeys() == std::vector<int>{20, 40, 50, 60, 70, 80}));

    // MOD-A6-B10: eliminacion de raiz.
    assert(twoChildren.root() != nullptr);
    const int oldRoot = twoChildren.root()->key;
    assert(twoChildren.remove(oldRoot));
    assert(twoChildren.size() == 5);
    assert(twoChildren.isTreap());
    assert(twoChildren.hasValidParentLinks());

    // MOD-A6-B10: operaciones mixtas e invariantes.
    ods::Treap<int> mixed(232);

    for (const auto& item : std::vector<std::pair<int, std::uint64_t>>{
             {100, 100}, {50, 50}, {150, 150}, {25, 25}, {75, 75},
             {125, 125}, {175, 175}, {60, 60}, {90, 90}}) {
        assert(mixed.addWithPriority(item.first, item.second));
        assert(mixed.isTreap());
        assert(mixed.hasValidParentLinks());
    }

    assert(mixed.size() == 9);

    for (int x : {75, 25, 150, 100}) {
        assert(mixed.remove(x));
        assert(mixed.isTreap());
        assert(mixed.hasValidParentLinks());
    }

    assert(mixed.size() == 5);
    assert((mixed.inorderKeys() == std::vector<int>{50, 60, 90, 125, 175}));
}
```

Llama la prueba desde `main()`:

```cpp
int main() {
    testBloque10TreapCompleto();

    // Resto de pruebas existentes...
}
```
#### 9. Respuestas de la Parte E

1. **¿Qué bug atraparía una prueba de enlaces `parent`?**
   Atraparía rotaciones que actualizan `left` y `right`, pero olvidan corregir `parent`. Ese bug suele aparecer después de `rotateLeft`, `rotateRight`, `trickleDown` o `splice`.

2. **¿Qué bug atraparía una prueba de `size()`?**
   Detectaría incrementos dobles al insertar, decrementos faltantes al eliminar o cambios de tamaño después de rechazar duplicados.

3. **¿Qué bug atraparía una prueba de inorden ordenado?**
   Detectaría errores en inserción BST o rotaciones que mueven subárboles al lado incorrecto.

4. **¿Qué bug atraparía una prueba de prioridad padre-hijo?**
   Detectaría fallas en `bubbleUp`, errores al elegir el hijo en `trickleDown` o rotaciones incompletas que dejan un hijo con prioridad menor que su padre.

5. **¿Por qué conviene usar prioridades fijas en pruebas unitarias?**
   Porque hacen que el árbol final sea determinístico. Así se puede afirmar la raíz, el recorrido por niveles, el número de rotaciones y el resultado de eliminaciones sin depender del generador aleatorio.

El Treap no es solo "un BST con prioridades". Su operación real depende de rotaciones cuidadosamente controladas. En inserción, primero se respeta el orden BST y luego `bubbleUp` restaura prioridad. En eliminación, primero se ubica por clave, luego `trickleDown` baja el nodo hasta hacerlo fácil de retirar y finalmente `splice` conserva enlaces y tamaño. Las búsquedas ordenadas (`findEQ`, `lowerBound`, `upperBound`) siguen siendo búsquedas BST; las prioridades solo dan balance probabilístico. 

Por eso el Treap conecta directamente Semana 5, donde aparecen BST y rotaciones, con Semana 6, donde se estudia prioridad, y prepara la comparación con AVL y Red-Black, donde el balance ya no depende del azar sino de invariantes deterministas.
