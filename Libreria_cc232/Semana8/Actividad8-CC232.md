### Actividad 8 - CC232

#### Datos generales

Duración: 3 horas de clase.

Modalidad: Trabajo individual.

Entrega: Un archivo llamado `Actividad8-CC232.md` y los archivos modificados solicitados.

#### Objetivo

Consolidar lo trabajado en la Semana 8 a partir de lectura de código, ejecución de demostraciones, revisión de pruebas, comparación experimental, modificación controlada y defensa escrita breve.

La meta es entender cómo se implementan diccionarios no ordenados mediante hashing y cómo se comparan con las estructuras estudiadas en las semanas anteriores:

1. Semana 5 introduce árboles binarios, BST, búsqueda ordenada y costo dependiente de la altura.
2. Semana 6 distingue interfaz, representación, prioridad, heaps y medición experimental.
3. Semana 7 estudia AVL y Red-Black Tree como diccionarios ordenados con altura controlada.
4. Semana 8 contrasta esas estructuras con tablas hash, donde el costo esperado puede ser constante si la función hash, la política de colisión, el factor de carga y el rehashing están bien diseñados.

El énfasis de esta actividad está en explicar no solo qué operación se ejecuta, sino qué invariante se mantiene, qué métrica se observa, qué evidencia produce el código y qué costo tiene cada decisión de diseño.

#### Material de trabajo

#### Código de la semana

Revisa como mínimo:

* `Semana8/README.md`
* `Semana8/lecturas/Lectura14-Morin.md`
* `Semana8/include/Dictionary.h`
* `Semana8/include/Entry.h`
* `Semana8/include/ArrayStack.h`
* `Semana8/include/Bitmap.h`
* `Semana8/include/PrimeUtils.h`
* `Semana8/include/HashCode.h`
* `Semana8/include/HashStats.h`
* `Semana8/include/RehashPolicy.h`
* `Semana8/include/UniversalHash.h`
* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/LinearHashTable.h`
* `Semana8/include/HashtableOA.h`
* `Semana8/include/QuadraticHashTable.h`
* `Semana8/include/DoubleHashTable.h`
* `Semana8/include/RobinHoodHashTable.h`
* `Semana8/include/Applications.h`
* `Semana8/include/Capitulo9.h`

#### Código reutilizado conceptualmente

Revisa también:

* `Semana5/include/BinarySearchTree.h`
* `Semana6/include/Treap.h`
* `Semana7/include/AVL.h`
* `Semana7/include/RedBlackTree.h`
* `Semana7/demos/demo_compare_avl_vs_redblack.cpp`
* `Semana7/demos/demo_capitulo7_panorama.cpp`

#### Demostraciones y pruebas

Revisa y ejecuta:

* `Semana8/demos/demo_chained.cpp`
* `Semana8/demos/demo_linear.cpp`
* `Semana8/demos/demo_hashtable_oa.cpp`
* `Semana8/demos/demo_aplicaciones.cpp`
* `Semana8/demos/demo_collision_strategies.cpp`
* `Semana8/demos/demo_hash_functions.cpp`
* `Semana8/demos/demo_tombstones.cpp`
* `Semana8/demos/demo_benchmark_load_factor.cpp`
* `Semana8/pruebas_publicas/test_public_week8.cpp`
* `Semana8/pruebas_internas/test_internal_week8.cpp`
* `Semana8/pruebas_internas/test_tombstones.cpp`
* `Semana8/pruebas_internas/test_collision_patterns.cpp`
* `Semana8/pruebas_internas/test_rehashing.cpp`
* `Semana8/pruebas_internas/test_randomized_against_stl.cpp`
* `Semana8/CMakeLists.txt`

#### Reglas de trabajo

1. No reemplaces las estructuras principales por `std::unordered_map`, `std::unordered_set`, `std::map`, `std::set` u otra estructura estándar que oculte el algoritmo central.
2. Puedes usar estructuras estándar solo como referencia externa de comparación cuando una prueba o pregunta lo indique explícitamente.
3. No cambies la interfaz principal de la librería salvo que una pregunta lo pida explícitamente.
4. Toda explicación debe mencionar invariante, operación, evidencia y costo.
5. Si modificas una demostración, una prueba o una función auxiliar, marca el cambio con un comentario breve.

```cpp
// MOD-A8-B4: medicion de tombstones despues de eliminaciones
```

6. No basta con ejecutar el programa. Debes poder explicar por qué una operación conserva la tabla en estado válido y por qué su costo es esperado, amortizado o de peor caso.
7. Cuando fuerces colisiones, no asumas que las claves `0, 8, 16, 24` colisionan si la función hash no es identidad. Si el código usa mezcla hash, debes verificar el bucket real o construir claves colisionantes mediante un pequeño experimento.

#### Bloque 1 - Diagnóstico inicial de la Semana 8

Revisa:

* `Semana8/README.md`
* `Semana8/CMakeLists.txt`
* `Semana8/include/Capitulo9.h`

Ejecuta desde la raíz de la librería:

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug -R semana8 --output-on-failure
```

Responde:

1. ¿Qué targets de demostración aparecen para Semana 8?
2. ¿Qué pruebas públicas e internas aparecen?
3. ¿Qué archivos incluye `Capitulo9.h`?
4. ¿Qué relación conceptual hay entre Semana 5, Semana 6, Semana 7 y Semana 8?
5. ¿Por qué no es correcto decir que una tabla hash siempre tiene costo `O(1)` garantizado?
6. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?
7. ¿Qué diferencia práctica hay entre compilar todo el proyecto y compilar solo los targets de Semana 8?.

Entrega en este bloque:

* Una tabla con comando ejecutado, resultado, error si hubo e interpretación.
* Una lista breve de los archivos que revisaste primero.
* Una conclusión inicial de máximo 8 líneas sobre el estado de la semana.

#### Bloque 2 - Núcleo conceptual de hashing y diccionarios

Revisa:

* `Semana8/lecturas/Notas.md`
* `Semana8/lecturas/GuiaHashing.md`
* `Semana8/include/Dictionary.h`
* `Semana8/include/Entry.h`
* `Semana8/include/HashCode.h`
* `Semana8/include/HashStats.h`
* `Semana8/include/RehashPolicy.h`

Responde:

1. Define con precisión qué es un diccionario abstracto.
2. Explica la diferencia entre diccionario, mapa, conjunto y tabla hash.
3. Explica qué representa un `Entry<K,V>`.
4. Explica qué hace una función hash.
5. Explica por qué pueden existir colisiones aunque la función hash sea razonable.
6. Explica qué significa factor de carga.
7. Explica qué significa rehashing.
8. Explica qué mide `HashStats`.
9. Explica qué decide `RehashPolicy`.
10. Compara el costo esperado de una tabla hash con el costo garantizado de AVL y Red-Black Tree.

Entrega en este bloque:

* Una tabla conceptual con las columnas: concepto, definición, archivo relacionado y ejemplo.
* Una explicación de máximo 12 líneas sobre por qué hashing no reemplaza completamente a los árboles balanceados.

#### Bloque 3 - Chaining: buckets, colisiones y longitud máxima

Revisa:

* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/ArrayStack.h`
* `Semana8/include/HashCode.h`
* `Semana8/demos/demo_chained.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_chained
```

Construye una tabla con estas columnas:

* Operación
* Clave
* Bucket calculado
* Tamaño del bucket antes
* Tamaño del bucket después
* Colisión observada
* `loadFactor()`
* `longestBucket()`

Responde:

1. ¿Qué diferencia hay entre el arreglo principal y los buckets?
2. ¿Por qué chaining puede almacenar más elementos que la cantidad de posiciones del arreglo principal?
3. ¿Qué significa que un bucket crezca demasiado?
4. ¿Por qué `longestBucket()` es una métrica importante?
5. ¿En qué caso la búsqueda en chaining deja de parecerse a `O(1)` esperado?
6. ¿Qué costo tiene recorrer un bucket de longitud `k`?
7. ¿Qué parte del costo depende de la función hash y qué parte depende de la distribución de claves?.

Entrega en este bloque:

* Salida relevante de `demo_chained.cpp`.
* Tabla de operaciones.
* Dibujo de una tabla hash con al menos 8 buckets y 10 claves.
* Explicación breve de costo esperado y peor caso.

#### Bloque 4 - Colisiones controladas sin asumir hash de identidad

Revisa:

* `Semana8/include/HashCode.h`
* `Semana8/demos/demo_hash_functions.cpp`
* `Semana8/demos/demo_collision_strategies.cpp`

Modifica o crea una demostración auxiliar que busque claves enteras que caigan en el mimso bucket para una capacidad fija `m`. No asumas que `x % m` es el bucket final si antes se aplica una mezcla hash.

Puedes usar una función auxiliar con esta idea:

```cpp
std::vector<int> findCollidingKeys(std::size_t capacity,
                                   std::size_t targetBucket,
                                   std::size_t needed);
```

La función debe probar claves enteras desde `0` hacia adelante y quedarse con las que cumplan:

```cpp
hashCode(x) % capacity == targetBucket
```

Responde:

1. ¿Por qué `0, 8, 16, 24` solo garantiza colisión si la función hash efectiva es `h(x) = x mod m`?
2. ¿Qué ocurre si antes se aplica una mezcla como `hashCode(x)`?
3. ¿Qué claves encontraste para un mismo bucket con capacidad `8` o `16`?
4. ¿Cómo cambia el experimento si usas cadenas en lugar de enteros?
5. ¿Por qué este bloque es importante para defender evidencia experimental honesta?.

Entrega en este bloque:

* Código de la función auxiliar.
* Lista de claves encontradas.
* Tabla con clave, valor hash normalizado y bucket.
* Evidencia de que esas claves sí producen colisiones en tu ejecución.

#### Bloque 5 - Linear probing: estados, sondeo y tombstones

Revisa:

* `Semana8/include/LinearHashTable.h`
* `Semana8/include/Bitmap.h`
* `Semana8/include/HashStats.h`
* `Semana8/demos/demo_linear.cpp`
* `Semana8/demos/demo_tombstones.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_linear
./build-debug/Semana8/sem8_demo_tombstones
```

Construye una tabla con estas columnas:

* Operación
* Clave
* Posición hash inicial
* Secuencia de sondeo
* Estado final de la celda
* `size`
* `occupied`
* `loadFactor()`
* `occupiedFactor()`
* `tombstoneCount()`

Responde:

1. ¿Qué representan los estados `Empty`, `Filled` y `Deleted`?
2. ¿Por qué `Deleted` no puede tratarse igual que `Empty`?
3. ¿Qué diferencia hay entre `size` y `occupied`?
4. ¿Por qué `loadFactor()` y `occupiedFactor()` pueden divergir después de muchas eliminaciones?
5. ¿Qué problema aparece si se acumulan demasiados tombstones?
6. ¿Cuándo debe hacerse rehashing por carga ocupada aunque haya pocos elementos activos?
7. ¿Qué costo tiene una búsqueda fallida cuando hay clustering?.

Entrega en este bloque:

* Salida relevante de `demo_linear.cpp` y `demo_tombstones.cpp`.
* Trazado manual de al menos una búsqueda exitosa y una búsqueda fallida.
* Explicación de por qué open addressing necesita una política cuidadosa de eliminación.

#### Bloque 6 - HashtableOA como diccionario `key value`

Revisa:

* `Semana8/include/Dictionary.h`
* `Semana8/include/Entry.h`
* `Semana8/include/HashtableOA.h`
* `Semana8/demos/demo_hashtable_oa.cpp`
* `Semana8/include/Applications.h`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_hashtable_oa
```

Responde:

1. ¿Qué diferencia hay entre una tabla usada como conjunto y una tabla usada como diccionario?
2. ¿Qué representa una clave?
3. ¿Qué representa un valor?
4. ¿Qué debe devolver `get(k)` si la clave existe?
5. ¿Qué debe ocurrir con `remove(k)` si la clave no existe?
6. ¿Qué política usa la implementación cuando se intenta insertar una clave repetida?
7. ¿Por qué una interfaz `put`, `get`, `remove` permite separar el uso del diccionario de su implementación interna?.

Entrega en este bloque:

* Una tabla con operaciones `put`, `get`, `remove`, resultado esperado y evidencia observada.
* Un ejemplo `string` a `int` para conteo de frecuencias.
* Una explicación de cómo cambia el diseño si se desea que `put` actualice el valor de una clave ya existente.

#### Bloque 7 - Comparación de estrategias de colisión

Revisa:

* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/LinearHashTable.h`
* `Semana8/include/QuadraticHashTable.h`
* `Semana8/include/DoubleHashTable.h`
* `Semana8/include/RobinHoodHashTable.h`
* `Semana8/demos/demo_collision_strategies.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_collision_strategies
```

Compara al menos cinco estrategias:

1. Chaining.
2. Linear probing.
3. Quadratic probing.
4. Double hashing.
5. Robin Hood hashing.

Construye una tabla con estas columnas:

* Estrategia
* Representación interna
* Cómo resuelve colisiones
* Métrica más sensible
* Ventaja
* Debilidad
* Costo esperado
* Peor caso

Responde:

1. ¿Qué es clustering primario?
2. ¿Por qué linear probing tiende a formar bloques contiguos?
3. ¿Qué intenta mejorar quadratic probing?
4. ¿Qué intenta mejorar double hashing?
5. ¿Qué intenta equilibrar Robin Hood hashing?
6. ¿Por qué chaining y open addressing no tienen el mismo comportamiento ante carga alta?
7. ¿Qué estrategia elegirías para una tabla pequeña de laboratorio?
8. ¿Qué estrategia elegirías para una carga alta con muchas búsquedas?
9. ¿Qué estrategia se degrada más claramente en presencia de muchas eliminaciones?.

Entrega en este bloque:

* Salida de la demo.
* Tabla comparativa completa.
* Conclusión técnica de máximo 15 líneas.

#### Bloque 8 - Funciones hash, hashing universal y distribución

Revisa:

* `Semana8/include/HashCode.h`
* `Semana8/include/UniversalHash.h`
* `Semana8/demos/demo_hash_functions.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_hash_functions
```

Diseña tres conjuntos de claves:

1. Claves enteras consecutivas.
2. Claves enteras con patrón repetitivo.
3. Claves de texto con prefijos comunes.

Para cada conjunto, mide o reporta:

* cantidad de claves,
* capacidad de tabla,
* número de buckets usados,
* bucket más cargado,
* colisiones observadas,
* comentario sobre la distribución.

Responde:

1. ¿Qué propiedad debe tener una buena función hash?
2. ¿Por qué una función hash determinista puede ser buena para datos comunes y mala para datos adversariales?
3. ¿Qué idea aporta hashing universal?
4. ¿Por qué no se debe evaluar una función hash con un solo conjunto de claves?
5. ¿Qué relación existe entre dispersión y costo esperado?.

Entrega en este bloque:

* Tabla de distribución para los tres conjuntos de claves.
* Comparación entre `hashCode` y `UniversalHash` si la demo lo permite.
* Una conclusión sobre el papel de la función hash en el rendimiento real.

#### Bloque 9 - Rehashing, política de carga y costo amortizado

Revisa:

* `Semana8/include/RehashPolicy.h`
* `Semana8/include/HashStats.h`
* `Semana8/demos/demo_benchmark_load_factor.cpp`
* `Semana8/pruebas_internas/test_rehashing.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_benchmark_load_factor
```

Responde:

1. ¿Qué condición de carga provoca crecimiento?
2. ¿Qué condición puede provocar limpieza por tombstones?
3. ¿Qué condición puede provocar contracción?
4. ¿Por qué rehashing cuesta `O(n)` en el momento en que ocurre?
5. ¿Por qué aun así se habla de costo amortizado?
6. ¿Qué relación hay entre capacidad, factor de carga y número de sondeos?
7. ¿Qué evidencia muestra `HashStats` sobre rehashings?
8. ¿Qué riesgo hay si se permite que el factor de carga sea demasiado alto?.

Entrega en este bloque:

* Tabla con capacidad, número de elementos, factor de carga, rehashes y máximo de sondeos.
* Explicación de costo amortizado.
* Interpretación de al menos una prueba de `test_rehashing.cpp`.

#### Bloque 10 - Aplicaciones de hashing

Revisa:

* `Semana8/include/Applications.h`
* `Semana8/demos/demo_aplicaciones.cpp`

Ejecuta:

```bash
./build-debug/Semana8/sem8_demo_aplicaciones
```

Elige dos aplicaciones y explícalas con trazado manual:

1. `hasDuplicates`.
2. `uniquePreservingOrder`.
3. `firstRepeated`.
4. `frequencyCount`.
5. `wordFrequencyFromText`.
6. `twoSum`.
7. `deduplicateLogs`.
8. `invertedIndex`.

Para cada aplicación elegida, responde:

1. ¿Cuál es el problema de entrada?
2. ¿Cuál es la salida esperada?
3. ¿Qué se guarda en la tabla hash?
4. ¿Qué operación domina el costo?
5. ¿Por qué el costo esperado puede ser lineal?
6. ¿Qué caso podría degradar el rendimiento?
7. ¿Cómo resolverías el mismo problema con AVL o Red-Black Tree?
8. ¿Qué se gana y qué se pierde al usar hashing?.

Entrega en este bloque:

* Dos trazados manuales.
* Evidencia de ejecución.
* Comparación de costo esperado con tabla hash frente a costo garantizado con árbol balanceado.

#### Bloque 11 - Modificación controlada de código

Elige una de las siguientes modificaciones. Debes marcar tu cambio con comentario `MOD-A8` y mantener compilación limpia.

#### Opción A - Reporte uniforme de métricas

Crea una función auxiliar para imprimir métricas relevantes de una tabla hash.

```cpp
void printHashStats(const HashStats& stats);
```

La salida debe incluir como mínimo:

* colisiones,
* sondeos totales,
* máximo de sondeos,
* rehashings,
* tombstones si aplica.

#### Opción B - Experimento de colisiones reales

Crea una demo que busque claves que realmente colisionen bajo `hashCode(x) % capacity` y luego las inserte en `ChainedHashTable` o `LinearHashTable`.

#### Opción C - Caso adicional de aplicación

Agrega una aplicación pequeña basada en hashing, por ejemplo:

```cpp
std::vector<std::string> findRepeatedWords(const std::string& text);
```

Debe devolver palabras que aparecen más de una vez, sin usar `std::unordered_map` como estructura principal.

Responde:

1. ¿Qué archivo modificaste?
2. ¿Qué función agregaste?
3. ¿Qué invariante debe mantenerse?
4. ¿Qué prueba o demo evidencia el cambio?
5. ¿Qué costo tiene la función agregada?
6. ¿Por qué tu modificación no oculta el algoritmo central?.

Entrega en este bloque:

* Fragmento de código modificado.
* Evidencia de compilación.
* Evidencia de ejecución.
* Explicación de costo.

#### Bloque 12 - Comparación final con BST, AVL, Red-Black Tree y Treap

Revisa:

* `Semana5/include/BinarySearchTree.h`
* `Semana6/include/Treap.h`
* `Semana7/include/AVL.h`
* `Semana7/include/RedBlackTree.h`
* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/LinearHashTable.h`
* `Semana8/include/HashtableOA.h`

Construye una matriz de decisión con estas columnas:

* Estructura
* Mantiene orden
* Búsqueda promedio
* Búsqueda peor caso
* Inserción
* Eliminación
* Memoria adicional
* Ventaja principal
* Riesgo principal
* Caso de uso recomendado

Incluye:

1. BST simple.
2. Treap.
3. AVL.
4. Red-Black Tree.
5. ChainedHashTable.
6. LinearHashTable.
7. HashtableOA.

Responde:

1. ¿Cuándo elegirías una tabla hash?
2. ¿Cuándo elegirías AVL?
3. ¿Cuándo elegirías Red-Black Tree?
4. ¿Cuándo elegirías Treap?
5. ¿Por qué una tabla hash no sirve directamente para consultas por rango?
6. ¿Por qué un árbol balanceado sí permite recorrer claves en orden?
7. ¿Qué significa que una estructura tenga costo esperado y otra tenga costo garantizado?
8. ¿Qué estructura preferirías para un índice de palabras sin orden?
9. ¿Qué estructura preferirías para un ranking ordenado por clave?
10. ¿Qué estructura preferirías si necesitas `lowerBound` y `upperBound`?.

Entrega en este bloque:

* Matriz de decisión.
* Conclusión final de máximo 20 líneas.
* Un ejemplo concreto donde hashing gana.
* Un ejemplo concreto donde AVL o Red-Black Tree gana.

#### Producto final esperado

El archivo `Actividad8-CC232.md` debe contener:

1. Respuestas completas por bloque.
2. Tablas solicitadas.
3. Evidencia de comandos ejecutados.
4. Fragmentos de código modificados si corresponde.
5. Salidas relevantes de demostraciones y pruebas.
6. Trazados manuales de colisiones, sondeos y tombstones.
7. Comparación final contra BST, Treap, AVL y Red-Black Tree.
8. Conclusión técnica personal.

Además, si modificaste código, entrega los archivos cambiados y menciona exactamente qué cambiaste.
