### Árboles aleatorios y Scapegoat Trees - Morin

### Resumen

Esta lectura continúa el estudio de los árboles binarios de búsqueda eficientes a partir de una comparación entre dos ideas: el balance esperado producido por la aleatorización y el balance garantizado producido por reconstrucción parcial. En la lectura anterior se trabajaron árboles binarios de búsqueda aleatorios, Treaps y heaps. Ahora se introduce el ScapegoatTree, una estructura de conjunto ordenado que evita depender de rotaciones locales y, en su lugar, reconstruye subárboles completos cuando detecta que la altura empieza a crecer demasiado.

Un ScapegoatTree mantiene la propiedad de árbol binario de búsqueda, pero controla su altura mediante dos contadores: `n`, que representa el número actual de nodos, y `q`, que representa una cota superior reciente para el tamaño del árbol. La estructura mantiene la relación `q/2 <= n <= q` y garantiza que la altura no exceda `log_{3/2} q`. Cuando una inserción crea un nodo demasiado profundo, el algoritmo busca un ancestro desbalanceado, llamado scapegoat, y reconstruye todo su subárbol como un árbol perfectamente balanceado.

La importancia de esta estructura está en su estrategia de diseño. Mientras un Treap usa prioridades aleatorias y rotaciones para obtener tiempo esperado `O(log n)`, un ScapegoatTree usa una regla determinista de profundidad y reconstrucción parcial para obtener operaciones con tiempo amortizado `O(log n)`. Por eso sirve para estudiar otra forma de balancear árboles: no ajustando un nodo a la vez, sino rehaciendo subestructuras completas cuando el desbalance ya es medible.

### Introduccion

Un árbol binario de búsqueda común puede degradarse fácilmente. Si se insertan claves en orden creciente, la estructura puede convertirse en una cadena y sus operaciones pasan de `O(log n)` a `O(n)`. Este problema motivó el uso de árboles aleatorios, Treaps, árboles AVL, red-black trees y otras estructuras balanceadas.

Los árboles aleatorios y los Treaps resuelven el problema usando aleatorización. En un árbol binario de búsqueda aleatorio, la forma depende de una permutación aleatoria de inserción. En un Treap, cada nodo recibe una prioridad aleatoria y la estructura combina la propiedad de búsqueda por clave con la propiedad de heap por prioridad. En ambos casos, el objetivo es que las rutas de búsqueda tengan longitud esperada logarítmica.

El ScapegoatTree propone una estrategia diferente. No asigna prioridades aleatorias, no almacena colores y no mantiene factores de balance como en AVL. Tampoco necesita rotaciones después de cada operación. Su regla central es más global: permite cierto desbalance, pero si una inserción produce una profundidad mayor que la permitida, encuentra un subárbol responsable y lo reconstruye completamente.

Esta lectura debe entenderse como una transición desde árboles aleatorizados hacia árboles balanceados por reconstrucción. La pregunta central ya no es solo cómo evitar árboles degenerados, sino cuánto trabajo de reconstrucción se puede pagar de manera amortizada sin perder eficiencia global.

### Desarrollo

#### 1. De árboles aleatorios a balance por reconstrucción

En un árbol binario de búsqueda aleatorio, la altura y las rutas de búsqueda son pequeñas en promedio porque el orden de inserción se asume aleatorio. Esta idea es poderosa, pero no siempre basta como mecanismo explícito de mantenimiento. En una estructura dinámica, las operaciones llegan una por una y el árbol debe conservar buen rendimiento después de inserciones y eliminaciones arbitrarias.

El Treap convierte la idea de árbol aleatorio en una estructura dinámica: las prioridades aleatorias determinan una forma equivalente a insertar las claves en orden aleatorio de prioridad. El ScapegoatTree, en cambio, no intenta simular aleatoriedad. Su enfoque es determinista: si la altura sigue dentro de una cota logarítmica, no modifica la estructura; si la cota se rompe, reconstruye el subárbol que causó el problema.

Así aparecen dos filosofías de diseño. La primera acepta incertidumbre controlada mediante aleatorización. La segunda acepta desbalance temporal, pero lo corrige con reconstrucciones parciales. Ambas buscan el mismo objetivo: impedir que las búsquedas, inserciones y eliminaciones se vuelvan lineales.

#### 2. Idea central de ScapegoatTree

Un ScapegoatTree es un árbol binario de búsqueda que mantiene dos cantidades globales:

```text
n = numero actual de nodos
q = cota superior reciente del numero de nodos
```

La estructura conserva el invariante:

```text
q/2 <= n <= q
```

Además, su altura debe estar acotada por:

```text
altura <= log_{3/2} q
```

Esta cota permite que el árbol no sea perfectamente balanceado. Puede tener zonas visualmente inclinadas, pero la altura total sigue siendo logarítmica. Esta diferencia es importante: el ScapegoatTree no intenta mantener balance perfecto después de cada operación; solo exige que ninguna ruta sea demasiado larga.

Cuando se llama a `find(x)`, la operación es exactamente la de un árbol binario de búsqueda estándar. Se compara `x` con la clave del nodo actual y se avanza a la izquierda o a la derecha. Como la altura está acotada por `log_{3/2} q`, la búsqueda cuesta `O(log n)`.

#### 3. Reconstrucción parcial

La operación técnica más importante es `rebuild(u)`. Dado un nodo `u`, se toma todo el subárbol con raíz en `u`, se recorre en orden para colocar sus nodos en un arreglo y luego se reconstruye un árbol perfectamente balanceado a partir de ese arreglo.

El recorrido en orden conserva la propiedad de árbol binario de búsqueda porque produce las claves en orden creciente. Después, la reconstrucción elige el elemento central como raíz, construye recursivamente el subárbol izquierdo con la mitad menor y el subárbol derecho con la mitad mayor.

El costo de `rebuild(u)` es:

```text
O(size(u))
```

Este costo puede ser grande para una sola operación, pero la clave del análisis es que no ocurre en cada inserción. El árbol acumula cierto desbalance y solo reconstruye cuando una ruta supera la profundidad permitida.

#### 4. Inserción y búsqueda del scapegoat

La operación `add(x)` empieza como una inserción ordinaria en un árbol binario de búsqueda. Se busca la posición de `x`, se crea una hoja nueva y se registra su profundidad. Luego se evalúa si esa profundidad supera la cota permitida:

```text
depth(u) > log_{3/2} q
```

Si la profundidad no excede la cota, la inserción termina. Si la excede, el algoritmo sube desde el nodo insertado hacia la raíz buscando un ancestro `w` que esté suficientemente desbalanceado. Ese nodo es el scapegoat.

La condición que identifica el desbalance es:

```text
size(w.child) / size(w) > 2/3
```

Aquí `w.child` es el hijo de `w` que está en el camino hacia el nodo recién insertado. Intuitivamente, si una ruta se hizo demasiado larga, entonces en algún punto del camino debe existir un nodo cuyo subárbol pesado contiene más de dos tercios del tamaño total del subárbol. Ese nodo es culpable del exceso de profundidad.

Una vez encontrado el scapegoat, se reconstruye su subárbol. La reconstrucción reduce la altura local y devuelve al árbol completo a la cota permitida.

#### 5. Eliminación y reconstrucción global

La operación `remove(x)` también empieza como en un árbol binario de búsqueda estándar. Se busca el elemento y se elimina mediante el procedimiento usual. La eliminación no aumenta la altura del árbol, por lo que no hace falta buscar un scapegoat local.

Sin embargo, después de muchas eliminaciones, el contador `q` puede quedar demasiado grande en comparación con `n`. Por eso, después de eliminar, se verifica:

```text
q > 2n
```

Si esta condición se cumple, se reconstruye todo el árbol desde la raíz y se actualiza:

```text
q = n
```

Esta reconstrucción global evita que `q` siga representando un tamaño antiguo demasiado grande. También restaura una forma balanceada para el árbol completo.

#### 6. Corrección: por qué siempre existe un scapegoat

El argumento de corrección se basa en una contradicción. Supongamos que se insertó un nodo `u` con profundidad mayor que `log_{3/2} q`, pero que ningún nodo del camino hacia la raíz cumple la condición de scapegoat. Entonces cada hijo en ese camino tendría tamaño a lo más `2/3` del tamaño de su padre.

Si el camino desde la raíz hasta `u` tiene longitud `h`, se obtendría una disminución geométrica:

```text
size(u_i) <= (2/3)^i n
```

Para una profundidad `h > log_{3/2} q`, esta desigualdad llevaría a concluir que el subárbol de `u` tiene tamaño menor que 1, lo cual es imposible porque `u` existe. Por tanto, debe existir al menos un nodo del camino que viole esa relación de tamaños. Ese nodo es el scapegoat.

Esta demostración es importante porque garantiza que el algoritmo no se queda sin solución cuando detecta una profundidad excesiva. Si la cota de altura se rompe, necesariamente hay un subárbol suficientemente desbalanceado que puede reconstruirse.

#### 7. Tiempo amortizado

Si se ignora el costo de reconstrucción, `find(x)`, `add(x)` y `remove(x)` cuestan `O(log n)` porque recorren rutas de altura logarítmica. El punto delicado es demostrar que las llamadas a `rebuild(u)` no destruyen esa eficiencia.

Morin usa un análisis amortizado con créditos. La idea es asignar créditos a los nodos visitados durante inserciones y eliminaciones. Esos créditos se acumulan en las zonas que han sido afectadas por operaciones recientes. Cuando un subárbol se vuelve suficientemente desbalanceado y debe reconstruirse, ya existe una cantidad proporcional de créditos para pagar el costo de reconstrucción.

Durante una secuencia de `m` operaciones, cada operación reparte a lo más una cantidad logarítmica de créditos, porque solo visita una ruta de altura `O(log m)`. Por eso, el total de créditos repartidos es `O(m log m)`. El análisis muestra que esos créditos alcanzan para cubrir todas las reconstrucciones parciales y globales.

La conclusión es que una secuencia de `m` operaciones `add(x)` y `remove(x)` gasta en total `O(m log m)` tiempo en reconstrucciones. Por tanto, el costo amortizado por operación se mantiene en `O(log n)`.

#### 8. Comparación con Treap

El Treap y el ScapegoatTree implementan la misma abstracción general: un conjunto ordenado con operaciones de búsqueda, inserción y eliminación. Sin embargo, sus mecanismos internos son distintos.

En un Treap, cada nodo tiene una prioridad aleatoria. Las operaciones usan rotaciones locales mediante procesos como `bubbleUp` y `trickleDown`. El balance no es garantizado en cada ejecución, pero sí tiene buen comportamiento esperado.

En un ScapegoatTree, no hay prioridades aleatorias. La estructura tolera desbalance mientras la altura no exceda `log_{3/2} q`. Cuando la cota se rompe, reconstruye un subárbol completo. Por eso, el balance no se mantiene con pequeñas rotaciones, sino con reconstrucciones ocasionales de costo lineal en el tamaño del subárbol reconstruido.

Esta diferencia también afecta el rendimiento práctico. Un ScapegoatTree puede ser más lento que otras implementaciones de conjuntos ordenados porque las reconstrucciones completas mueven muchos nodos. Aun así, puede ser útil cuando los nodos contienen información adicional difícil de actualizar con rotaciones locales, pero fácil de recalcular durante una reconstrucción completa.


#### Conclusiones

El ScapegoatTree muestra que no existe una única forma de balancear árboles binarios de búsqueda. Los árboles aleatorios y los Treaps usan aleatorización para evitar configuraciones desfavorables. El ScapegoatTree, en cambio, usa una regla determinista: si una inserción produce una ruta demasiado profunda, entonces debe existir un ancestro suficientemente desbalanceado; ese ancestro se reconstruye.

La estructura mantiene los contadores `n` y `q`, garantiza altura logarítmica y soporta `find(x)`, `add(x)` y `remove(x)` en tiempo amortizado `O(log n)`. Su operación distintiva es `rebuild(u)`, que convierte un subárbol desbalanceado en un subárbol perfectamente balanceado en tiempo lineal respecto al tamaño de ese subárbol.

Desde el punto de vista conceptual, el ScapegoatTree es importante porque separa dos ideas que a veces se confunden: estar perfectamente balanceado y tener altura suficientemente pequeña. Un ScapegoatTree puede verse desbalanceado, pero mientras respete su cota de altura seguirá ofreciendo operaciones eficientes.

Para el curso, esta lectura cierra una línea de comparación entre árboles aleatorios, Treaps, heaps y árboles con reconstrucción parcial. El mensaje central es que el diseño de estructuras de datos depende de elegir buenos invariantes y de justificar, con análisis riguroso, cuándo el costo de mantener esos invariantes sigue siendo eficiente.
