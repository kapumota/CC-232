### Semana13: B-Trees, B+Trees y memoria externa

#### Propósito

Esta semana estudia estructuras de búsqueda diseñadas para escenarios donde el costo dominante no es una comparación en CPU, sino una transferencia de bloque entre memoria externa y memoria principal.

La idea central es comparar un árbol binario de búsqueda con un árbol multiway. Un BST puede tener gran altura si los datos llegan ordenados. Un B-Tree reduce la altura usando nodos con muchas claves. Un B+Tree, además, organiza los registros en hojas enlazadas y facilita recorridos de rango.

#### Temas

- Modelo de memoria externa.
- Bloques, páginas y costo de I/O.
- Altura de BST frente a altura de B-Tree.
- B-Tree con búsqueda, inserción, split y eliminación.
- Validación de invariantes de B-Tree.
- B+Tree con hojas enlazadas.
- Búsqueda exacta y range scan en B+Tree.
- Simulador de almacenamiento por bloques.
- Comparación experimental pequeña entre BST y B-Tree.

#### Código principal

```txt
include/IoStats.h
include/BlockModel.h
include/BlockStoreSimulator.h
include/ExternalMemoryCost.h
include/BinarySearchTreeBaseline.h
include/BTree.h
include/BTreeValidator.h
include/BPlusTree.h
include/BPlusTreeValidator.h
include/CapituloMemoriaExterna.h
```

#### Demos

```txt
demos/demo_block_model.cpp
demos/demo_btree_insert.cpp
demos/demo_btree_delete.cpp
demos/demo_bplus_range_scan.cpp
demos/demo_bst_vs_btree.cpp
```

#### Pruebas

```txt
pruebas_publicas/test_public_week13.cpp
pruebas_internas/test_btree_insert_search.cpp
pruebas_internas/test_btree_delete.cpp
pruebas_internas/test_btree_invariants.cpp
pruebas_internas/test_bplus_tree.cpp
pruebas_internas/test_range_scan.cpp
pruebas_internas/test_external_memory_cost.cpp
```

#### Validación local

Desde la raíz del repositorio:

```bash
cmake -S Libreria_cc232/Semana13 -B build_semana13
cmake --build build_semana13
ctest --test-dir build_semana13 --output-on-failure
```

Para validar toda la librería:

```bash
cmake -S Libreria_cc232 -B build_libreria
cmake --build build_libreria
ctest --test-dir build_libreria --output-on-failure
```

#### Nota académica

Los códigos Python de referencia pueden servir para entender la lógica de B-Tree y B+Tree, pero esta semana entrega una versión modular en C++17 con validadores, pruebas y simulación de costo de I/O.
