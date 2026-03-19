### Proyecto 0 para CC232

Proyecto independiente para arrancar un curso de estructuras de datos y algoritmos en C++17. Su objetivo no es enseñar muchas estructuras todavía, sino fijar el flujo de trabajo mínimo:

1. compilar con **CMake**
2. correr **tests**
3. ejecutar un **micro-benchmark**
4. practicar **referencias**, **const** y `std::vector`

#### Qué contiene

- `include/warmup_vector.h`, `src/warmup_vector.cpp`  
  Funciones pequeñas para discutir paso por valor, referencia y referencia const.
- `include/line_stats.h`, `src/line_stats.cpp`  
  Módulo mínimo para practicar separación `.h/.cpp`, API y pruebas.
- `include/mini_test.h`  
  Harness mínimo de testing para no depender de librerías externas.
- `include/mini_bench.h`  
  Micro-harness para medir tiempos promedio en microsegundos.
- `tests/`  
  Pruebas unitarias mínimas.
- `apps/demo_const_refs.cpp`  
  Demostración rápida de `const std::vector<int>&`, `std::vector<int>&` y copia por valor.
- `bench/bench_vector_growth.cpp`  
  `push_back` con y sin `reserve`.
- `bench/bench_vector_ops.cpp`  
  `push_back` al final vs `insert(begin())` vs `insert(middle)`.
- `bench/bench_cache_effects.cpp`  
  Localidad básica: `vector` secuencial vs acceso aleatorio vs `std::list`.

#### Build normal

```bash
cmake -S . -B build
cmake --build build --config Debug 
ctest --test-dir build -C Debug --output-on-failure
```
Desde build por ejemplo

```bash
./Debug/demo_line_stats.exe
./Debug/bench_vector_growth.exe
./Debug/bench_vector_ops.exe
./Debug/bench_cache_effects.exe
./Debug/sanitizer_demo.exe
```

#### Qué mirar para la clase

##### 1. Referencias y `const`
- `const std::vector<int>&` evita copiar y protege contra modificación accidental.
- `std::vector<int>&` permite mutar el objeto original.
- pasar `std::vector<int>` por valor crea una copia.

##### 2. `std::vector`
- memoria contigua
- `push_back`
- crecimiento dinámico
- `reserve`
- costo de insertar al inicio o al medio

##### 3.  Tests
Los tests aquí son mínimos a propósito: solo validan correctitud observable. No intentan medir rendimiento.

##### 4. Sanitizers
Los sanitizers no "arreglan" bugs, pero ayudan a encontrarlos rápido. La demostración produce un acceso fuera de rango de forma intencional.

##### 5.  Benchmarks
Los micro-benchmarks sirven para observar tendencias, no para "demostrar leyes universales".
Hay que leerlos con cautela:

- dependen del compilador
- dependen del hardware
- dependen del tamaño `n`
- una diferencia pequeña puede ser ruido

