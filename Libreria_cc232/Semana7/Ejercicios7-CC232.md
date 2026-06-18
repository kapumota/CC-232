### Ejercicios 7 - CC232

#### Reglas generales de entrega

Estos ejercicios corresponden a la Semana 7 de `Libreria_cc232`. El tema central es el control de altura en árboles binarios de búsqueda mediante invariantes adicionales: altura en AVL, colores en Red-Black Tree y reconstrucción parcial en ScapegoatTree.

Para cada ejercicio que implique código, entrega como mínimo:

- archivo fuente o header modificado,
- prueba pública o interna,
- salida de ejecución,
- explicación de la complejidad,
- explicación del invariante que se conserva,
- un caso donde la implementación fallaría si no se actualizan alturas, colores, padres o tamaños.

No basta con dibujar el árbol final. En los ejercicios manuales debes mostrar cada comparación, rotación, recoloreo, reconstrucción o propagación de corrección.

Comandos sugeridos de validación:

```bash
cd Libreria_cc232
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug --target \
  sem7_demo_avl_deng_core \
  sem7_demo_avl_compact_rotations \
  sem7_demo_bst_deng_vs_avl \
  sem7_demo_redblack_morin \
  sem7_demo_redblack_llrb \
  sem7_demo_compare_avl_vs_redblack \
  sem7_test_public \
  sem7_test_internal
ctest --test-dir build-debug -R sem7 --output-on-failure
```

#### Ejercicio 1 - Verificador fuerte de BST

Implementa una función de validación para un árbol binario de búsqueda:

```cpp
template <typename T>
bool isBSTStrict(const Node<T>* root);
```

La función debe verificar que todo nodo cumple la propiedad BST estricta:

```text
claves del subárbol izquierdo < clave del nodo < claves del subárbol derecho
```

No basta con comparar cada nodo solo con sus hijos inmediatos. Debes propagar rangos válidos hacia abajo.

Prueba con:

```cpp
{50, 30, 70, 20, 40, 60, 80}
{50, 30, 70, 20, 65, 60, 80} // debe forzarse como árbol inválido
```

Entrega:

- implementación recursiva o iterativa,
- prueba de árbol válido,
- prueba de árbol inválido no detectable por comparación local simple,
- explicación de por qué el recorrido inorder ordenado caracteriza a un BST,
- complejidad temporal y espacial.

#### Ejercicio 2 - Primer nodo que viola AVL

Implementa una función que retorne el primer nodo que viola la condición AVL:

```cpp
template <typename T>
std::optional<T> firstAVLViolation(const AVL<T>& tree);
```

La condición AVL exige que, para todo nodo `u`:

```text
abs(height(u.left) - height(u.right)) <= 1
```

La búsqueda del primer error debe hacerse con un recorrido bien definido. Puedes usar postorden para calcular alturas desde las hojas hacia la raíz.

Prueba con:

```cpp
{30, 20, 40, 10, 25, 5}
{50, 30, 70, 20, 40, 60, 80, 10, 5}
```

Entrega:

- implementación,
- pruebas con árbol válido e inválido,
- altura calculada de cada nodo del camino problemático,
- explicación de por qué postorden es natural para validar altura,
- explicación de qué ocurre si se confía en alturas almacenadas corruptas.

#### Ejercicio 3 - Casos manuales de rotación AVL

Construye manualmente los cuatro casos clásicos de inserción AVL:

```text
LL, LR, RL, RR
```

Usa estas secuencias mínimas:

```cpp
LL: {30, 20, 10}
RR: {10, 20, 30}
LR: {30, 10, 20}
RL: {10, 30, 20}
```

Para cada caso, muestra:

- árbol antes de rebalancear,
- nodo `g` desbalanceado,
- padre `p`, hijo `v`,
- factor de balance de `g`, `p` y `v`,
- rotación o doble rotación aplicada,
- árbol final,
- recorrido inorder antes y después.

Entrega:

- explicación manual,
- una demostración en `demo_avl_compact_rotations.cpp`,
- validación automática con `isAVL()`,
- explicación de por qué una rotación conserva el orden inorder.

#### Ejercicio 4 - Inserción AVL con conteo de rotaciones

Modifica la implementación AVL para contar cuántas rotaciones se ejecutan durante cada inserción.

Agrega una estructura auxiliar:

```cpp
struct AVLInsertStats {
  int comparisons = 0;
  int rotations = 0;
  int heightUpdates = 0;
  bool rebalanced = false;
};
```

Implementa una variante:

```cpp
AVLInsertStats insertWithStats(const T& x);
```

Prueba con:

```cpp
{50, 30, 70, 20, 40, 60, 80}
{1, 2, 3, 4, 5, 6, 7, 8, 9}
{9, 8, 7, 6, 5, 4, 3, 2, 1}
```

Entrega:

- implementación,
- tabla con una fila por inserción,
- altura final del árbol,
- número total de rotaciones,
- explicación de por qué una inserción AVL requiere a lo más una operación de rebalanceo local, aunque esa operación pueda tener una o dos rotaciones.

#### Ejercicio 5 - Eliminación AVL con múltiples rebalanceos

Diseña una secuencia de eliminación donde AVL necesite más de una operación de rebalanceo al subir hacia la raíz.

Puedes construir primero un árbol con:

```cpp
{50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 35, 55, 65, 85, 95, 1, 6, 14, 16}
```

Luego busca una eliminación que fuerce propagación de cambios de altura.

Entrega:

- árbol inicial,
- clave eliminada,
- camino desde el nodo eliminado hasta la raíz,
- nodos que cambian de altura,
- cada rebalanceo aplicado,
- número de rotaciones,
- validación final con `isAVL()` e inorder ordenado,
- explicación de por qué la eliminación puede requerir varios rebalanceos, a diferencia de la inserción.

#### Ejercicio 6 - Comparación BST contra AVL con entrada ordenada

Crea un demostración `demo_bst_vs_avl_sorted.cpp` que inserte las claves:

```cpp
1, 2, 3, ..., n
```

en un BST común y en un AVL.

Prueba con:

```text
n = 10
n = 100
n = 1000
n = 5000
```

Para cada `n`, reporta:

- altura del BST,
- altura del AVL,
- número de comparaciones promedio en búsqueda exitosa,
- número de rotaciones AVL,
- tiempo aproximado de construcción.

Entrega:

- demostración,
- tabla de resultados,
- explicación de por qué el BST degenera,
- explicación de por qué el AVL mantiene altura `O(log n)`,
- una reflexión sobre si menor altura siempre implica menor tiempo real.

#### Ejercicio 7 - Red-Black Tree: validador de invariantes

Implementa un verificador fuerte de Red-Black Tree:

```cpp
struct RBValidationResult {
  bool valid = true;
  int blackHeight = 0;
  std::string message;
};

template <typename T>
RBValidationResult validateRedBlackTree(const RedBlackTree<T>& tree);
```

Debe verificar:

1. la raíz es negra,
2. todos los nodos externos `nil` se consideran negros,
3. no existe arista rojo-rojo,
4. todos los caminos desde un nodo hasta hojas externas tienen la misma altura negra,
5. el recorrido inorder respeta el orden BST.

Entrega:

- implementación,
- pruebas con árbol válido,
- prueba alterando manualmente un color para romper rojo-rojo,
- prueba alterando manualmente un color para romper altura negra,
- explicación de cada invariante.

#### Ejercicio 8 - Conversión Red-Black Tree a árbol 2-4

Implementa una función de diagnóstico que agrupe cada nodo negro con sus hijos rojos directos para producir una representación conceptual de árbol 2-4.

Puedes imprimir cada nodo 2-4 como una lista ordenada de claves:

```text
[3]
[1, 2]
[5, 7, 9]
```

Prueba con un Red-Black Tree construido por:

```cpp
{7, 3, 11, 1, 5, 9, 15, 0, 2, 4, 6, 8, 10, 12, 14}
```

Entrega:

- función de impresión,
- árbol rojo-negro original con colores,
- árbol 2-4 conceptual,
- explicación de cuándo un nodo negro representa un nodo 2, 3 o 4,
- explicación de por qué la altura negra se corresponde con la altura del árbol 2-4.

#### Ejercicio 9 - Inserciones Red-Black Tree paso a paso

Usando el árbol base:

```cpp
{7, 3, 11, 1, 5, 9, 15, 0, 2, 4, 6, 8, 10, 12, 14}
```

ilustra la inserción de:

```cpp
13
3.5
3.3
```

Si tu implementación usa enteros, reemplaza `3.5` y `3.3` por claves enteras equivalentes que mantengan el mismo orden relativo, por ejemplo:

```cpp
35
33
```

usando una escala por diez.

Entrega:

- estado después de cada inserción,
- colores de todos los nodos en el camino afectado,
- caso de corrección aplicado,
- rotaciones ejecutadas,
- recoloreos ejecutados,
- validación final,
- correspondencia conceptual con división de nodos en un árbol 2-4.

#### Ejercicio 10 - Eliminaciones Red-Black Tree paso a paso

Usando el árbol construido en el ejercicio anterior, ilustra la eliminación de:

```cpp
11
9
5
```

Para cada eliminación, muestra:

- nodo buscado,
- sucesor usado si el nodo tiene dos hijos,
- nodo físicamente removido,
- color del nodo removido,
- si aparece doble negro,
- caso de `removeFixup` aplicado,
- rotaciones y recoloreos,
- árbol final validado.

Entrega:

- explicación manual,
- salida de la demostración,
- prueba automática con `validateRedBlackTree`,
- explicación de por qué eliminar un nodo negro es más delicado que eliminar un nodo rojo.

#### Ejercicio 11 - `pushBlack` y `pullBlack` como operaciones sobre árboles 2-4

Explica e implementa trazas para las operaciones conceptuales:

```cpp
pushBlack(u)
pullBlack(u)
```

No basta con decir que cambian colores. Debes interpretar cada operación sobre el árbol 2-4 simulado.

Entrega:

- ejemplo donde `pushBlack(u)` representa una división,
- ejemplo donde `pullBlack(u)` representa una fusión o préstamo,
- dibujo antes y después en Red-Black Tree,
- dibujo antes y después en árbol 2-4,
- explicación de cómo cambia la altura negra local,
- explicación de qué invariante podría romperse si se aplica en el nodo incorrecto.

#### Ejercicio 12 - Altura extrema en Red-Black Tree

Construye familias de Red-Black Trees con altura cercana a:

```text
2 log n
```

No se requiere una fórmula cerrada perfecta, pero sí una construcción general para valores crecientes de `n`.

Entrega:

- construcción para al menos cuatro tamaños diferentes,
- altura real medida,
- cota `2 log2(n)`,
- dibujo o impresión por niveles,
- explicación de por qué alternar nodos negros y rojos maximiza la altura manteniendo los invariantes,
- discusión breve sobre por qué AVL suele quedar más bajo que Red-Black Tree.

#### Ejercicio 13 - Unión de dos Red-Black Trees

Diseña una operación conceptual para unir dos Red-Black Trees `T1` y `T2` tales que:

```text
max(T1) < min(T2)
```

Primero resuelve el caso donde ambos árboles tienen la misma altura negra. Luego extiende tu solución al caso general.

Firma sugerida:

```cpp
template <typename T>
RedBlackTree<T> joinRedBlack(RedBlackTree<T>& left,
                             const T& middle,
                             RedBlackTree<T>& right);
```

Entrega:

- algoritmo para alturas negras iguales,
- algoritmo para alturas negras distintas,
- explicación de dónde se inserta `middle`,
- corrección de colores necesaria,
- complejidad en función de `h1` y `h2`,
- prueba con árboles pequeños y medianos.

#### Ejercicio 14 - ScapegoatTree manual con créditos

Ilustra qué ocurre cuando se agrega la secuencia:

```cpp
1, 5, 2, 4, 3
```

sobre un ScapegoatTree vacío.

Para cada inserción, muestra:

- árbol antes y después,
- valores de `n` y `q`,
- profundidad del nodo insertado,
- valor de `log_{3/2}(q)`,
- si aparece un scapegoat,
- subárbol reconstruido,
- créditos asignados según el análisis amortizado,
- créditos gastados durante `rebuild(u)`.

Entrega:

- desarrollo manual paso a paso,
- tabla de créditos,
- árbol final,
- explicación de por qué la reconstrucción parcial conserva el orden BST.

#### Ejercicio 15 - Costo inferior de reconstrucciones en ScapegoatTree

Demuestra experimentalmente y razona teóricamente que, si se inserta:

```cpp
1, 2, 3, ..., n
```

en un ScapegoatTree vacío, el tiempo total gastado en llamadas a `rebuild(u)` es al menos:

```text
c n log n
```

para alguna constante `c > 0` y para infinitos valores de `n`.

Prueba con:

```text
n = 100
n = 300
n = 1000
n = 3000
n = 10000
```

Entrega:

- contador de llamadas a `rebuild`,
- suma total de tamaños reconstruidos,
- tabla comparando `rebuildWork` contra `n log2(n)`,
- argumento teórico breve,
- explicación de por qué ScapegoatTree puede ser más lento que Treap o Red-Black Tree en ciertas secuencias.

#### Ejercicio 16 - ScapegoatTree parametrizado por `b`

Diseña una variante de ScapegoatTree donde la trayectoria de búsqueda no exceda:

```text
log_b(q), con 1 < b < 2
```

En la versión clásica, `b = 3/2`.

Implementa:

```cpp
class ScapegoatTreeB {
public:
  explicit ScapegoatTreeB(double b);
};
```

Prueba con:

```text
b = 1.2
b = 1.5
b = 1.8
```

Entrega:

- modificación del criterio de profundidad,
- modificación del criterio para encontrar scapegoat,
- análisis amortizado en función de `b`,
- experimentos con inserciones ordenadas y aleatorias,
- discusión sobre el costo de búsqueda frente al costo de reconstrucción.

#### Ejercicio 17 - Optimización de `add(x)` en ScapegoatTree

Modifica `add(x)` para no recomputar tamaños de subárboles ya calculados durante la búsqueda del scapegoat.

La idea es que, cuando se quiere calcular `size(w)`, ya se conoce uno de estos valores:

```cpp
size(w.left)
size(w.right)
```

porque se viene subiendo desde el hijo que pertenece al camino de inserción.

Entrega:

- implementación original instrumentada,
- implementación optimizada,
- contador de llamadas a `size`,
- comparación con datos ordenados y aleatorios,
- explicación de por qué la complejidad asintótica no cambia necesariamente, pero el tiempo real sí puede mejorar.

#### Ejercicio 18 - ScapegoatTree con tamaños explícitos

Implementa una segunda versión de ScapegoatTree donde cada nodo almacene:

```cpp
std::size_t size;
```

Debes mantener `size` después de:

- inserción,
- eliminación,
- reconstrucción parcial,
- reconstrucción total de la raíz.

Entrega:

- cambios en `Node`,
- actualización de tamaños,
- pruebas después de cada operación,
- comparación contra la versión original y contra la versión del ejercicio anterior,
- explicación de qué se gana y qué se pierde al almacenar tamaños explícitos.

#### Ejercicio 19 - Reconstrucción sin arreglo auxiliar

Reimplementa:

```cpp
rebuild(u)
```

sin usar un arreglo de nodos.

La reconstrucción debe tener dos fases:

1. convertir el subárbol en una lista enlazada ordenada usando recorrido inorder,
2. convertir la lista enlazada en un BST perfectamente balanceado.

Entrega:

- implementación recursiva,
- demostración con un subárbol de al menos 11 nodos,
- prueba de inorder antes y después,
- validación de padres,
- validación de altura mínima,
- análisis de espacio adicional usado.

#### Ejercicio 20 - Árbol balanceado por peso

Implementa una estructura `WeightBalancedTree` basada en BST.

Cada nodo `u`, excepto la raíz, debe satisfacer:

```text
size(u) <= (2/3) size(u.parent)
```

Las operaciones `add(x)` y `remove(x)` siguen el BST estándar, pero si se viola el invariante en algún nodo `u`, se reconstruye el subárbol con raíz en `u.parent`.

Entrega:

- diseño de nodo con tamaño,
- implementación de inserción,
- implementación de eliminación,
- criterio exacto de reconstrucción,
- prueba con inserciones ordenadas,
- prueba con inserciones aleatorias,
- argumento de costo amortizado `O(log n)`.

#### Ejercicio 21 - CountdownTree

Diseña e implementa una estructura `CountdownTree`.

Cada nodo `u` mantiene un temporizador:

```cpp
int timer;
```

Cada vez que una operación afecta el subárbol de `u`, se decrementa `u.timer`. Cuando `u.timer == 0`, se reconstruye el subárbol de `u` como un BST perfectamente balanceado. Después de una reconstrucción, cada nodo reconstruido reinicia su temporizador con una cantidad proporcional al tamaño de su subárbol.

Entrega:

- regla exacta para inicializar `timer`,
- regla exacta para decrementar `timer`,
- implementación de reconstrucción,
- experimento con inserciones ordenadas,
- experimento con inserciones aleatorias,
- explicación de qué invariante de balance aproximado se induce.

#### Ejercicio 22 - DynamiteTree aleatorizado

Diseña e implementa una estructura `DynamiteTree`.

Cada nodo mantiene:

```cpp
std::size_t size;
```

Cuando una inserción o eliminación afecta el subárbol de un nodo `u`, el nodo `u` se reconstruye con probabilidad:

```text
1/size(u)
```

Entrega:

- generador pseudoaleatorio con semilla fija,
- implementación de inserción,
- implementación de eliminación,
- contador de explosiones o reconstrucciones,
- comparación con ScapegoatTree,
- análisis del tiempo esperado `O(log n)`,
- explicación de por qué se debe usar semilla fija en pruebas.

#### Ejercicio 23 - Estructura `Sequence` con orden constante

Diseña una estructura `Sequence` que mantenga una lista de elementos y soporte:

```cpp
Element* addAfter(Element* e, const T& value);
void remove(Element* e);
bool testBefore(Element* e1, Element* e2) const;
```

Requisitos:

- `addAfter(e)` debe costar `O(log n)` amortizado,
- `remove(e)` debe costar `O(log n)` amortizado,
- `testBefore(e1, e2)` debe costar `O(1)`.

Sugerencia: guarda los elementos en una estructura tipo ScapegoatTree siguiendo el orden de la secuencia. Asigna a cada elemento una etiqueta entera que codifique el camino desde la raíz.

Entrega:

- diseño de etiquetas,
- operación `addAfter`,
- operación `remove`,
- operación `testBefore`,
- caso donde las etiquetas deben reconstruirse,
- análisis amortizado.

#### Ejercicio 24 - Comparación experimental de estructuras SSet

Diseña una batería de experimentos para comparar:

```text
BST
AVL
Treap
ScapegoatTree
RedBlackTree
RedBlackTreeLLRB
```

Debe medir:

- `find(x)`,
- `add(x)`,
- `remove(x)`,
- altura final,
- número de rotaciones,
- número de reconstrucciones,
- número de recoloreos,
- memoria aproximada por nodo.

Escenarios obligatorios:

1. inserción aleatoria y búsqueda aleatoria,
2. inserción ordenada creciente,
3. inserción ordenada decreciente,
4. eliminación aleatoria,
5. eliminación ordenada,
6. patrón mixto: 60% búsqueda, 25% inserción, 15% eliminación.

Entrega:

- programa `demo_sem7_sset_benchmark.cpp`,
- semilla fija,
- tabla de resultados,
- gráfico opcional,
- conclusión razonada sobre qué estructura conviene en cada escenario,
- explicación de por qué el peor caso, el costo esperado y el costo amortizado no significan lo mismo.

#### Bloque integrador - Defensa técnica de Semana 7

Responde por escrito, con ejemplos, las siguientes preguntas:

1. ¿Por qué una rotación preserva el recorrido inorder?
2. ¿Por qué AVL suele tener menor altura que Red-Black Tree?
3. ¿Por qué Red-Black Tree puede hacer menos trabajo de rebalanceo que AVL en algunas actualizaciones?
4. ¿Qué relación existe entre Red-Black Tree y árboles 2-4?
5. ¿Qué significa doble negro en una eliminación Red-Black?
6. ¿Por qué ScapegoatTree no usa rotaciones locales para rebalancear?
7. ¿Qué diferencia hay entre tiempo esperado, amortizado y peor caso?
8. ¿Por qué una estructura con mejor cota asintótica puede ser más lenta en una implementación real?
9. ¿Qué invariante es más fácil de verificar automáticamente: AVL, Red-Black Tree o ScapegoatTree?
10. ¿Qué estructura elegirías para una biblioteca estándar y por qué?.

Entrega:

- respuestas breves pero justificadas,
- al menos un ejemplo manual por cada grupo de estructuras,
- referencias a funciones concretas del código de Semana 7,
- conclusiones comparativas.
