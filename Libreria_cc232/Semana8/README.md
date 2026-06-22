### Semana 8 - Hashing, tablas hash y aplicaciones avanzadas

Esta carpeta continúa el trabajo de `Semana5`, `Semana6` y `Semana7` dentro de `Libreria_cc232`. El objetivo principal es estudiar cómo implementar diccionarios no ordenados mediante hashing, separando con claridad cinco ideas que suelen confundirse:

* una **interfaz de diccionario** define operaciones como insertar, buscar y eliminar,
* una **función hash** transforma claves en posiciones de una tabla,
* una **estrategia de colisiones** decide qué ocurre cuando dos claves llegan a la misma posición,
* el **factor de carga** controla cuándo la tabla empieza a degradarse,
* el **rehashing** reconstruye la tabla para recuperar eficiencia esperada.

La semana se organiza como una continuación natural de las semanas anteriores:

* `Semana5` introduce árboles binarios, BST y estructuras básicas de búsqueda.
* `Semana6` refuerza el contraste entre prioridad, heaps y búsqueda ordenada.
* `Semana7` estudia árboles balanceados, AVL y Red-Black Tree, que garantizan altura logarítmica.
* `Semana8` contrasta esas estructuras ordenadas con tablas hash, que buscan eficiencia esperada constante bajo una buena dispersión.

La idea central es que una tabla hash puede ofrecer operaciones esperadas `O(1)`, pero no por magia: depende de la calidad de la función hash, del manejo de colisiones, de la política de carga, de la eliminación y del rehashing.

#### Contenido principal

La carpeta incluye los siguientes componentes:

* `Dictionary.h`: interfaz abstracta de diccionario.
* `Entry.h`: par clave-valor usado en implementaciones tipo diccionario.
* `array.h`: arreglo base estilo Morin para estructuras con almacenamiento contiguo.
* `ArrayStack.h`: arreglo dinámico usado como lista de cubeta en chaining.
* `Bitmap.h`: soporte para marcas de eliminación perezosa.
* `PrimeUtils.h`: utilidades para elegir capacidades primas en tablas hash.
* `HashCode.h`: funciones de dispersión, normalización y conversión de claves.
* `HashStats.h`: métricas de colisiones, sondeos, rehashings y tombstones.
* `RehashPolicy.h`: política configurable de crecimiento, limpieza y contracción.
* `UniversalHash.h`: familia MAD para hashing universal.
* `ChainedHashTable.h`: tabla hash con encadenamiento separado.
* `LinearHashTable.h`: tabla hash con direccionamiento abierto y sondeo lineal.
* `HashtableOA.h`: tabla hash tipo diccionario `key -> value`, cercana a la línea de Deng.
* `QuadraticHashTable.h`: direccionamiento abierto con sondeo cuadrático.
* `DoubleHashTable.h`: direccionamiento abierto con doble hashing.
* `RobinHoodHashTable.h`: direccionamiento abierto con estrategia Robin Hood.
* `Applications.h`: aplicaciones pequeñas basadas en hashing.
* `Capitulo9.h`: header agregador de la semana.

#### Qué continúa de `Semana5`, `Semana6` y `Semana7`

`Semana8` debe leerse como continuación conceptual y práctica de las semanas anteriores.

Desde `Semana5` se retoman estas ideas:

* búsqueda en estructuras lineales y enlazadas,
* diferencias entre acceso secuencial y acceso directo,
* árboles binarios de búsqueda como diccionarios ordenados,
* complejidad dependiente de la altura en un BST.

Desde `Semana6` se retoman estas ideas:

* comparación entre representación e interfaz,
* uso de estructuras basadas en arreglos,
* análisis de operaciones dominantes,
* medición práctica mediante demos y pruebas.

Desde `Semana7` se retoman estas ideas:

* comparación entre BST común, AVL y Red-Black Tree,
* garantía `O(log n)` mediante invariantes estructurales,
* defensa de decisiones de diseño,
* contraste entre eficiencia garantizada y eficiencia esperada.

La relación conceptual puede leerse así:

```text
Semana5
└── árboles binarios, BST y búsqueda ordenada básica
Semana6
└── priority queues, heaps, representación y comparación experimental
Semana7
└── AVL, Red-Black Tree, balanceo y altura logarítmica
Semana8
└── hashing, tablas hash, colisiones, carga, rehashing y diccionarios no ordenados
```

#### Aclaración importante sobre tablas hash y diccionarios

En C++ conviene distinguir tres niveles:

* una interfaz de diccionario describe operaciones,
* una tabla hash es una representación concreta,
* una política de colisiones forma parte del diseño interno de esa representación.

Por eso, no se debe decir simplemente que "hashing es un diccionario". Lo correcto es decir que una tabla hash es una forma de implementar diccionarios, mapas o conjuntos no ordenados.

En esta entrega aparecen dos usos pedagógicos:

```text
Conjunto hash
└── ChainedHashTable, LinearHashTable, QuadraticHashTable, DoubleHashTable, RobinHoodHashTable

Diccionario key -> value
└── Dictionary, Entry, HashtableOA
```

El primer bloque permite comparar estrategias de colisión sobre conjuntos. El segundo bloque permite trabajar la interfaz formal de diccionario con pares clave-valor.

#### Por qué aparecen varias tablas hash

En esta semana no se incluye una única tabla hash porque el objetivo no es memorizar una implementación, sino comparar decisiones de diseño.

La separación intencional es la siguiente:

* `ChainedHashTable` usa listas por cubeta y tolera colisiones acumulándolas fuera de la tabla principal.
* `LinearHashTable` usa sondeo lineal y muestra el problema del agrupamiento primario.
* `QuadraticHashTable` modifica la secuencia de sondeo para reducir parte del agrupamiento.
* `DoubleHashTable` usa una segunda función hash para mejorar la dispersión del sondeo.
* `RobinHoodHashTable` intenta equilibrar las distancias de búsqueda intercambiando elementos según su distancia al hash original.
* `HashtableOA` conserva una interfaz de diccionario `key -> value` y permite discutir `put`, `get` y `remove` con eliminación perezosa.

Esta diversidad permite observar que todas son "tablas hash", pero no tienen el mismo comportamiento ante carga alta, colisiones, borrados o claves adversariales.

#### Organización práctica

Además de los headers, la carpeta contiene:

* `demos/`: programas pequeños para ejecutar y observar cada estructura.
* `pruebas_publicas/`: pruebas públicas esperadas para validar comportamiento básico.
* `pruebas_internas/`: pruebas adicionales de cobertura, colisiones, rehashing y comparación contra STL.
* `lecturas/Lectura14-Morin.md`: resumen conceptual de hashing y tablas hash.
* `Actividad8-CC232.md`: guía de actividad para ejecutar demos y sustentar decisiones.
* `Ejercicios8-CC232.md`: espacio para ejercicios de la semana.

La estructura base se conserva: no se agregan carpetas nuevas fuera de las usadas por la organización de la semana.

#### Demostraciones incluidos

Los demos principales son:

* `demo_chained.cpp`: uso de chaining, cubetas y longitud máxima de cubeta.
* `demo_linear.cpp`: uso de linear probing, factor activo, factor ocupado y tombstones.
* `demo_hashtable_oa.cpp`: diccionario `string -> int` con tabla hash abierta.
* `demo_aplicaciones.cpp`: aplicaciones de duplicados, two-sum y frecuencia de palabras.
* `demo_collision_strategies.cpp`: comparación entre chaining, linear probing, quadratic probing, double hashing y Robin Hood.
* `demo_hash_functions.cpp`: comparación entre `hashCode` y `UniversalHash`.
* `demo_tombstones.cpp`: efecto de eliminación perezosa en direccionamiento abierto.
* `demo_benchmark_load_factor.cpp`: experimento simple con distintas políticas de carga.

#### Aplicaciones incluidas

`Applications.h` incluye funciones pequeñas que muestran usos reales de hashing:

* `hasDuplicates`: detectar si una secuencia contiene repetidos.
* `uniquePreservingOrder`: eliminar duplicados preservando el orden de aparición.
* `firstRepeated`: encontrar el primer elemento repetido.
* `frequencyCount`: contar frecuencias de elementos.
* `wordFrequencyFromText`: contar palabras desde texto normalizado.
* `twoSum`: resolver búsqueda de complemento en tiempo esperado lineal.
* `deduplicateLogs`: eliminar registros repetidos preservando orden.
* `invertedIndex`: construir un índice invertido simple para documentos.

Estas aplicaciones conectan la estructura con problemas concretos y ayudan a sustentar cuándo conviene usar hashing en lugar de una estructura ordenada.

#### Nota de diseño

La implementación mantiene el estilo header-only usado en las semanas anteriores para facilitar la integración dentro de `Libreria_cc232`. Las estructuras pueden estudiarse como módulos separados, pero se conectan mediante una idea común: acceso eficiente por clave mediante dispersión.

La separación de responsabilidades es la siguiente:

* `Dictionary` define la interfaz conceptual de diccionario.
* `Entry` representa el par clave-valor.
* `HashCode` y `UniversalHash` definen formas de convertir claves en direcciones hash.
* `RehashPolicy` decide cuándo crecer, limpiar o contraer.
* `HashStats` registra evidencia experimental del comportamiento.
* Las tablas concretas implementan distintas estrategias de resolución de colisiones.
* `Applications` usa las tablas hash en problemas pequeños y verificables.

Esto ayuda a defender oralmente qué parte del comportamiento corresponde a la interfaz, qué parte corresponde a la función hash y qué parte corresponde a la política de resolución de colisiones.

#### Relación con las lecturas

Esta semana está alineada con el bloque de diccionarios no ordenados y hashing. El proyecto conecta las lecturas así:

* Deng: ADT diccionario, operaciones `get`, `put` y `remove`.
* Deng: tabla hash, función hash, cubetas, colisiones y dirección hash.
* Deng: eliminación perezosa y rehashing en direccionamiento abierto.
* Morin: `ChainedHashTable` como encadenamiento separado.
* Morin: `LinearHashTable` como direccionamiento abierto con sondeo lineal.
* Extensión de la librería: sondeo cuadrático, doble hashing, Robin Hood hashing, estadísticas y aplicaciones.
* Puente a semanas anteriores: comparación con BST, AVL y Red-Black Tree.

#### Qué no se incluye como núcleo

No se incluye `Skiplist` ni `Quadlist` como núcleo de esta semana. Aunque aparecen dentro del capítulo de diccionarios de Deng, corresponden mejor a una comparación posterior entre balanceo probabilístico y balanceo determinista.

Aquí el foco es:

```text
hashing + chaining + open addressing + load factor + tombstones + rehashing
```

#### ¿Desde dónde se compila?

Para mantener la misma forma de trabajo de la librería completa, la recomendación es compilar desde la raíz del proyecto:

```bash
cd Libreria_cc232
```

Ese será el supuesto de todos los comandos principales. En esa ubicación debe existir, como mínimo, la carpeta:

```text
Libreria_cc232/
└── Semana8/
```

Si `Semana8` ya está integrada al `CMakeLists.txt` principal de `Libreria_cc232`, no entres a `Semana8/` para compilar. Entra a la raíz, configura el proyecto una sola vez y luego compila o ejecuta los targets de la semana.

#### Aclaración sobre `build-debug`

El nombre de la carpeta `build-debug` es solo una convención. No activa Debug por sí mismo.

Para compilar realmente en modo Debug:

* en Linux hay que pasar `-DCMAKE_BUILD_TYPE=Debug`,
* en Windows con Visual Studio hay que usar `--config Debug`.

### Linux

#### 1. Configurar todo el proyecto en modo Debug

```bash
cd Libreria_cc232
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
```

Este comando prepara el árbol de compilación completo del proyecto.

#### 2. Compilar solo la semana 8

Si quieres compilar únicamente los targets principales de esta semana:

```bash
cmake --build build-debug --target \
  sem8_demo_chained \
  sem8_demo_linear \
  sem8_demo_hashtable_oa \
  sem8_demo_aplicaciones \
  sem8_demo_collision_strategies \
  sem8_demo_hash_functions \
  sem8_demo_tombstones \
  sem8_demo_benchmark_load_factor \
  sem8_test_public \
  sem8_test_internal \
  sem8_test_tombstones \
  sem8_test_collision_patterns \
  sem8_test_rehashing \
  sem8_test_randomized_against_stl
```

Si prefieres compilar todo el repositorio:

```bash
cmake --build build-debug
```

#### 3. Ejecutar todas las pruebas de la semana 8

```bash
ctest --test-dir build-debug -R semana8 --output-on-failure
```

#### 4. Ejecutar demostraciones paso a paso

##### Chaining

```bash
./build-debug/Semana8/sem8_demo_chained
```

##### Linear probing

```bash
./build-debug/Semana8/sem8_demo_linear
```

##### Hashtable key -> value

```bash
./build-debug/Semana8/sem8_demo_hashtable_oa
```

##### Aplicaciones

```bash
./build-debug/Semana8/sem8_demo_aplicaciones
```

##### Estrategias de colisión

```bash
./build-debug/Semana8/sem8_demo_collision_strategies
```

##### Funciones hash

```bash
./build-debug/Semana8/sem8_demo_hash_functions
```

##### Tombstones

```bash
./build-debug/Semana8/sem8_demo_tombstones
```

##### Benchmark de factor de carga

```bash
./build-debug/Semana8/sem8_demo_benchmark_load_factor
```

### Windows con Visual Studio

#### 1. Configurar todo el proyecto

```powershell
cd Libreria_cc232
cmake -S . -B build-debug
```

#### 2. Compilar solo la semana 8 en modo Debug

```powershell
cmake --build build-debug --config Debug --target `
  sem8_demo_chained `
  sem8_demo_linear `
  sem8_demo_hashtable_oa `
  sem8_demo_aplicaciones `
  sem8_demo_collision_strategies `
  sem8_demo_hash_functions `
  sem8_demo_tombstones `
  sem8_demo_benchmark_load_factor `
  sem8_test_public `
  sem8_test_internal `
  sem8_test_tombstones `
  sem8_test_collision_patterns `
  sem8_test_rehashing `
  sem8_test_randomized_against_stl
```

Si prefieres compilar todo el repositorio:

```powershell
cmake --build build-debug --config Debug
```

#### 3. Ejecutar todas las pruebas de la semana 8

```powershell
ctest --test-dir build-debug -C Debug -R semana8 --output-on-failure
```

#### 4. Ejecutar demos paso a paso

##### Chaining

```powershell
.\build-debug\Semana8\Debug\sem8_demo_chained.exe
```

##### Linear probing

```powershell
.\build-debug\Semana8\Debug\sem8_demo_linear.exe
```

##### Hashtable key -> value

```powershell
.\build-debug\Semana8\Debug\sem8_demo_hashtable_oa.exe
```

##### Aplicaciones

```powershell
.\build-debug\Semana8\Debug\sem8_demo_aplicaciones.exe
```

##### Estrategias de colisión

```powershell
.\build-debug\Semana8\Debug\sem8_demo_collision_strategies.exe
```

##### Funciones hash

```powershell
.\build-debug\Semana8\Debug\sem8_demo_hash_functions.exe
```

##### Tombstones

```powershell
.\build-debug\Semana8\Debug\sem8_demo_tombstones.exe
```

##### Benchmark de factor de carga

```powershell
.\build-debug\Semana8\Debug\sem8_demo_benchmark_load_factor.exe
```

### Targets principales

#### Demos

* `sem8_demo_chained`
* `sem8_demo_linear`
* `sem8_demo_hashtable_oa`
* `sem8_demo_aplicaciones`
* `sem8_demo_collision_strategies`
* `sem8_demo_hash_functions`
* `sem8_demo_tombstones`
* `sem8_demo_benchmark_load_factor`

#### Pruebas

* `sem8_test_public`
* `sem8_test_internal`
* `sem8_test_tombstones`
* `sem8_test_collision_patterns`
* `sem8_test_rehashing`
* `sem8_test_randomized_against_stl`

### Compilación aislada de `Semana8`

También se puede compilar desde la carpeta `Semana8`:

```bash
cd Libreria_cc232/Semana8
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug --output-on-failure
```

En ese caso, los ejecutables quedarán dentro de:

```text
Semana8/build-debug/
```

### Qué debes poder explicar

Al terminar esta semana, el estudiante debería poder sustentar:

1. Qué problema resuelve un diccionario no ordenado.
2. Qué diferencia hay entre diccionario, mapa, conjunto y tabla hash.
3. Por qué una tabla hash puede tener `O(1)` esperado, pero no `O(1)` garantizado en peor caso.
4. Qué propiedades debe tener una buena función hash.
5. Por qué aparecen colisiones aunque la función hash sea razonable.
6. Cómo funciona chaining y qué ocurre cuando una cubeta acumula muchos elementos.
7. Cómo funciona open addressing y por qué no usa listas externas.
8. Qué problema produce el clustering en linear probing.
9. Qué mejora quadratic probing respecto de linear probing.
10. Qué mejora double hashing respecto de una sola secuencia de sondeo.
11. Qué intenta equilibrar Robin Hood hashing.
12. Qué diferencia hay entre `loadFactor()` y `occupiedFactor()`.
13. Por qué una celda `Deleted` no puede tratarse igual que una celda vacía.
14. Cuándo se debe hacer rehashing y qué costo tiene.
15. Cómo interpretar métricas como colisiones, sondeos, tombstones y rehashings.
16. Cuándo conviene elegir una tabla hash en lugar de BST, AVL o Red-Black Tree.
17. Cuándo conviene elegir AVL o Red-Black Tree en lugar de una tabla hash.
18. Cómo aplicar hashing a duplicados, conteo de frecuencias, two-sum, logs e índice invertido.
19. Por qué la comparación experimental debe considerar tipo de claves, orden de inserción, carga y patrón de búsqueda.
20. Qué parte del diseño corresponde a la interfaz, qué parte a la función hash y qué parte a la estrategia de colisiones.
