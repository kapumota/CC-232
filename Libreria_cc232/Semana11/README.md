### Semana11 CC232: Tries, cadenas y busqueda de patrones

#### Objetivo

Esta semana introduce estructuras de datos para cadenas y algoritmos clasicos de busqueda de patrones. El foco esta en conectar diccionarios de prefijos, tries, matching exacto y estructuras de sufijos con implementacion C++17, pruebas y analisis de costo.

#### Temas principales

1. Modelo de cadenas, alfabeto, prefijos, sufijos y costo por longitud.
2. `TrieSet` para diccionarios de palabras.
3. `TrieMap` para asociar cadenas con valores.
4. Consultas `contains`, `startsWith`, `autocomplete` y `longestPrefixOf`.
5. Trie comprimido como reduccion de caminos unarios.
6. Busqueda de patrones por fuerza bruta.
7. Funcion prefijo y Knuth-Morris-Pratt.
8. Rabin-Karp con hashing rodante y verificacion de coincidencias.
9. Boyer-Moore simplificado con regla de mal caracter.
10. Aho-Corasick para multiples patrones.
11. Suffix array basico y arreglo LCP.
12. Suffix trie ingenuo como puente hacia suffix trees.

#### Relacion con fuentes

Deng aporta la linea de busqueda de patrones: fuerza bruta, KMP, Rabin-Karp y Boyer-Moore. Morin aporta la perspectiva de tries digitales para enteros mediante `BinaryTrie`, `XFastTrie` y `YFastTrie`. La semana agrega material complementario para tries de cadenas, autocompletado, Aho-Corasick, suffix array y suffix trie.

#### Estructura

```txt
Semana11/
├── CMakeLists.txt
├── README.md
├── Resumen_Semana11.md
├── Actividad11-CC232.md
├── Ejercicios11-CC232.md
├── PATCH_ROOT_CMAKE.md
├── include/
├── demos/
├── lecturas/
├── pruebas_publicas/
├── pruebas_internas/
└── sustentacion/
```

#### Compilacion aislada

```bash
cmake -S Libreria_cc232/Semana11 -B build_semana11
cmake --build build_semana11
ctest --test-dir build_semana11 --output-on-failure
```

#### Integracion desde la raiz de la libreria

Agregar en `Libreria_cc232/CMakeLists.txt`:

```cmake
add_subdirectory(Semana11)
```

Luego ejecutar:

```bash
cmake -S Libreria_cc232 -B build_libreria
cmake --build build_libreria
ctest --test-dir build_libreria --output-on-failure
```

#### Archivos principales

| Archivo | Contenido |
|---|---|
| `TrieSet.h` | Diccionario de palabras con prefijos |
| `TrieMap.h` | Diccionario de cadenas a valores |
| `CompressedTrie.h` | Trie comprimido didactico |
| `PrefixFunction.h` | Funcion prefijo para KMP |
| `StringMatching.h` | Fuerza bruta y funcion Z |
| `KMP.h` | Busqueda exacta con KMP |
| `RabinKarp.h` | Busqueda con hashing rodante |
| `BoyerMoore.h` | Variante por mal caracter |
| `AhoCorasick.h` | Matching multiple con automata de fallos |
| `SuffixArray.h` | Suffix array y LCP |
| `SuffixTrie.h` | Suffix trie ingenuo con terminador |
| `CapituloCadenas.h` | Cabecera agregadora |

#### Nivel esperado

El estudiante debe poder explicar invariantes, costos y casos borde. No basta con ejecutar los algoritmos: debe justificar por que `TrieSet` depende de la longitud de la cadena, por que KMP evita retroceder en el texto, por que Rabin-Karp necesita verificacion y por que Aho-Corasick combina trie y enlaces de fallo.
