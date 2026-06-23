### Diccionarios y tablas hash - Deng
### Resumen

Esta lectura presenta la parte del capítulo 9 de Deng que sirve como base para la Semana 8 de CC232. El capítulo completo trata sobre diccionarios, listas de salto y tablas hash, pero la Semana 8 toma principalmente la línea de diccionarios implementados mediante hashing.

La idea principal es estudiar cómo un diccionario permite asociar una clave con un valor sin exigir que las claves estén ordenadas. En árboles de búsqueda como BST, AVL o Red-Black Tree, las claves se comparan por orden y la estructura mantiene un invariante ordenado. En una tabla hash, en cambio, la clave se transforma en una dirección de tabla mediante `hashCode()` y una hash function. El acceso deja de depender de recorridos ordenados y pasa a depender de dispersión, colisiones, factor de carga y rehashing.

Deng introduce el TAD `Dictionary` con operaciones `put(key, value)`, `get(key)` y `remove(key)`. Luego muestra que una tabla hash puede implementar ese diccionario usando un arreglo de buckets, una función hash que mapea claves a direcciones y una estrategia para resolver conflictos cuando dos claves producen el mismo índice. La implementación base de Deng usa open addressing, linear probing, marcas de eliminación perezosa mediante `lazyRemoval`, búsqueda con `probe4Hit`, inserción con `probe4Free` y reconstrucción con `rehash()`.

Para Semana 8, esta lectura se conecta directamente con `Dictionary.h`, `Entry.h`, `HashCode.h`, `UniversalHash.h`, `RehashPolicy.h`, `HashStats.h`, `ChainedHashTable.h`, `LinearHashTable.h`, `HashtableOA.h` y las aplicaciones de hashing. La parte de Skiplist y Quadlist aparece en el capítulo de Deng, pero no es el núcleo de Semana 8.

### Introducción

Un diccionario es una estructura que almacena entradas formadas por una clave y un valor. La clave permite localizar el valor asociado. En programación, esta idea aparece en mapas, arreglos asociativos, tablas de símbolos, diccionarios de Python, mapas de Java o estructuras `key -> value` usadas en bases de datos, compiladores, caches y procesamiento de texto.

La diferencia central con una estructura ordenada es que un diccionario no necesita que las claves puedan compararse por menor o mayor. Para buscar por clave exacta basta con saber cuándo dos claves son iguales. Esta observación permite abandonar el modelo basado exclusivamente en comparaciones y abre la puerta a hashing.

Hashing busca construir una asociación entre el valor lógico de una clave y una dirección física dentro de un arreglo. Si esa asociación distribuye bien las claves, las operaciones de búsqueda, inserción y eliminación pueden ejecutarse en tiempo esperado constante. Esta eficiencia depende del diseño completo de la tabla, no solo de una fórmula aislada.

La lectura debe entenderse como un puente entre dos formas de implementar diccionarios. La primera usa orden y balance, como en AVL o Red-Black Tree. La segunda usa dispersión y resolución de colisiones, como en tablas hash. Ambas implementan operaciones de diccionario, pero sus invariantes y sus criterios de rendimiento son distintos.

### Desarrollo

#### 1. Diccionario como TAD

Deng comienza definiendo el diccionario como un conjunto de entradas. Cada entrada contiene una clave y un valor. La clave identifica la entrada dentro de la estructura, y el valor es el dato asociado.

Las operaciones estándar son:

    get(key)
    put(key, value)
    remove(key)
    size()

`get(key)` busca una entrada con la clave dada. Si existe, devuelve el valor asociado. Si no existe, devuelve una marca de ausencia. `put(key, value)` intenta insertar o asociar una clave con un valor. `remove(key)` elimina la entrada que tiene la clave buscada. `size()` informa cuántas entradas hay en el diccionario.

En Semana 8, esta abstracción se refleja en `Dictionary.h` y `Entry.h`. `Dictionary.h` define la interfaz conceptual y `Entry.h` representa el par `key -> value`. La estructura concreta puede cambiar, pero la interfaz permite razonar sobre el problema a nivel abstracto.

#### 2. Diccionario, mapa y repetición de claves

Deng distingue entre diccionario y mapa, aunque luego trabaja con una interfaz unificada. En algunos contextos, un diccionario puede permitir varias entradas con la misma clave. En otros, como un mapa, cada clave aparece a lo más una vez.

Esta diferencia importa porque afecta el significado de `put`. Si una clave ya existe, una implementación puede reemplazar el valor anterior, aceptar una entrada repetida o rechazar la inserción. En el capítulo, Deng señala que las tablas hash se tratan de forma más cercana a un mapa, donde las claves repetidas se prohíben.

En Semana 8, esta decisión aparece en `HashtableOA` y en las aplicaciones. Por ejemplo, en conteo de frecuencias, si una palabra ya existe, la aplicación puede hacer `get`, luego actualizar el conteo. Según la política de la tabla, eso puede hacerse reemplazando el valor o eliminando e insertando de nuevo.

#### 3. Entrada `key -> value`

La unidad básica del diccionario es la entrada. Conceptualmente, una entrada puede representarse como:

    Entry<K, V>
        key
        value

La clave no necesita ser comparable por orden, pero sí debe ser comparable por igualdad. Esto es suficiente para responder si una entrada encontrada corresponde a la clave buscada.

En hashing, la clave cumple dos roles. Primero, permite calcular una dirección mediante `hashCode()` y la hash function. Segundo, permite confirmar igualdad cuando se encuentra una entrada candidata. Esto es importante porque dos claves diferentes pueden producir la misma dirección hash.

En Semana 8, esta idea se usa en `HashtableOA.h`, donde la tabla almacena asociaciones `K -> V`. También aparece en aplicaciones como frecuencia de palabras, `twoSum` e índice invertido, donde se usan claves como `std::string` o `int` y valores como contadores, posiciones o listas de documentos.

#### 4. Por qué no basta un arreglo directo

Deng usa ejemplos como matrículas, teléfonos e IPs para explicar por qué no siempre se puede reservar un arreglo con una celda por cada clave posible.

Si los códigos de estudiantes están en un rango compacto y conocido, puede existir una función perfecta como:

    hash(key) = key - base

En ese caso, cada clave válida va a una celda única y no hay desperdicio significativo. Pero en aplicaciones reales el universo de claves suele ser enorme. Para teléfonos de 8 dígitos, direcciones IP o identificadores dispersos, reservar una celda por clave posible desperdiciaría memoria.

La tabla hash resuelve este problema usando una tabla mucho más pequeña que el universo de claves. Si hay `N` entradas reales y un universo posible de tamaño `R`, se elige una tabla de tamaño `M`, normalmente con:

    R >> M > N

La hash function comprime el espacio de claves en el espacio de direcciones de la tabla.

#### 5. Tabla hash y bucket array

Una tabla hash se implementa mediante un arreglo de buckets. Cada bucket es una posición del arreglo que puede almacenar una entrada o participar en una estrategia de resolución de colisiones.

Si la tabla tiene capacidad `M`, sus direcciones válidas son:

    0, 1, 2, ..., M - 1

La hash function asigna cada clave a una dirección dentro de ese rango:

    hash() : key -> hash(key)

En Semana 8, esta idea aparece de dos formas. En `ChainedHashTable`, cada bucket puede contener una lista de elementos. En `LinearHashTable` y `HashtableOA`, cada posición funciona como un slot que almacena como máximo una entrada activa.

La diferencia entre bucket y slot es útil. En chaining, el índice apunta a un bucket que puede crecer como lista. En open addressing, el índice apunta a un slot y, si está ocupado, se busca otro slot dentro del mismo arreglo.

#### 6. Función hash

La función hash establece la correspondencia entre la clave y la dirección de tabla. Deng destaca tres condiciones básicas para una buena función hash.

Primero, debe ser determinista. La misma clave debe producir siempre la misma dirección mientras la tabla no cambie de configuración.

Segundo, debe ser rápida. Si calcular la dirección cuesta demasiado, se pierde la ventaja de usar una tabla hash.

Tercero, debe distribuir las claves sobre el espacio de direcciones disponible. Si muchas claves terminan en la misma región de la tabla, aumentan las colisiones y las operaciones se degradan.

En Semana 8, la función hash se separa en dos capas:

    key -> hashCode(key) -> table index

`HashCode.h` produce el código hash de una clave. Luego la tabla reduce ese código al rango de direcciones disponible, por ejemplo mediante módulo o una función universal.

#### 7. Colisiones

Una colisión ocurre cuando dos claves distintas producen la misma dirección de tabla:

    x != y
    hash(x) = hash(y)

Las colisiones son inevitables cuando el universo de claves es mayor que la tabla. Por eso una tabla hash real no se define solo por su función hash, sino también por su estrategia de resolución de colisiones.

Deng desarrolla esta idea con open addressing, donde las colisiones se resuelven buscando otra posición dentro del mismo arreglo. Semana 8 amplía la comparación con varias estrategias: separate chaining, linear probing, quadratic probing, double hashing y Robin Hood hashing.

El punto pedagógico es que `O(1)` no significa ausencia de colisiones. Significa que, bajo buenas condiciones de dispersión y carga, el costo esperado de resolver esas colisiones es constante.

#### 8. Factor de carga

El factor de carga mide qué tan llena está una tabla hash. En el modelo básico de Deng se expresa como:

    lambda = N / M

donde `N` es el número de entradas almacenadas y `M` es la capacidad de la tabla.

A medida que `lambda` crece, aumentan las colisiones y las cadenas de sondeo. Por eso la tabla debe crecer antes de quedar demasiado ocupada. Deng usa el umbral del 50 por ciento para activar rehashing en su implementación base.

En Semana 8, este concepto se vuelve más preciso. Además de `loadFactor`, se usa `occupiedFactor` cuando hay open addressing con tombstones. Esto permite distinguir entre elementos reales y slots ocupados por marcas de borrado.

#### 9. Open addressing en Deng

La tabla hash de Deng usa una estructura parecida a esta:

    Entry<K, V>** ht
    int M
    int N
    Bitmap* lazyRemoval

`ht` es el arreglo de buckets. `M` es la capacidad. `N` es el número de entradas reales. `lazyRemoval` es un bitmap que registra marcas de eliminación perezosa.

La tabla define operaciones internas:

    probe4Hit(k)
    probe4Free(k)
    rehash()

`probe4Hit(k)` busca una entrada cuya clave coincida con `k`. `probe4Free(k)` busca una posición libre para insertar. `rehash()` reconstruye la tabla cuando el factor de carga es demasiado alto.

En Semana 8, estas ideas aparecen en `LinearHashTable.h` y `HashtableOA.h`. La implementación moderna puede usar estados explícitos como `Empty`, `Filled` y `Deleted`, o un bitmap para recordar qué posiciones fueron eliminadas.

#### 10. Linear probing

Deng toma como ejemplo el sondeo lineal. Si una clave `k` produce la dirección inicial:

    r = hashCode(k) % M

entonces se revisa `r`. Si esa posición está ocupada, se prueba:

    r + 1
    r + 2
    r + 3

Los índices se toman módulo `M`, para que el recorrido vuelva al inicio cuando llega al final del arreglo.

El sondeo lineal es simple y eficiente en memoria, pero puede formar clusters. Un cluster es un bloque de posiciones ocupadas consecutivas. Si una búsqueda cae dentro de un cluster largo, debe examinar muchos slots antes de encontrar la clave o una celda que permita detenerse.

En Semana 8, esto se estudia en `LinearHashTable.h` y en los demos de linear probing, tombstones y benchmark por factor de carga.

#### 11. `probe4Hit`

`probe4Hit(k)` recorre la cadena de sondeo correspondiente a la clave `k` para encontrar una entrada coincidente. Su tarea no es encontrar cualquier bucket, sino una entrada cuya clave sea igual a `k`.

En open addressing, la búsqueda no puede detenerse simplemente al encontrar un slot marcado como eliminado. Debe continuar hasta encontrar la clave o hasta encontrar una posición que pruebe que la clave nunca pudo haber sido insertada más adelante.

Esto conecta con la idea de tombstones. Una marca de eliminación perezosa no es un elemento real, pero tampoco equivale a un `null` definitivo para búsqueda.

En Semana 8, esta lógica se ve en las funciones internas de búsqueda de `LinearHashTable` y `HashtableOA`, donde el bucle de sondeo avanza hasta encontrar la clave, un estado vacío o completar la tabla.

#### 12. `probe4Free`

`probe4Free(k)` busca la primera posición libre disponible para insertar una nueva entrada. En la versión de Deng, se parte de:

    hashCode(k) % M

Luego se avanza linealmente hasta encontrar una cubeta vacía.

La diferencia con `probe4Hit` es que la inserción busca espacio, mientras que la búsqueda busca coincidencia de clave. Para insertar correctamente, la tabla debe garantizar que exista algún espacio libre. Por eso el factor de carga debe mantenerse bajo control.

En Semana 8, esta idea aparece en las rutinas de inserción de `LinearHashTable` y `HashtableOA`. También se conecta con `RehashPolicy.h`, que decide cuándo la tabla ya no debe aceptar más inserciones sin reconstruirse.

#### 13. Eliminación perezosa

La eliminación perezosa evita romper la cadena de sondeo. Si una entrada se elimina y se borra físicamente como si nunca hubiera existido, búsquedas futuras podrían detenerse antes de llegar a claves que fueron insertadas después de una colisión.

Por eso Deng usa un `Bitmap` llamado `lazyRemoval`. Este bitmap marca que en una posición hubo una entrada eliminada. La entrada ya no está activa, pero la marca conserva información para la búsqueda.

En Semana 8, el mismo concepto aparece como `Deleted` o tombstone. Un slot `Deleted` significa:

    aquí hubo una entrada
    ahora no cuenta como elemento activo
    una búsqueda no debe detenerse aquí
    una inserción puede reutilizarlo bajo ciertas condiciones

Esta idea es esencial para entender por qué `remove` en open addressing no es simplemente asignar `null`.

#### 14. Rehashing

Deng define `rehash()` como una reconstrucción de la tabla. Cuando el factor de carga supera cierto umbral, se crea una nueva tabla de mayor capacidad y se reinsertan las entradas activas.

No basta con copiar el arreglo antiguo con `memcpy`. Deng explica dos razones. Primero, se heredarían las colisiones originales. Segundo, se podrían romper cadenas de sondeo. Por eso el procedimiento correcto es extraer las entradas una por una y volver a insertarlas usando la nueva capacidad.

El rehashing tiene tres efectos:

    aumenta la capacidad
    redistribuye las entradas
    elimina marcas perezosas antiguas

En Semana 8, `RehashPolicy.h` generaliza esta decisión. `HashStats.h` permite medir cuántas reconstrucciones ocurrieron. Las pruebas internas verifican que la tabla siga siendo correcta después de insertar, eliminar y reconstruir.

#### 15. `hashCode()` como conversión intermedia

Deng separa el mapeo de una clave arbitraria en dos pasos. Primero se convierte la clave en un entero mediante `hashCode()`. Luego la función hash transforma ese entero en una dirección de tabla.

El esquema es:

    key -> hashCode(key) -> hash address

Esta separación permite que la tabla acepte claves que no son enteros, como caracteres, cadenas, objetos compuestos o registros. `hashCode()` debe ser consistente con igualdad. Si dos claves son iguales, deben producir el mismo código hash.

Deng presenta conversiones para tipos comunes. Para `char` e `int`, puede usarse una representación entera directa. Para `long long`, conviene combinar partes para no perder bits. Para cadenas, se procesa cada carácter, usando desplazamientos y suma para conservar información del orden y del contenido.

En Semana 8, `HashCode.h` implementa una versión moderna de esta idea mediante funciones para enteros, cadenas, punteros de cadena, normalización de tokens y combinación de hashes.

#### 16. Cadenas y objetos reales

Las cadenas son claves importantes porque aparecen en diccionarios de palabras, índices invertidos, logs y tablas de símbolos. Un mal `hashCode()` para cadenas puede producir muchas colisiones si ignora caracteres, orden o longitud.

Deng sugiere que, para cadenas, el código hash debe conservar la mayor cantidad posible de información. Por eso procesa los caracteres de izquierda a derecha y mezcla el valor acumulado.

En aplicaciones reales, a veces también se normaliza el texto antes de aplicar hashing. Por ejemplo:

    "Hash,"
    "hash"
    "HASH"

pueden tratarse como la misma palabra si el objetivo es contar frecuencias de texto. En Semana 8, esto se conecta con `normalizeToken()` y con aplicaciones como `wordFrequencyFromText` e `invertedIndex`.

Para objetos compuestos, la regla es definir una clave lógica y combinar los hash codes de sus campos. Si un objeto tiene campos `id`, `name` y `semester`, no necesariamente todos deben formar parte de la clave. La elección depende del problema.

#### 17. Aplicaciones del hashing en Deng

Deng presenta aplicaciones como el ordenamiento por buckets. La idea es que, si los enteros pertenecen a un rango conocido `[0, M)`, se puede crear una tabla de longitud `M`, insertar las claves y luego recorrer la tabla en orden de índice.

Para enteros distintos, el procedimiento es:

    crear una tabla de tamaño M
    insertar cada entero en su bucket
    recorrer los buckets de 0 a M - 1
    emitir los buckets no vacíos

El costo es:

    O(n + M)

Esto puede superar la cota de comparación `Omega(n log n)` porque aprovecha información adicional sobre el rango de claves.

Semana 8 no se centra en bucket sort, pero sí toma la idea general de usar hashing para aplicaciones concretas: detección de duplicados, conteo de frecuencias, `twoSum`, deduplicación de logs e inverted index.

#### 18. Qué toma Semana 8 de Deng

Semana 8 toma de Deng los elementos fundamentales del marco de diccionarios y tablas hash:

    Dictionary como interfaz abstracta
    Entry como par key-value
    tabla hash como bucket array
    hash function como mapeo de key a address
    factor de carga como criterio de eficiencia
    open addressing con linear probing
    eliminación perezosa
    rehashing por reinserción
    hashCode para claves no enteras

La carpeta de Semana 8 amplía estas ideas con una organización experimental. Además de `HashtableOA`, incluye `ChainedHashTable`, `LinearHashTable`, `QuadraticHashTable`, `DoubleHashTable`, `RobinHoodHashTable`, métricas con `HashStats`, políticas con `RehashPolicy` y demos para observar comportamiento.

#### 19. Qué no toma como núcleo

El capítulo de Deng también desarrolla Skiplist y Quadlist. Esa parte es valiosa porque muestra otra manera de implementar diccionarios con tiempo esperado `O(log n)`, usando niveles y torres. Sin embargo, no es el centro de Semana 8.

Semana 8 no está dedicada a listas de salto. Su foco es hashing. Por eso los conceptos centrales son dispersión, colisiones, buckets, slots, tombstones y rehashing.

La lectura de Deng permite entender que Skiplist y Hashtable son dos respuestas al mismo problema abstracto: implementar un diccionario. Pero la implementación que se estudia y se programa en Semana 8 corresponde a la línea de Hashtable.

#### 20. Relación con el código de Semana 8

La relación puede resumirse así:

    Dictionary.h
    define la interfaz abstracta del diccionario.

    Entry.h
    define las entradas key-value.

    HashCode.h
    implementa la conversión de claves reales a códigos hash.

    UniversalHash.h
    permite experimentar con familias de funciones hash.

    RehashPolicy.h
    decide cuándo crecer, contraer o limpiar la tabla.

    HashStats.h
    registra colisiones, probes, rehashing y tombstones.

    HashtableOA.h
    implementa un diccionario key-value con open addressing.

    LinearHashTable.h
    permite estudiar slots, tombstones y linear probing.

    ChainedHashTable.h
    sirve para contrastar open addressing con separate chaining.

    Applications.h
    usa tablas hash en duplicados, two-sum, frecuencias, logs e inverted index.

### Conclusiones

Deng ofrece el marco abstracto para entender diccionarios y mapas como estructuras `key -> value`. Ese marco es la base de Semana 8. La diferencia con las estructuras ordenadas es que hashing no exige comparar claves por orden, sino transformarlas en direcciones mediante `hashCode()` y una hash function.

La tabla hash de Deng se construye sobre un arreglo de buckets, usa open addressing con linear probing, mantiene marcas de eliminación perezosa con `lazyRemoval`, controla el factor de carga y reconstruye la tabla mediante `rehash()`. Estas ideas aparecen en Semana 8 como `HashtableOA`, `LinearHashTable`, tombstones, `RehashPolicy` y `HashStats`.

La lectura también muestra por qué las tablas hash no deben enseñarse como una caja negra de `O(1)`. El rendimiento esperado depende de la calidad de la función hash, de la política de colisiones, del factor de carga y de la limpieza de eliminaciones. Una mala función hash o una tabla demasiado llena puede degradar la estructura.

Para el curso, esta lectura permite ubicar Semana 8 dentro de una secuencia lógica. Primero se estudiaron árboles balanceados para búsqueda ordenada. Luego se introduce el diccionario abstracto. Finalmente se estudia hashing como una implementación no ordenada, rápida en promedio y muy útil para aplicaciones de búsqueda exacta, conteo, deduplicación e indexación.
