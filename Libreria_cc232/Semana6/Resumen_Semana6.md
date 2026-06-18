### Resumen final - Semana 6

#### Colas de prioridad, heaps, Huffman y Treap

La Semana 6 continúa el trabajo de la Semana 5. En la Semana 5 se estudiaron árboles binarios, árboles binarios de búsqueda, recorridos, eliminación,sucesores y rotaciones. 
La Semana 6 toma esa base y la orienta hacia una idea nueva: la prioridad.

Una estructura con prioridad no se organiza solo por posición, como una pila o una cola ordinaria, ni solo por clave de búsqueda, como un árbol binario de búsqueda. 
Su objetivo principal es permitir que el elemento más importante, urgente, grande, pequeño o costoso, según el criterio del problema, pueda obtenerse de manera eficiente.

La semana separa tres conceptos que suelen confundirse:

1. Una cola de prioridad es un ADT.
2. Un heap es una representación eficiente para implementar ese ADT.
3. Un Treap es un árbol de búsqueda que usa prioridades aleatorias para mantener buen comportamiento esperado.

Una cola de prioridad define qué operaciones se ofrecen. Un heap define cómo se almacenan los datos para que esas operaciones sean eficientes. 
Un Treap reutiliza la idea de prioridad, pero no para extraer el máximo o el mínimo, sino para evitar que un árbol binario de búsqueda se degrade.

El material de Semana 6 conecta código, teoría y aplicaciones. En el código aparecen `PQ`, `PQ_ComplHeap`, `PQ_LeftHeap`, `Huffman_PQ`, `MeldableHeap` y `Treap`. 
En las lecturas aparecen la cola de prioridad de Deng, el heap binario completo, el algoritmo de Floyd, heapsort, el heap izquierdista, el BinaryHeap de Morin, el MeldableHeap aleatorizado y el análisis de Treaps mediante árboles binarios de búsqueda aleatorios.

#### 1. Cola de prioridad: idea central

Una cola de prioridad es una estructura de datos que almacena elementos comparables mediante algún criterio de prioridad. A diferencia de una cola FIFO, donde se atiende primero al elemento más antiguo, en una cola de prioridad se atiende primero al elemento con mayor
o menor prioridad, según la convención escogida.

En un hospital, por ejemplo, no siempre debe atenderse primero al paciente que llegó antes. Un caso crítico puede tener prioridad mayor. En un planificador de tareas, una tarea urgente puede ejecutarse antes que una tarea antigua. 
En Huffman, los símbolos o árboles de menor frecuencia deben seleccionarse repetidamente. En algoritmos de grafos como Dijkstra, se extrae repetidamente el vértice con menor distancia tentativa.

La interfaz básica de una cola de prioridad contiene:

| Operación | Significado |
|---|---|
| `size()` | Devuelve el número de elementos almacenados. |
| `empty()` | Indica si la estructura está vacía. |
| `insert(e)` | Inserta un elemento con su prioridad implícita o explícita. |
| `getMax()` | Consulta el elemento de mayor prioridad sin eliminarlo. |
| `delMax()` | Elimina y devuelve el elemento de mayor prioridad. |

La implementación de Semana 6 usa una convención de max-heap en `PQ_ComplHeap`: la raíz contiene el máximo según el comparador. Morin presenta el `BinaryHeap` principalmente como min-heap: la raíz contiene el mínimo. Ambas versiones son equivalentes conceptualmente. 
Basta invertir el comparador para cambiar entre máximo y mínimo.

Lo importante es que una cola de prioridad no necesita mantener todos los elementos ordenados. Solo necesita garantizar que el elemento extremo esté disponible de forma rápida. 
Esta es la diferencia entre mantener un orden total y mantener un orden parcial.

#### 2. Orden total frente a orden parcial

Una lista ordenada mantiene una relación completa entre todos los elementos. Esto permite encontrar el mínimo o el máximo rápidamente, pero puede volver costosa cada inserción.

Una lista no ordenada hace lo contrario: insertar es fácil, pero encontrar el máximo o el mínimo puede requerir recorrer todos los elementos.

El heap adopta una solución intermedia. No exige que el arreglo interno esté completamente ordenado. Exige solo una propiedad local: cada padre debe dominar a sus hijos.

En un max-heap:

```text
prioridad(parent(i)) >= prioridad(i)
```

En un min-heap:

```text
prioridad(parent(i)) <= prioridad(i)
```

La consecuencia global es que la raíz contiene el extremo de prioridad. En un max-heap, la raíz contiene el máximo. En un min-heap, la raíz contiene el mínimo.

Por eso el arreglo interno de un heap no se debe leer como un arreglo ordenado. Puede ocurrir que un hijo izquierdo y un hijo derecho no estén ordenados entre sí. 
También puede ocurrir que valores ubicados en distintos subárboles no tengan una relación directa. El heap solo garantiza la relación padre-hijo, no el orden entre todos los pares.

Esta es una lección de diseño de estructuras de datos: mantener menos información puede hacer la estructura más eficiente si esa información es exactamente la que la operación necesita.

#### 3. Heap binario completo

El heap binario completo combina dos propiedades:

| Propiedad | Significado |
|---|---|
| Forma completa | El árbol se llena por niveles, de izquierda a derecha. |
| Orden de heap | Cada padre domina a sus hijos según el comparador. |

La forma completa es importante porque garantiza altura `O(log n)`. Si un árbol completo tiene `n` nodos, sus niveles están casi llenos. 
Por tanto, cualquier camino desde una hoja hasta la raíz tiene longitud logarítmica.

Además, un árbol binario completo puede almacenarse de forma compacta en un vector. No se necesitan punteros explícitos a padre, hijo izquierdo o hijo derecho. 
La posición de cada nodo determina sus relaciones.

Si la raíz está en el índice `0`, entonces:

```text
left(i) = 2*i + 1
right(i) = 2*i + 2
parent(i) = floor((i - 1) / 2)
```

Esta representación es conocida como método de Eytzinger. Los nodos se almacenan por niveles. La raíz ocupa la primera posición, luego sus dos hijos, luego los cuatro nodos del siguiente nivel, y así sucesivamente.

La implementación sobre vector tiene ventajas prácticas:

| Ventaja | Explicación |
|---|---|
| Compacidad | No hay punteros por nodo. |
| Localidad de memoria | Los elementos están contiguos o casi contiguos. |
| Acceso directo | Padre e hijos se calculan por índice. |
| Altura controlada | La forma completa impide cadenas largas. |

La desventaja es que la fusión eficiente de dos heaps no es natural. Para fusionar dos heaps completos, una alternativa simple es concatenar elementos y
reconstruir el heap, pero eso no usa una operación local de mezcla como en los heaps izquierdistas o mezclables.

#### 4. `getMax`: acceso inmediato al extremo

En `PQ_ComplHeap`, la operación `getMax()` devuelve el elemento de la raíz. Como la raíz está en la posición `0` del vector, la consulta cuesta `O(1)`.

```text
getMax() = heap[0]
```

Esta operación es la más directa del heap. Toda la estructura está diseñada para que el máximo esté siempre en la raíz. No importa que los demás elementos no estén totalmente ordenados. 
La propiedad de heap basta para asegurar que ningún hijo, nieto o descendiente pueda tener prioridad mayor que la raíz.

Si el heap está vacío, `getMax()` debe tratarse como caso inválido. Una implementación robusta debe lanzar una excepción, retornar un valor opcional o documentar claramente su precondición.

La defensa técnica de `getMax()` debe mencionar tres ideas:

1. La raíz está en el índice `0`.
2. La propiedad de heap garantiza que la raíz domina a todos los descendientes.
3. No se modifica la estructura, por eso la operación es constante.

#### 5. Inserción y `percolateUp`

Para insertar un elemento en un heap binario completo, primero se agrega al final del vector. 
Esto conserva la forma completa, porque el nuevo nodo ocupa la siguiente posición disponible del árbol.

Sin embargo, el nuevo elemento puede violar la propiedad de heap. En un max-heap, si el nuevo elemento tiene mayor prioridad que su padre, debe subir.

El algoritmo se llama `percolateUp`, filtrado hacia arriba o burbujeo hacia arriba.

```text
insert(x):
    agregar x al final del vector
    i = posición de x
    mientras i no sea la raíz y heap[i] domine a heap[parent(i)]:
        intercambiar heap[i] con heap[parent(i)]
        i = parent(i)
```

Cada intercambio sube el elemento un nivel. Como la altura del heap completo es `O(log n)`, el peor caso de `insert()` es `O(log n)`.

El caso mejor ocurre cuando el nuevo elemento no domina a su padre. Entonces no hay intercambios y la reparación es `O(1)` después de insertar al final.

El arreglo resultante no queda ordenado. Solo queda garantizada la propiedad padre-hijo. Esta diferencia debe ser defendida con claridad porque muchos
errores de estudiante vienen de esperar que un heap sea un arreglo ordenado.

#### 6. Eliminación del máximo y `percolateDown`

La operación `delMax()` elimina la raíz. El problema es que, si se elimina directamente el primer elemento del vector, se rompe la forma completa. 
Para conservarla, se reemplaza la raíz con el último elemento del vector y se reduce el tamaño lógico del heap.

Luego debe repararse la propiedad de heap. El elemento colocado en la raíz probablemente no sea mayor que sus hijos. Por eso debe bajar.

El algoritmo se llama `percolateDown`, filtrado hacia abajo o hundimiento.

```text
delMax():
    guardar heap[0] como respuesta
    mover el último elemento a heap[0]
    eliminar la última posición
    percolateDown(0)
    devolver la respuesta
```

El filtrado hacia abajo funciona así:

```text
percolateDown(i):
    mientras i tenga al menos un hijo:
        elegir el hijo de mayor prioridad
        si heap[i] domina a ese hijo:
            detener
        intercambiar heap[i] con ese hijo
        i = posición del hijo
```

La elección del hijo dominante es esencial. En un max-heap, si ambos hijos existen, se elige el mayor. Si solo existe el hijo izquierdo, se compara con ese hijo.
En un árbol completo, no puede existir hijo derecho sin hijo izquierdo.

Cada intercambio baja un nivel. Por tanto, el costo de `delMax()` es `O(log n)`.

#### 7. Validación de la propiedad heap

Una función de validación revisa que el arreglo interno cumpla la propiedad de heap. Para cada posición `i`, se calculan sus hijos, si existen, y se 
verifica que el padre domine a cada hijo.

```text
complHeapIsValid(a):
    para cada índice i:
        si left(i) existe y a[left(i)] domina a a[i]:
            fallar
        si right(i) existe y a[right(i)] domina a a[i]:
            fallar
    aceptar
```

Esta validación es útil para pruebas y para depuración. Si `percolateUp` falla, probablemente aparezca una violación entre un nodo insertado y su padre. 
Si `percolateDown` falla, probablemente aparezca una violación entre un nodo bajado y uno de sus hijos.

Una versión más informativa puede devolver el primer par `(parent, child)` que viola la propiedad. Esto permite explicar con precisión dónde se rompió el invariante.

Casos borde importantes:

| Caso | Qué debe ocurrir |
|---|---|
| Heap vacío | Es válido. |
| Heap con un elemento | Es válido. |
| Valores repetidos | Son válidos si el comparador permite igualdad. |
| Nodo con solo hijo izquierdo | Se compara únicamente con ese hijo. |
| Hijo derecho sin izquierdo | No debe aparecer en un heap completo válido. |

La complejidad de validar todo el heap es `O(n)`, porque cada nodo se examina una cantidad constante de veces.

#### 8. Construcción de heap con Floyd

Una forma sencilla de construir un heap desde un conjunto de `n` elementos consiste en insertar cada elemento en un heap inicialmente vacío. 
Si cada inserción cuesta `O(log n)`, la construcción completa cuesta `O(n log n)`.

El algoritmo de Floyd mejora esta construcción. La idea es colocar todos los elementos en el vector y luego reparar desde los últimos nodos internos hacia 
la raíz.

```text
heapifyFloyd(a):
    para i desde lastInternal(n) hasta 0:
        percolateDown(a, n, i)
```

La razón por la que este algoritmo cuesta `O(n)` no es obvia al inicio. Aunque `percolateDown` puede costar `O(log n)` en la raíz, la mayoría de nodos están cerca de las hojas y tienen altura pequeña. 
Muchos nodos no necesitan bajar nada o bajan muy poco.

Por tanto, la suma de las alturas de todos los nodos internos en un árbol completo es lineal. Floyd aprovecha la forma del árbol para construir el heap 
en tiempo óptimo.

Esta diferencia es importante:

| Método | Estrategia | Costo |
|---|---|---|
| Inserciones sucesivas | Insertar uno por uno y subir | `O(n log n)` |
| Floyd | Reparar nodos internos de abajo hacia arriba | `O(n)` |

En la Semana 6, `PQ_ComplHeap_heapifyFloyd.h` representa esta idea. Los ejercicios piden construir desde rango usando Floyd y no por inserciones sucesivas.

#### 9. Heapsort

Heapsort reutiliza el heap binario completo para ordenar un vector. Se basa en dos fases:

1. Convertir el vector en heap.
2. Extraer repetidamente el máximo y colocarlo en su posición final.

Para un max-heap, el máximo está en la raíz. Se intercambia con el último elemento de la zona no ordenada. Luego se reduce el tamaño lógico del heap y se
aplica `percolateDown` en la raíz para restaurar el heap.

```text
heapSort(a):
    construir max-heap con Floyd
    heapSize = n
    mientras heapSize > 1:
        intercambiar a[0] con a[heapSize - 1]
        heapSize--
        percolateDown(a, heapSize, 0)
```

Después de cada extracción, la parte final del vector queda ordenada. La parte inicial sigue siendo el heap activo.

El costo total es `O(n log n)`. La construcción inicial cuesta `O(n)`, pero luego se hacen `n` extracciones, cada una con costo `O(log n)`. 
El espacio auxiliar es `O(1)` si se ordena dentro del mismo vector.

Heapsort no es estable por defecto. Si dos elementos tienen la misma prioridad, su orden relativo puede cambiar. Esto importa cuando se ordenan objetos, por ejemplo estudiantes con la misma nota. 
Para estabilidad se necesita agregar un criterio de desempate, como el orden de llegada, o usar un algoritmo estable.

#### 10. Heap izquierdista

El heap binario completo es excelente para `getMax`, `insert`, `delMax` y heapsort. Sin embargo, no está diseñado para fusionar dos heaps de manera local y 
eficiente.

El heap izquierdista resuelve ese problema. Es un heap basado en nodos, no en un vector completo. Mantiene la propiedad de heap y agrega una propiedad estructural llamada propiedad izquierdista.

La clave del heap izquierdista es la longitud de camino a nodo nulo, llamada `npl`.

```text
npl(null) = 0
npl(x) = 1 + min(npl(left(x)), npl(right(x)))
```

La propiedad izquierdista exige:

```text
npl(left(x)) >= npl(right(x))
```

Esto fuerza a que el camino derecho sea corto. No significa que el árbol esté perfectamente balanceado. Significa que la estructura se inclina hacia la izquierda de forma controlada.

La operación central es `merge`.

```text
merge(a, b):
    si a está vacío: devolver b
    si b está vacío: devolver a
    hacer que la raíz dominante sea a
    a.right = merge(a.right, b)
    si npl(a.left) < npl(a.right):
        intercambiar a.left y a.right
    actualizar npl(a)
    devolver a
```

Una vez que `merge` existe, las demás operaciones se vuelven simples:

| Operación | Implementación |
|---|---|
| `insert(x)` | Crear un heap de un nodo y fusionarlo. |
| `delMax()` | Eliminar la raíz y fusionar sus dos subheaps. |
| `mergeAll()` | Fusionar repetidamente varios heaps. |

La ventaja del heap izquierdista no es superar a `PQ_ComplHeap` en inserción o eliminación simple. Su ventaja es que la fusión se vuelve una operación natural y eficiente.

#### 11. Huffman y colas de prioridad

La codificación de Huffman es una aplicación clásica de colas de prioridad. Su objetivo es asignar códigos más cortos a símbolos más frecuentes y códigos 
más largos a símbolos menos frecuentes, manteniendo una codificación prefija sin ambigüedad.

El algoritmo trabaja con un bosque de árboles. Cada símbolo inicial es un árbol de un solo nodo con peso igual a su frecuencia. Luego se repite:

```text
mientras haya más de un árbol:
    extraer los dos árboles de menor frecuencia
    crear un nuevo nodo padre con peso suma
    reinsertar el nuevo árbol
```

Al final queda un único árbol de Huffman. Cada camino desde la raíz hasta una hoja define el código de un símbolo. 
Un movimiento a la izquierda puede representar `0` y un movimiento a la derecha puede representar `1`.

La razón por la que Huffman necesita una cola de prioridad es que en cada iteración debe seleccionar los dos pesos mínimos. 
Si se buscara linealmente cada vez, el costo sería mayor. Con una cola de prioridad, cada extracción e inserción cuesta `O(log n)`, y la construcción completa cuesta `O(n log n)`.

Aunque `PQ_ComplHeap` esté escrita como max-heap, Huffman puede usarla invirtiendo el comparador. Así, el árbol de menor frecuencia se trata como el elemento
de mayor prioridad lógica.

Casos importantes para una implementación robusta:

| Caso | Tratamiento esperado |
|---|---|
| Texto vacío | No hay alfabeto que codificar. |
| Un solo carácter repetido | Se debe asignar un código válido a ese único símbolo. |
| Frecuencias iguales | Puede haber varios árboles óptimos equivalentes. |
| Espacios y puntuación | Deben tratarse como símbolos reales si aparecen en el texto. |
| Validación round-trip | Codificar y decodificar debe reconstruir exactamente el texto original. |

La longitud promedio ponderada de los códigos permite medir la calidad de la compresión. Si las frecuencias son muy desiguales, Huffman suele producir una mejora mayor. 
Si todas las frecuencias son iguales, los códigos tienden a longitudes similares y la ventaja disminuye.

#### 12. BinaryHeap de Morin y método de Eytzinger

Morin presenta el `BinaryHeap` como una cola de prioridad implementada con un árbol binario completo implícito. El método de Eytzinger almacena los nodos por niveles dentro de un arreglo. 
Esto produce las mismas fórmulas de índice usadas en la Semana 6:

```text
left(i) = 2*i + 1
right(i) = 2*i + 2
parent(i) = floor((i - 1) / 2)
```

La diferencia principal es de convención. Morin usa un min-heap en la explicación: el menor elemento está en la raíz. La implementación de `PQ_ComplHeap` de Semana 6 se presenta como max-heap: el mayor elemento está en la raíz.

El análisis no cambia. En ambos casos:

| Operación | Costo |
|---|---|
| Consultar extremo | `O(1)` |
| Insertar | `O(log n)` |
| Eliminar extremo | `O(log n)` |
| Redimensionamientos | Costo amortizado bajo secuencias largas |

La idea teórica importante es que la altura del árbol completo está acotada por `log n`. Por eso `bubbleUp` y `trickleDown`, o `percolateUp` y `percolateDown`, recorren solo un camino logarítmico.

#### 13. MeldableHeap aleatorizado

El `MeldableHeap` de Morin es otra estructura de cola de prioridad. A diferencia del `BinaryHeap`, no exige forma completa. 
Puede tener cualquier forma de árbol binario, siempre que respete la propiedad de heap.

Su operación central es `merge(h1, h2)`. Si una raíz es nula, se devuelve la otra. Si ambas existen, se elige como raíz la que tiene mayor prioridad según 
la convención. Luego se fusiona recursivamente el otro heap con uno de los dos subárboles de la raíz elegida.

La característica distintiva es que la elección entre hijo izquierdo e hijo derecho se hace aleatoriamente.

```text
merge(h1, h2):
    si h1 está vacío: devolver h2
    si h2 está vacío: devolver h1
    asegurar que h1 tenga la raíz dominante
    elegir aleatoriamente left o right
    fusionar h2 con ese subárbol
    devolver h1
```

Con `merge`, las operaciones principales se expresan de forma muy simple:

| Operación | Implementación |
|---|---|
| `add(x)` | Crear un nodo y fusionarlo con la raíz. |
| `remove()` | Eliminar la raíz y fusionar sus hijos. |
| `absorb(h)` | Fusionar el heap actual con otro heap. |

El análisis usa caminatas aleatorias. La longitud esperada de una caminata aleatoria en un árbol binario con `n` nodos es `O(log n)`, independientemente de la forma del árbol. Por eso `merge` tiene tiempo esperado `O(log n)`.

El `MeldableHeap` muestra una idea distinta a la del heap completo. En vez de imponer una forma rígida, usa aleatorización para evitar depender de una configuración desfavorable.

#### 14. Árbol binario de búsqueda aleatorio

La Semana 6 también introduce un puente hacia estructuras balanceadas mediante Treap. El punto de partida es el problema de un árbol binario de búsqueda ordinario.

Un `BinarySearchTree` puede ser eficiente si su altura es baja. Pero si se insertan claves ordenadas, puede degenerarse en una cadena de longitud `n`. 
En ese caso, `find`, `add` y `remove` pueden costar `O(n)`.

Morin muestra que, si las claves se insertan en orden aleatorio, la ruta esperada de búsqueda es logarítmica. El análisis usa números armónicos:

```text
H_k = 1 + 1/2 + 1/3 + ... + 1/k
```

Como `H_k` está acotado por expresiones logarítmicas, la longitud esperada de una ruta de búsqueda en un árbol binario de búsqueda aleatorio es `O(log n)`.

Este resultado es importante, pero tiene una limitación: un árbol construido a partir de una permutación aleatoria completa no es una estructura dinámica suficiente. 
En un curso de estructuras de datos, se necesita insertar, buscar y eliminar en cualquier momento. El Treap toma la idea de inserción aleatoria y la convierte en una estructura dinámica.

#### 15. Treap: búsqueda por clave y heap por prioridad

Un Treap combina dos invariantes:

| Invariante | Significado |
|---|---|
| Propiedad BST | Las claves menores van al subárbol izquierdo y las mayores al derecho. |
| Propiedad heap | Las prioridades aleatorias respetan orden padre-hijo. |

Cada nodo almacena una clave `x` y una prioridad `p`. Según las claves, el Treap es un árbol binario de búsqueda. Según las prioridades, el Treap es un heap.

Si las prioridades son únicas y aleatorias, la forma del Treap queda determinada. La raíz es el nodo con mejor prioridad. 
El subárbol izquierdo contiene claves menores que la raíz. El subárbol derecho contiene claves mayores que la raíz. Recursivamente ocurre lo mismo.

Una forma útil de entenderlo es esta: un Treap tiene la misma forma que un `BinarySearchTree` donde las claves se hubieran insertado en orden creciente de prioridad. Como las prioridades son aleatorias, el orden de inserción efectivo también es aleatorio.

Por eso el Treap obtiene tiempo esperado `O(log n)` para:

| Operación | Costo esperado |
|---|---|
| `find(x)` | `O(log n)` |
| `add(x)` | `O(log n)` |
| `remove(x)` | `O(log n)` |

La ventaja conceptual es que no necesita almacenar factores de balance como AVL ni colores como red-black tree. Usa prioridades aleatorias y rotaciones locales.

#### 16. Rotaciones en BST y Treap

Las rotaciones son operaciones locales que modifican la forma de un árbol binario de búsqueda sin cambiar el orden inorder.

En una rotación izquierda, un nodo baja hacia la izquierda y su hijo derecho sube. En una rotación derecha, un nodo baja hacia la derecha y su hijo izquierdo sube. 
Aunque cambian las relaciones padre-hijo, las claves siguen apareciendo en el mismo orden si se recorre el árbol en inorden.

Esto es fundamental para Treap. Cuando se inserta un nuevo nodo, primero se coloca como hoja usando la regla BST. Luego puede violar la propiedad de heap por prioridad. 
Para repararla, el nodo sube mediante rotaciones.

```text
add(x):
    insertar como en BST
    asignar prioridad aleatoria
    mientras la prioridad viole la propiedad heap:
        rotar con el padre
```

Este proceso se llama `bubbleUp`.

Para eliminar un nodo, se hace lo inverso. Primero se localiza la clave. Luego se rota el nodo hacia abajo, eligiendo el hijo que permita mantener 
la propiedad heap. Cuando el nodo llega a una hoja, se separa del árbol.

```text
remove(x):
    buscar nodo con clave x
    mientras tenga hijos:
        rotar hacia el hijo con mejor prioridad
    separar la hoja
```

Este proceso se llama `trickleDown`.

La defensa técnica debe resaltar que las rotaciones cumplen dos funciones simultáneas:

1. Preservan el orden BST.
2. Corrigen la propiedad heap de prioridades.

Sin esta doble propiedad, el Treap no podría ser al mismo tiempo estructura de búsqueda y estructura basada en prioridad.

#### 17. Relación entre heap, BST y Treap

La Semana 6 exige distinguir tres estructuras que usan árboles pero responden preguntas distintas.

| Estructura | Pregunta principal | Invariante central |
|---|---|---|
| Heap | ¿Cuál es el elemento de mayor o menor prioridad? | Padre domina a hijos. |
| BST | ¿Dónde está una clave dentro de un conjunto ordenado? | Izquierda menor, derecha mayor. |
| Treap | ¿Cómo mantener un conjunto ordenado dinámico con buen costo esperado? | BST por clave y heap por prioridad. |

Un heap no sirve para búsqueda ordenada eficiente de una clave arbitraria. Puede encontrar rápidamente el máximo o mínimo, pero no permite saber en `O(log n)`
si una clave intermedia existe, salvo que se agreguen otras estructuras.

Un BST sí sirve para búsqueda ordenada, pero puede desbalancearse. El Treap corrige ese riesgo usando prioridades aleatorias. 
No se usa para extraer repetidamente el máximo como una cola de prioridad pura, sino para mantener bajo control la forma del árbol de búsqueda.

Esta distinción ayuda a evitar errores de diseño:

| Necesidad | Estructura adecuada |
|---|---|
| Extraer repetidamente el máximo | `PQ_ComplHeap` |
| Ordenar in situ | `heapSort` |
| Fusionar heaps eficientemente | `PQ_LeftHeap` o `MeldableHeap` |
| Codificación Huffman | Cola de prioridad con comparador de menor frecuencia |
| Buscar claves ordenadas | `BinarySearchTree` o `Treap` |
| Mantener conjunto ordenado dinámico con costo esperado bajo | `Treap` |

#### 18. Organización del código de Semana 6

La carpeta de Semana 6 mantiene un estilo modular y header-only. La intención es que cada estructura pueda estudiarse por separado, pero que todas
se conecten por la idea de prioridad.

Los archivos principales son:

| Archivo | Rol |
|---|---|
| `PQ.h` | Interfaz abstracta de cola de prioridad. |
| `PQ_ComplHeap.h` | Cola de prioridad basada en heap binario completo. |
| `PQ_ComplHeap_macro.h` | Funciones de índice para padre e hijos. |
| `PQ_ComplHeap_getMax.h` | Consulta del máximo. |
| `PQ_ComplHeap_insert.h` | Inserción en heap completo. |
| `PQ_ComplHeap_delMax.h` | Eliminación del máximo. |
| `PQ_ComplHeap_percolateUp.h` | Reparación hacia arriba. |
| `PQ_ComplHeap_percolateDown.h` | Reparación hacia abajo. |
| `PQ_ComplHeap_heapifyFloyd.h` | Construcción lineal del heap. |
| `vector_heapSort.h` | Ordenamiento por heap. |
| `PQ_LeftHeap.h` | Heap izquierdista. |
| `PQ_LeftHeap_merge.h` | Fusión de heaps izquierdistas. |
| `PQ_LeftHeap_insert.h` | Inserción mediante `merge`. |
| `PQ_LeftHeap_delMax.h` | Eliminación mediante `merge` de subárboles. |
| `Huffman_PQ.h` | Construcción de Huffman con cola de prioridad. |
| `Huffman_PQ_generateTree.h` | Generación auxiliar del árbol de Huffman. |
| `MeldableHeap.h` | Heap mezclable de apoyo conceptual. |
| `Treap.h` | Árbol aleatorizado con clave y prioridad. |
| `Capitulo6.h` | Agregador de la semana. |
| `Capitulo10.h` | Alias de compatibilidad para priority queues. |

La semana reutiliza infraestructura de Semana 5:

| Archivo reutilizado | Para qué sirve |
|---|---|
| `BinaryTree.h` | Base conceptual de nodos y recorridos. |
| `BinarySearchTree.h` | Base para búsqueda ordenada y rotaciones. |
| `BinaryHeap.h` | Comparación con otra implementación de heap. |
| `Capitulo5.h` | Integración con el bloque anterior. |

Los demostraciones permiten observar comportamiento concreto:

| Demo | Qué muestra |
|---|---|
| `demo_pq_complheap_basico.cpp` | Inserción, consulta y eliminación en `PQ_ComplHeap`. |
| `demo_heapify_floyd.cpp` | Construcción de heap desde vector. |
| `demo_heapsort.cpp` | Ordenamiento usando heap. |
| `demo_left_heap_merge.cpp` | Fusión de heaps izquierdistas. |
| `demo_huffman.cpp` | Construcción de códigos Huffman. |
| `demo_compare_with_semana5.cpp` | Comparación con estructuras previas. |
| `demo_bst_rotations.cpp` | Rotaciones sobre BST. |
| `demo_treap_basico.cpp` | Inserción, búsqueda y eliminación en Treap. |
| `demo_capitulo6_panorama.cpp` | Recorrido general de la semana. |


#### 19. Complejidades principales

| Estructura u operación | Tiempo esperado o garantizado | Observación |
|---|---:|---|
| `PQ_ComplHeap::getMax()` | `O(1)` | La raíz está en índice `0`. |
| `PQ_ComplHeap::insert()` | `O(log n)` | Usa `percolateUp`. |
| `PQ_ComplHeap::delMax()` | `O(log n)` | Usa `percolateDown`. |
| `heapifyFloyd()` | `O(n)` | Repara desde últimos internos hacia la raíz. |
| `heapSort()` | `O(n log n)` | Ordena in situ, no es estable por defecto. |
| Validar heap completo | `O(n)` | Revisa relaciones padre-hijo. |
| `PQ_LeftHeap::merge()` | `O(log n)` | Depende del camino derecho controlado por `npl`. |
| `PQ_LeftHeap::insert()` | `O(log n)` | Caso particular de `merge`. |
| `PQ_LeftHeap::delMax()` | `O(log n)` | Fusiona subárboles de la raíz. |
| Huffman con heap | `O(n log n)` | Extrae y reinserta árboles. |
| `BinaryHeap` de Morin | `O(log n)` para `add` y `remove` | Ignorando redimensionamiento puntual. |
| `MeldableHeap::merge()` | Tiempo esperado `O(log n)` | Usa elección aleatoria. |
| `Treap::find()` | Tiempo esperado `O(log n)` | Ruta esperada logarítmica. |
| `Treap::add()` | Tiempo esperado `O(log n)` | BST más `bubbleUp`. |
| `Treap::remove()` | Tiempo esperado `O(log n)` | `trickleDown` más separación. |
| `Treap::rank()` con tamaños | Tiempo esperado `O(log n)` | Requiere mantener tamaño de subárbol. |
| `Treap::select()` con tamaños | Tiempo esperado `O(log n)` | Busca por rango. |

#### 20. Cierre conceptual

La Semana 6 muestra que la prioridad es una forma de organizar datos distinta al orden lineal y distinta al orden de búsqueda. 
Una cola de prioridad no pregunta quién llegó primero ni dónde está una clave específica. Pregunta cuál elemento debe salir primero según un criterio de prioridad.

El heap binario completo responde a esa pregunta con una representación compacta en vector. Su fuerza está en mantener una forma rígida y una propiedad local 
padre-hijo. `getMax`, `insert`, `delMax`, Floyd y heapsort son consecuencias directas de esa combinación.

El heap izquierdista y el MeldableHeap responden a otra necesidad: fusionar heaps. El primero lo logra controlando el camino derecho con `npl`. 
El segundo lo logra mediante aleatorización en `merge`.

Huffman muestra por qué una cola de prioridad no es solo una estructura abstracta, sino una herramienta algorítmica. 
Seleccionar repetidamente los dos símbolos o árboles de menor frecuencia se convierte en una operación eficiente y limpia.

El Treap cierra la semana conectando prioridad con búsqueda ordenada. No usa la prioridad para decidir qué elemento sale primero, sino para decidir la forma del árbol. 
Así evita el desbalance esperado de un BST ordinario y logra operaciones dinámicas eficientes.

En conjunto, la Semana 6 enseña una idea profunda: una estructura de datos eficiente no conserva toda la información posible, sino la información correcta 
para las operaciones que debe soportar. En heaps, esa información es el extremo de prioridad.  En Treaps, es la combinación de orden por clave y prioridad aleatoria. 
En Huffman, es la selección repetida de pesos mínimos. 

Comprender estos invariantes permite modificar el código, defenderlo y extenderlo sin convertirlo en una colección de casos especiales.
