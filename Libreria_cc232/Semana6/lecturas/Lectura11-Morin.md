### Treaps, heaps y colas de prioridad - Morin

### Resumen

Esta lectura reúne dos bloques centrales de estructuras de datos estudiados por Morin: los árboles binarios de búsqueda aleatorizados, especialmente los **Treaps**, y las implementaciones de **colas de prioridad** mediante **heaps**. En ambos casos, el objetivo es obtener operaciones eficientes, usualmente con tiempo esperado o garantizado de orden `O(log n)`.

En el capítulo sobre árboles binarios de búsqueda aleatorios, Morin muestra que el orden de inserción afecta profundamente la forma del árbol. Una secuencia ordenada puede producir un árbol degenerado, equivalente a una lista, mientras que una permutación aleatoria tiende a producir árboles mucho más balanceados. Esta idea se formaliza usando números armónicos para analizar la longitud esperada de las rutas de búsqueda. A partir de este análisis surge el **Treap**, una estructura que combina la propiedad de árbol binario de búsqueda respecto a las claves con la propiedad de heap respecto a prioridades aleatorias.

En el capítulo sobre heaps, Morin presenta dos implementaciones de colas de prioridad. La primera es el **BinaryHeap**, que representa un árbol binario completo dentro de un arreglo mediante el método de Eytzinger. La segunda es el **MeldableHeap**, un heap fusionable aleatorizado cuya operación fundamental es `merge`. Mientras el BinaryHeap destaca por su simplicidad y eficiencia práctica, el MeldableHeap permite fusionar colas de prioridad de manera natural, manteniendo tiempo esperado `O(log n)`.

En conjunto, estos temas muestran dos estrategias recurrentes en el diseño de estructuras de datos: usar invariantes estructurales para mantener eficiencia y usar aleatorización para evitar configuraciones desfavorables.

### Introduccion

Las estructuras de datos no solo almacenan información; también imponen una organización que permite ejecutar operaciones con ciertas garantías de tiempo. En un árbol binario de búsqueda, la organización depende de las comparaciones entre claves. En un heap, la organización depende de prioridades: el elemento mínimo se mantiene cerca de la raíz para poder extraerlo rápidamente.

Morin presenta estos temas desde una preocupación común: evitar que las operaciones se degraden a tiempo lineal. En un árbol binario de búsqueda común, insertar claves en orden puede crear una cadena de altura `n - 1`, por lo que una búsqueda puede costar `O(n)`. En cambio, si la estructura se mantiene balanceada, la altura se aproxima a `O(log n)` y las operaciones son mucho más eficientes.

La aleatorización aparece como una herramienta para obtener buen comportamiento promedio sin tener que mantener reglas rígidas de balanceo como en árboles AVL o red-black trees. En los Treaps, las prioridades aleatorias determinan la forma del árbol. En los MeldableHeaps, una elección aleatoria dentro de `merge` evita depender de una forma específica del árbol. Por otro lado, el BinaryHeap consigue eficiencia mediante una estructura completamente determinada: un árbol binario completo representado en un arreglo.

Esta lectura, por tanto, conecta tres ideas: búsqueda ordenada, prioridad y aleatorización.

### Desarrollo

#### 1. Árboles binarios de búsqueda aleatorios

Un árbol binario de búsqueda puede tener formas muy distintas aun si almacena el mismo conjunto de claves. Morin ilustra esta diferencia con dos árboles que contienen los enteros `0, ..., 14`: uno degenerado, con altura `14`, y otro perfectamente balanceado, con altura `3`. La diferencia no está en los datos, sino en el orden de inserción.

Un **árbol binario de búsqueda aleatorio** se obtiene tomando una permutación aleatoria de `n` elementos e insertándolos en un `BinarySearchTree`. Como cada permutación es igualmente probable, el árbol resultante permite analizar la longitud esperada de las rutas de búsqueda.

El análisis usa los **números armónicos**:

```text
H_k = 1 + 1/2 + 1/3 + ... + 1/k
```

Estos números están relacionados con el logaritmo natural, pues `ln k < H_k <= ln k + 1`. Por ello, al estudiar rutas de búsqueda, las sumas armónicas conducen naturalmente a cotas logarítmicas.

El resultado principal indica que, en un árbol binario de búsqueda aleatorio de tamaño `n`, la longitud esperada de la ruta de búsqueda para un elemento es aproximadamente `O(log n)`. Para un valor almacenado en el árbol, la ruta esperada se expresa mediante términos como `H_{x+1}` y `H_{n-x}`. Para un valor no almacenado, se obtiene una expresión similar. La conclusión es que buscar un elemento presente y buscar un elemento ausente tienen costos esperados muy cercanos.

Esta observación es importante porque justifica la idea de que un árbol binario de búsqueda puede ser eficiente si su forma se comporta como si las inserciones hubieran ocurrido en orden aleatorio.

#### 2. Treap: árbol binario de búsqueda aleatorizado

El problema de los árboles binarios de búsqueda aleatorios es que no son una estructura dinámica completa: el análisis parte de insertar una permutación aleatoria completa, pero una colección real necesita operaciones `add(x)`, `remove(x)` y `find(x)` en cualquier momento.

El **Treap** resuelve este problema combinando dos propiedades:

- Propiedad de árbol binario de búsqueda sobre la clave `x`.
- Propiedad de heap sobre una prioridad aleatoria `p`.

Cada nodo almacena una clave y una prioridad. Respecto a las claves, todo elemento menor va al subárbol izquierdo y todo elemento mayor va al subárbol derecho. Respecto a las prioridades, el padre tiene prioridad menor que sus hijos. Así, el nodo con menor prioridad queda en la raíz.

La idea clave es que, si las prioridades son aleatorias y únicas, el Treap tiene la misma forma que un árbol binario de búsqueda construido insertando los elementos en orden creciente de prioridad. Como ese orden es aleatorio, el Treap hereda el comportamiento esperado de los árboles binarios de búsqueda aleatorios.

La operación `find(x)` sigue la ruta normal de búsqueda de un árbol binario de búsqueda. Su costo esperado es `O(log n)`.

La operación `add(x)` procede en dos fases. Primero inserta el nuevo nodo como en un árbol binario de búsqueda ordinario. Luego, si la prioridad del nuevo nodo viola la propiedad de heap, se aplican rotaciones para hacerlo subir. Este proceso se conoce como `bubbleUp`. Cada rotación preserva el orden de búsqueda y reduce la profundidad del nodo insertado hasta que la propiedad de heap se restaura.

La operación `remove(x)` es el proceso inverso. Se localiza el nodo, luego se aplican rotaciones para hacerlo bajar hasta convertirlo en hoja. Después se elimina mediante una operación de separación. Este proceso suele llamarse `trickleDown`. La elección de rotar hacia la izquierda o hacia la derecha depende de las prioridades de los hijos, de modo que la propiedad de heap se mantenga tras la eliminación.

Morin concluye que un Treap implementa la interfaz de conjunto ordenado `SSet` y soporta `add(x)`, `remove(x)` y `find(x)` en tiempo esperado `O(log n)` por operación. En términos conceptuales, el Treap es una estructura elegante porque usa prioridades aleatorias para obtener balance esperado sin almacenar explícitamente alturas ni factores de balance.

#### 3. Colas de prioridad y BinaryHeap

Una **cola de prioridad** permite insertar elementos y extraer repetidamente el elemento de mayor prioridad. En la formulación de Morin, el heap usado es un min-heap: el elemento mínimo se ubica en la raíz.

El **BinaryHeap** representa un árbol binario completo dentro de un arreglo. Esta representación se basa en el método de Eytzinger, que almacena los nodos por niveles. Si un nodo está en el índice `i`, entonces:

```text
left(i) = 2i + 1
right(i) = 2i + 2
parent(i) = (i - 1) / 2
```

La propiedad de heap exige que ningún nodo tenga un valor menor que su padre. Por ello, el menor elemento siempre está en la posición `0` del arreglo.

La operación `add(x)` agrega el nuevo elemento al final del arreglo, preservando la forma de árbol completo. Luego aplica `bubbleUp`: mientras el nuevo elemento sea menor que su padre, intercambia posiciones con él. Como la altura de un árbol binario completo con `n` nodos es `O(log n)`, el costo de `add(x)` es `O(log n)`.

La operación `remove()` elimina el mínimo, ubicado en la raíz. Para no romper la estructura compacta del arreglo, se reemplaza la raíz por el último elemento y se reduce el tamaño del heap. Luego se aplica `trickleDown`: el nuevo valor de la raíz se compara con sus hijos y se intercambia con el menor de ellos hasta restaurar la propiedad de heap. Esta operación también cuesta `O(log n)`.

Morin señala que el costo de redimensionar el arreglo puede analizarse de forma amortizada. Por tanto, el BinaryHeap soporta secuencias de operaciones de forma eficiente y sirve como base para algoritmos como **heapsort**.

#### 4. MeldableHeap: heap fusionable aleatorizado

El **MeldableHeap** también implementa una cola de prioridad, pero no exige que el árbol sea completo ni que tenga una forma fija. Su ventaja principal es que permite fusionar heaps mediante una operación natural: `merge(h1, h2)`.

La operación `merge` recibe dos raíces de heaps y devuelve una raíz que contiene todos los elementos. Si una raíz es nula, se devuelve la otra. Si ambas existen, se coloca como raíz aquella con menor clave. Luego se fusiona recursivamente el otro heap con uno de los subárboles de la raíz elegida. La elección entre subárbol izquierdo y derecho se hace aleatoriamente, como si se lanzara una moneda.

Con `merge`, las operaciones principales son simples:

- `add(x)` crea un heap de un solo nodo y lo fusiona con el heap actual.
- `remove()` elimina la raíz y fusiona sus dos subárboles.
- `absorb(h)` puede fusionar dos colas de prioridad completas.

El análisis de `merge` se basa en una caminata aleatoria dentro de un árbol binario. Morin demuestra que la longitud esperada de una caminata aleatoria en un árbol con `n` nodos es a lo sumo `log(n + 1)`, independientemente de la forma del árbol. Como `merge` puede verse como caminatas aleatorias en los heaps que se están fusionando, su tiempo esperado es `O(log n)`.

De esta manera, el MeldableHeap ofrece una implementación flexible de colas de prioridad, especialmente útil cuando la operación de fusión es importante.

#### 5. Relación entre los temas

Los Treaps y los heaps parecen estructuras distintas, pero comparten una idea central: mantener una propiedad local que produce buen rendimiento global.

En un Treap, la propiedad de búsqueda organiza las claves y la propiedad de heap organiza las prioridades aleatorias. En un BinaryHeap o MeldableHeap, la propiedad de heap organiza directamente los valores según prioridad. En todos los casos, las operaciones locales como intercambios, rotaciones o fusiones restauran invariantes que garantizan eficiencia.

También hay una diferencia importante. El BinaryHeap obtiene eficiencia por su forma rígida: siempre es un árbol binario completo embebido en un arreglo. El Treap y el MeldableHeap, en cambio, usan aleatorización para evitar depender de una forma perfectamente balanceada. Esta aleatorización no garantiza que cada ejecución sea óptima, pero sí ofrece buenas cotas esperadas.

Finalmente, estas estructuras explican la base conceptual de varias aplicaciones. Un BinaryHeap sirve para implementar colas de prioridad y heapsort. Una cola de prioridad también es útil para algoritmos como Huffman, Dijkstra y procesos donde repetidamente se necesita extraer el elemento de menor costo o prioridad. Los Treaps, por su parte, son útiles cuando se necesita mantener un conjunto ordenado dinámico con búsquedas, inserciones y eliminaciones eficientes.

#### Conclusiones

Morin muestra que muchas estructuras eficientes dependen de mantener invariantes simples pero potentes. En los árboles binarios de búsqueda, el reto es evitar que la altura crezca linealmente. Los árboles aleatorios y los Treaps resuelven este problema usando aleatorización, logrando rutas de búsqueda de longitud esperada logarítmica.

El Treap es especialmente importante porque convierte el análisis de árboles de búsqueda aleatorios en una estructura dinámica. Al combinar claves ordenadas con prioridades aleatorias, logra implementar `find`, `add` y `remove` en tiempo esperado `O(log n)`, usando rotaciones para conservar sus propiedades.

Los heaps, por otro lado, son la estructura natural para implementar colas de prioridad. El BinaryHeap usa un arreglo y una forma de árbol completo, lo que lo hace simple, compacto y eficiente. Sus operaciones principales se basan en `bubbleUp` y `trickleDown`, ambas acotadas por la altura logarítmica del árbol.

El MeldableHeap amplía la idea de heap al permitir fusiones eficientes. Su operación fundamental, `merge`, usa una decisión aleatoria para conservar un tiempo esperado `O(log n)` sin imponer una forma fija al árbol. Esto lo hace conceptualmente simple y adecuado para escenarios donde combinar colas de prioridad es una operación frecuente.

En síntesis, la lectura presenta dos caminos hacia la eficiencia: estructura rígida, como en BinaryHeap, y estructura aleatorizada, como en Treap y MeldableHeap. Ambos enfoques muestran cómo el diseño cuidadoso de invariantes permite obtener operaciones rápidas y escalables.
