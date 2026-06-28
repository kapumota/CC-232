### Experimentos con g++ para CC232

#### Proposito

Estos experimentos muestran que el rendimiento de un programa depende de la eleccion del algoritmo, de la estructura de datos, de la correctitud del codigo y de la calidad de las pruebas.

La regla principal es:

1. Elegir bien el algoritmo.
2. Verificar que el programa sea correcto.
3. Medir rendimiento.
4. Explorar optimizaciones del compilador solo despues de validar correctitud.

#### Archivo base

Usar:

```text
Semana0/stl_optimizacion_demostracion.cpp
```

#### Experimento 1: escalera de optimizacion

Compilar el mismo programa con distintos niveles de optimizacion y comparar tiempo, tamaño del ejecutable y facilidad de depuracion.

#### Comandos

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -pedantic demo.cpp -o demo_O0
g++ -std=c++17 -Og -g -Wall -Wextra -pedantic demo.cpp -o demo_Og
g++ -std=c++17 -O1 -DNDEBUG demo.cpp -o demo_O1
g++ -std=c++17 -O2 -DNDEBUG demo.cpp -o demo_O2
g++ -std=c++17 -O3 -DNDEBUG demo.cpp -o demo_O3
g++ -std=c++17 -Os -DNDEBUG demo.cpp -o demo_Os
```

#### Experimento 2: STL y algoritmo correcto

Comparar decisiones de diseño con STL:

1. `sort` frente a `nth_element`.
2. `sort` completo frente a `partial_sort`.
3. Busqueda lineal frente a `lower_bound` sobre vector ordenado.
4. `push_back` con y sin `reserve`.

#### Comando base

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o stl_demo
./stl_demo --light
```

#### Experimento 3: LTO

Mostrar que el compilador puede optimizar a nivel de programa completo cuando se usa `-flto` al compilar y al enlazar.

#### Experimento 4: PGO

Mostrar que el compilador puede optimizar usando informacion de una carga representativa.

#### Experimento 5: sanitizers

Separar errores logicos de errores de memoria o comportamiento indefinido.

#### Comando base

```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined demo.cpp -o demo_asan_ubsan
./demo_asan_ubsan
```

#### Experimento 6: cobertura

Mostrar que un conjunto de pruebas puede pasar y aun asi dejar ramas importantes sin cubrir.

#### Comando base

```bash
g++ -std=c++17 --coverage -O0 tests.cpp modulo.cpp -o tests_cov
./tests_cov
gcov tests.cpp modulo.cpp
```

#### Experimento 7: warnings dependientes de optimizacion

Comparar warnings con builds sin optimizacion y con builds optimizados.

#### Experimento 8: profiling con gprof

Identificar funciones que consumen mas tiempo.

#### Comando base

```bash
g++ -std=c++17 -O2 -pg demo.cpp -o demo_gprof
./demo_gprof
gprof demo_gprof gmon.out
```

#### Que medir

1. Tiempo total.
2. Tamaño del ejecutable.
3. Correctitud del resultado.
4. Estabilidad entre corridas.
5. Uso de memoria cuando sea posible.

#### Condiciones para comparar

1. Mismo input.
2. Misma maquina.
3. Mismo compilador.
4. Varias repeticiones.
5. Mismo entorno de ejecucion.
