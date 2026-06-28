### Actividad0-CC232: Preparacion tecnica del curso

#### Objetivo

Preparar el entorno de trabajo para CC232 y validar que el estudiante puede compilar, probar, ejecutar y limpiar un proyecto C++17 con CMake y CTest.

#### Contexto

Durante el curso se implementaran estructuras de datos con C++17. Antes de modificar arreglos, listas, arboles, tablas hash o grafos, cada estudiante debe demostrar que domina el flujo tecnico minimo.

#### Trabajo individual

La actividad es individual. Cada estudiante debe ejecutar los comandos, revisar la salida y entregar un reporte breve.

#### Parte 1: Exploracion de Semana0

Desde la raiz del repositorio, listar la estructura principal:

```bash
find Semana0 -maxdepth 2 -type f | sort
```

Responder en el reporte:

1. Que archivos pertenecen al flujo obligatorio.
2. Que archivos pertenecen al material avanzado.
3. Que carpeta contiene el proyecto compilable.

#### Parte 2: Compilacion de Proyecto0

Ejecutar:

```bash
rm -rf build_semana0
cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
```

Responder en el reporte:

1. Si la configuracion de CMake termino correctamente.
2. Si la compilacion termino correctamente.
3. Que ejecutables o pruebas se generaron.

#### Parte 3: Pruebas con CTest

Ejecutar:

```bash
ctest --test-dir build_semana0 --output-on-failure
```

Responder en el reporte:

1. Cuantas pruebas se ejecutaron.
2. Cuantas pruebas pasaron.
3. Que significa una prueba fallida en el contexto del curso.

#### Parte 4: Limpieza del repositorio

Ejecutar:

```bash
rm -rf build_semana0
rm -rf Semana0/Proyecto0/Testing
rm -rf Semana0/ejercicios0_out

git status --short --untracked-files=all
```

Responder en el reporte:

1. Que archivos generados fueron eliminados.
2. Por que no se deben subir builds ni carpetas de salida.
3. Que muestra `git status` despues de la limpieza.

#### Parte 5: Lectura tecnica

Leer:

```text
Semana0/lecturas/README.md
Semana0/lecturas/Lectura03-Pruebas-Unitarias.md
```

Responder:

1. Diferencia entre prueba publica y prueba interna.
2. Diferencia entre prueba y benchmark.
3. Por que primero se valida correctitud y despues se mide rendimiento.

#### Parte 6: Material avanzado

Revisar sin modificar codigo:

```text
Semana0/avanzado/Ejercicios0_experimentos_gpp.md
Semana0/avanzado/INSTRUCCIONES_Ejercicios0_v4_2.md
```

Responder:

1. Que experimentos son obligatorios para empezar el curso.
2. Que experimentos se consideran avanzados.
3. Por que LTO, PGO y profiling no deben mezclarse con la primera validacion del proyecto.

#### Entregable

El estudiante debe entregar un archivo llamado:

```text
reporte_semana0.md
```

El reporte debe contener:

1. Comandos ejecutados.
2. Salida resumida de CMake.
3. Salida resumida de CTest.
4. Respuestas a las preguntas de la actividad.
5. Observaciones sobre errores encontrados y como se corrigieron.

#### Criterios de evaluacion

| Criterio | Puntaje |
|---|---:|
| Compilacion correcta con CMake | 4 |
| Ejecucion correcta de CTest | 4 |
| Limpieza del repositorio | 3 |
| Comprension de pruebas y benchmarks | 3 |
| Identificacion de material obligatorio y avanzado | 3 |
| Reporte claro y verificable | 3 |

#### Restricciones

1. No modificar codigo fuente de `Proyecto0` en esta actividad.
2. No subir carpetas `build` ni salidas temporales.
3. No usar capturas de pantalla como sustituto de comandos y salidas.
4. No entregar todo en un unico commit final si se trabaja en repositorio propio.

#### Extension Fase 0.2

En esta fase se agrega una lectura obligatoria de C++17 minimo y tres demos
pequenos. El estudiante debe revisar:

1. `lecturas/Lectura00-Cpp-Minimo-CC232.md`.
2. `Proyecto0/apps/demo_const_refs.cpp`.
3. `Proyecto0/apps/demo_copy_semantics.cpp`.
4. `Proyecto0/apps/demo_raii.cpp`.

El objetivo no es memorizar todo C++. El objetivo es reconocer las decisiones que
apareceran despues en arreglos, listas, heaps, arboles, hashing, grafos y
estructuras de rango.

#### Preguntas de control de Fase 0.2

1. Cuando conviene usar `const std::vector<int>&` en lugar de `std::vector<int>`.
2. Por que `std::size_t` aparece al recorrer un `std::vector`.
3. Que diferencia hay entre una copia compartida y una copia profunda.
4. Por que un destructor puede ejecutarse aunque no se llame de forma explicita.
5. Como RAII ayuda a evitar fugas de recursos.



#### Extension de Fase 0.3

Agrega la lectura `Lectura01-Templates-Genericos.md`, ejecuta el demo `demo_templates` y revisa la prueba `test_simple_array`. El estudiante debe explicar por que `SimpleArray<T>` define `operator[]` mutable y constante.
