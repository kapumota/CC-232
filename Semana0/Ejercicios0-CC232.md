### Ejercicios0-CC232: Preparación técnica

#### Propósito

Estos ejercicios acompañan la Actividad0 y permiten verificar los prerrequisitos técnicos de CC232.

#### Ejercicio 1: Entorno y compilación

Ejecuta la compilación normal de `Proyecto0`.

```bash
rm -rf build_semana0
cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
```

Entrega:

1. Versión de CMake.
2. Versión del compilador.
3. Resultado de la compilación.

#### Ejercicio 2: Pruebas con CTest

Ejecuta:

```bash
ctest --test-dir build_semana0 --output-on-failure
```

Entrega:

1. Número de pruebas ejecutadas.
2. Resultado final.
3. Explicación breve de una prueba revisada.

#### Ejercicio 3: Función template

Implementa `maximumValue`.

```cpp
template <typename T>
const T& maximumValue(const T& a, const T& b);
```

Debe probarse con:

1. `int`.
2. `double`.
3. `std::string`.

Entrega:

1. Código de la función.
2. Casos de prueba.
3. Explicación de por qué devuelve `const T&`.

#### Ejercicio 4: `SimpleArray<T>`

Implementa o completa `SimpleArray<T>`.

Debe incluir:

1. Constructor por tamaño.
2. `size`.
3. `empty`.
4. `operator[]`.
5. `at`.
6. `fill`.

Entrega:

1. Código relevante.
2. Pruebas.
3. Explicación de la diferencia entre `operator[]` y `at`.

#### Ejercicio 5: ASan

Ejecuta:

```bash
./build_semana0_san/demo_asan_out_of_bounds
```

Entrega:

1. Tipo de error detectado.
2. Línea reportada.
3. Causa del error.
4. Forma correcta de evitarlo.

#### Ejercicio 6: UBSan

Ejecuta:

```bash
./build_semana0_san/demo_ubsan_overflow
```

Entrega:

1. Tipo de error detectado.
2. Línea reportada.
3. Causa del error.
4. Forma correcta de evitarlo.

#### Ejercicio 7: Iteradores

Ejecuta:

```bash
./build_semana0/demo_iterator_invalidation
```

Entrega:

1. Qué operación puede invalidar iteradores.
2. Por qué se guarda un índice lógico.
3. Cómo se recupera un iterador válido.

#### Ejercicio 8: Algoritmos STL

Ejecuta:

```bash
./build_semana0/demo_stl_algorithms
```

Explica el uso de:

1. `std::sort`.
2. `std::lower_bound`.
3. `std::nth_element`.
4. `std::partial_sort`.
5. `std::priority_queue`.

#### Ejercicio 9: Benchmark simple

Ejecuta:

```bash
./build_semana0/bench_vector_growth
```

Entrega:

1. Resultado observado.
2. Interpretación breve.
3. Diferencia entre prueba y benchmark.

#### Ejercicio 10: Reporte final

Redacta un reporte corto con:

1. Entorno.
2. Comandos.
3. Resultados.
4. Errores detectados.
5. Conclusión técnica.
