### Lectura02: CMake y CTest para CC232

#### Proposito

Esta lectura explica el flujo mínimo de CMake y CTest que se usará durante el curso CC232.

El objetivo no es memorizar todos los comandos de CMake. El objetivo es entender como se organiza un proyecto pequeño de C++17, como se separa una librería de sus demostraciones y pruebas, y como se valida el código antes de avanzar a estructuras de datos.

#### Por que CMake en CC232

En este curso cada semana contiene codigo C++17, pruebas, demostraciones y a veces benchmarks.

CMake permite describir esa estructura de manera reproducible:

```text
include/   headers publicos
src/       implementacion principal
apps/      demostraciones ejecutables
tests/     pruebas
bench/     benchmarks
```

El estudiante debe poder compilar el proyecto desde cero sin depender de un IDE específico.

#### Comandos minimos

Desde la raiz del repositorio:

```bash
rm -rf build_semana0
cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
ctest --test-dir build_semana0 --output-on-failure
```

El primer comando elimina una compilación anterior. El segundo configura el proyecto. El tercero compila. El cuarto ejecuta las pruebas registradas con CTest.

#### Librería principal

El proyecto define una librería llamada `cc232_proyecto0`.

Una librería agrupa código reutilizable. Los demostraciones y pruebas se enlazan contra ella.

```cmake
add_library(cc232_proyecto0)

target_sources(cc232_proyecto0
    PRIVATE
        src/line_stats.cpp
        src/warmup_vector.cpp
)

target_include_directories(cc232_proyecto0
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

La palabra `PRIVATE` indica archivos usados para construir la librería. La palabra `PUBLIC` indica headers que también necesitan los programas que usan la librería.

#### Version de C++

En CC232 se usa C++17.

```cmake
target_compile_features(cc232_proyecto0 PUBLIC cxx_std_17)
```

Esta forma es preferible porque asocia la versión de C++ con el target que la necesita.

#### Advertencias estrictas

El proyecto puede activar advertencias de compilación con una opción:

```cmake
option(CC232_ENABLE_WARNINGS "Activa advertencias estrictas" ON)
```

Cuando esta opción esta activa, se agregan flags como:

```text
-Wall
-Wextra
-Wpedantic
```

Estas advertencias ayudan a detectar errores tempranos, conversiones sospechosas y código frágil.

#### Ejecutables de prueba

Cada prueba se declara como ejecutable y se registra con `add_test`.

```cmake
add_executable(test_line_stats tests/test_line_stats.cpp)
target_link_libraries(test_line_stats PRIVATE cc232_proyecto0)
add_test(NAME test_line_stats COMMAND test_line_stats)
```

CTest permite ejecutar todas las pruebas con un solo comando.

```bash
ctest --test-dir build_semana0 --output-on-failure
```

#### Demostraciones

Los demostraciones son programas pequeños para observar comportamiento.

```cmake
option(BUILD_APPS "Compila demos de Proyecto0" ON)
```

Si la opción esta activa, CMake compila las demostraciones disponibles en `apps/`.

```bash
cmake -S Semana0/Proyecto0 -B build_semana0 -DBUILD_APPS=ON
cmake --build build_semana0
```

#### Benchmarks

Los benchmarks se controlan con otra opción:

```cmake
option(BUILD_BENCHMARKS "Compila benchmarks de Proyecto0" ON)
```

Los benchmarks no reemplazan las pruebas. Primero se verifica la correctitud. Luego se mide.

#### Reglas de trabajo

1. Primero compilar.
2. Luego ejecutar pruebas.
3. Despues ejecutar demostraciones.
4. Finalmente ejecutar benchmarks si corresponde.
5. No dejar carpetas `build` dentro del commit.

#### Errores frecuentes

##### Comandos en la misma línea

Cada instrucción de CMake debe estar bien separada.

Correcto:

```cmake
add_executable(demo_templates apps/demo_templates.cpp)
target_link_libraries(demo_templates PRIVATE cc232_proyecto0)
```

Incorrecto:

```cmake
add_executable(demo_templates apps/demo_templates.cpp) target_link_libraries(demo_templates PRIVATE cc232_proyecto0)
```

##### Olvidar registrar una prueba

Compilar una prueba no basta. También debe registrarse:

```cmake
add_test(NAME test_simple_array COMMAND test_simple_array)
```

##### Mezclar código de prueba con código principal

Los archivos de `tests/` no deben formar parte de la librería principal. Solo se usan para crear ejecutables de prueba.

#### Validación de esta fase

```bash
rm -rf build_semana0

cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
ctest --test-dir build_semana0 --output-on-failure

rm -rf build_semana0
```

#### Resultado esperado

Al terminar esta fase, el estudiante debe entender:

1. Que es un target en CMake.
2. Como se declara una librería.
3. Como se registran pruebas con CTest.
4. Como se separan librería, demostraciones, pruebas y benchmarks.
5. Como activar o desactivar demos y benchmarks.
6. Por que las advertencias estrictas ayudan a mantener código de calidad.
