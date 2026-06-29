### Actividad0-CC232: Prerrequisito técnico del curso

#### Propósito

Esta actividad cierra Semana0 como prerrequisito formal de CC232.

El objetivo es verificar que el estudiante puede compilar, probar, depurar, usar templates, ejecutar sanitizers, realizar una medición simple y entregar un reporte corto antes de iniciar las estructuras de datos principales.

#### Resultado esperado

Al terminar la actividad, el estudiante debe entregar evidencia de que puede:

1. Configurar y compilar `Proyecto0` con CMake.
2. Ejecutar pruebas con CTest.
3. Implementar una función template sencilla.
4. Implementar o completar `SimpleArray<T>`.
5. Ejecutar ASan sobre un bug intencional.
6. Ejecutar UBSan sobre un bug intencional.
7. Ejecutar un benchmark simple.
8. Escribir un reporte breve y verificable.

#### Reglas generales

1. El trabajo debe compilar en C++17.
2. Los comandos deben ejecutarse desde la raíz del repositorio.
3. No se deben subir carpetas de compilación.
4. No se deben modificar archivos generados por CMake.
5. Todo cambio debe estar justificado en el reporte.
6. El reporte debe ser breve, técnico y reproducible.

#### Parte 1: Compilación con CMake

Ejecuta:

```bash
rm -rf build_semana0

cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
```

El estudiante debe registrar:

1. Sistema operativo.
2. Versión del compilador.
3. Versión de CMake.
4. Resultado de la compilación.

#### Parte 2: Pruebas con CTest

Ejecuta:

```bash
ctest --test-dir build_semana0 --output-on-failure
```

El estudiante debe indicar:

1. Cantidad de pruebas ejecutadas.
2. Cantidad de pruebas aprobadas.
3. Si alguna prueba falla, causa probable y corrección aplicada.

#### Parte 3: C++ básico

Revisa las demostraciones principales:

```bash
./build_semana0/demo_line_stats
./build_semana0/demo_const_refs
./build_semana0/demo_copy_semantics
./build_semana0/demo_raii
```

El estudiante debe explicar:

1. Diferencia entre paso por valor y paso por referencia const.
2. Uso de RAII.
3. Diferencia entre copia superficial y copia profunda.
4. Por qué una función de solo lectura debe usar `const` cuando corresponde.

#### Parte 4: Templates

El estudiante debe implementar una función template llamada `maximumValue`.

Firma esperada:

```cpp
template <typename T>
const T& maximumValue(const T& a, const T& b);
```

La función debe devolver una referencia constante al mayor valor según `operator<`.

Debe probarse al menos con:

1. `int`.
2. `double`.
3. `std::string`.

#### Parte 5: `SimpleArray<T>`

El estudiante debe implementar o completar una clase `SimpleArray<T>` con estas operaciones mínimas:

```cpp
template <typename T>
class SimpleArray {
public:
    explicit SimpleArray(std::size_t size);

    std::size_t size() const noexcept;
    bool empty() const noexcept;

    T& operator[](std::size_t index) noexcept;
    const T& operator[](std::size_t index) const noexcept;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    void fill(const T& value);
};
```

Requisitos:

1. `at` debe validar rango.
2. `operator[]` no debe validar rango.
3. `fill` debe asignar el mismo valor a todos los elementos.
4. La clase debe respetar RAII.
5. La clase debe evitar memoria manual innecesaria si se usa `std::vector<T>` internamente.

#### Parte 6: Sanitizers

Compila con sanitizers:

```bash
rm -rf build_semana0_san

cmake -S Semana0/Proyecto0 -B build_semana0_san \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCC232_ENABLE_SANITIZERS=ON

cmake --build build_semana0_san
ctest --test-dir build_semana0_san --output-on-failure
```

Ejecuta manualmente las demostraciones incorrectas:

```bash
./build_semana0_san/demo_asan_out_of_bounds
./build_semana0_san/demo_ubsan_overflow
./build_semana0_san/demo_iterator_invalid
```

El estudiante debe explicar:

1. Qué error detecta ASan.
2. Qué error detecta UBSan.
3. En qué archivo y línea aparece el error.
4. Por qué estas demostraciones no deben registrarse como pruebas automáticas de CTest.

#### Parte 7: STL, iteradores y complejidad

Ejecuta:

```bash
./build_semana0/demo_vector_growth
./build_semana0/demo_iterator_invalidation
./build_semana0/demo_stl_algorithms
```

El estudiante debe explicar:

1. Diferencia entre tamaño y capacidad de `std::vector`.
2. Por qué una inserción puede invalidar iteradores.
3. Cuándo usar `std::sort`.
4. Cuándo usar `std::lower_bound`.
5. Cuándo usar `std::nth_element`.
6. Cuándo usar `std::partial_sort`.

#### Parte 8: Benchmark simple

Ejecuta al menos un benchmark disponible:

```bash
./build_semana0/bench_vector_growth
```

Si existen más benchmarks, pueden ejecutarse también:

```bash
./build_semana0/bench_vector_ops
./build_semana0/bench_cache_effects
```

El estudiante debe reportar:

1. Tamaño de entrada.
2. Tiempo aproximado.
3. Observación principal.
4. Por qué un benchmark no reemplaza una prueba de correctitud.

#### Parte 9: Reporte corto

El reporte debe tener como máximo dos páginas y debe incluir:

1. Datos del estudiante.
2. Entorno usado.
3. Comandos ejecutados.
4. Resultado de CMake.
5. Resultado de CTest.
6. Evidencia de sanitizers.
7. Resultado del benchmark.
8. Una conclusión técnica.

#### Entregables

El estudiante debe entregar:

1. Código modificado si corresponde.
2. Reporte corto en Markdown o PDF.
3. Captura o texto de salida de CTest.
4. Fragmento relevante de salida de ASan.
5. Fragmento relevante de salida de UBSan.
6. Resultado del benchmark simple.

#### Criterio de aprobación

Semana0 se considera aprobada si:

1. El proyecto compila.
2. Las pruebas pasan.
3. La implementación template funciona.
4. `SimpleArray<T>` cumple su contrato mínimo.
5. El estudiante entiende al menos un reporte de ASan y uno de UBSan.
6. El reporte es claro y reproducible.
