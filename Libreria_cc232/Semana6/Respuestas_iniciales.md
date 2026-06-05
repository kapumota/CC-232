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

El `CMakeLists.txt` ya define una función auxiliar `cc232_add_sem6_target` para crear ejecutables de demos y enlazarlos con los headers de Semana 6.  Agrega esta línea junto a las otras demostraciones:

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



