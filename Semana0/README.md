### Semana0: Preparacion tecnica para CC232

#### Proposito

Semana0 es la entrada tecnica al curso CC232. Su objetivo es asegurar que cada
estudiante pueda compilar, probar, medir y documentar codigo C++17 antes de
implementar estructuras de datos.

Esta semana no adelanta listas, arboles, hashing ni grafos. Su funcion es
preparar el entorno, fijar el flujo de trabajo y ordenar los conceptos minimos
que se usaran durante todo el curso.

#### Resultado esperado

Al terminar Semana0, el estudiante debe poder:

1. Compilar un proyecto C++17 con CMake.
2. Ejecutar pruebas con CTest.
3. Leer una estructura basica de proyecto con `include`, `src`, `apps`, `tests` y `bench`.
4. Usar referencias, `const`, `std::vector` y funciones auxiliares sencillas.
5. Distinguir paso por valor, paso por referencia y referencia const.
6. Explicar `struct`, `class`, constructores, destructores y RAII.
7. Distinguir copia superficial y copia profunda.
8. Distinguir pruebas, benchmarks y experimentos de optimizacion.
9. Ejecutar el flujo local sin dejar archivos temporales en el repositorio.

#### Estructura de la semana

```text
Semana0/
├── README.md
├── Actividad0-CC232.md
├── VALIDACION_LOCAL.txt
├── Proyecto0/
├── lecturas/
└── avanzado/
```

#### Material obligatorio

| Recurso | Uso |
|---|---|
| `README.md` | Mapa de la semana y flujo de trabajo. |
| `Actividad0-CC232.md` | Actividad principal de preparacion tecnica. |
| `VALIDACION_LOCAL.txt` | Comandos minimos para validar Semana0. |
| `Proyecto0/` | Proyecto base con CMake, pruebas, demos y benchmarks. |
| `lecturas/Lectura00-Cpp-Minimo-CC232.md` | Base de C++17 para el curso. |
| `lecturas/Lectura03-Pruebas-Unitarias.md` | Pruebas unitarias, `assert`, CTest y herramientas de prueba. |

#### Material avanzado

| Recurso | Uso |
|---|---|
| `avanzado/Ejercicios0_experimentos_gpp.md` | Experimentos con optimizacion, sanitizers, cobertura y profiling. |
| `avanzado/INSTRUCCIONES_Ejercicios0_v4_2.md` | Guia de uso del script de experimentos. |
| `resolver_ejercicios0_v4.2.sh` | Script de apoyo para experimentos avanzados. |
| `stl_optimizacion_demostracion.cpp` | Programa base para experimentos con STL y optimizacion. |

#### Demos de C++17 minimo

| Demo | Concepto |
|---|---|
| `Proyecto0/apps/demo_const_refs.cpp` | referencias, referencia const y copia por valor |
| `Proyecto0/apps/demo_copy_semantics.cpp` | copia superficial controlada y copia profunda |
| `Proyecto0/apps/demo_raii.cpp` | constructores, destructores y RAII |

#### Como compilar Proyecto0

Desde la raiz del repositorio:

```bash
rm -rf build_semana0
cmake -S Semana0/Proyecto0 -B build_semana0
cmake --build build_semana0
```

#### Como ejecutar pruebas

```bash
ctest --test-dir build_semana0 --output-on-failure
```

#### Como ejecutar demos

```bash
./build_semana0/demo_const_refs
./build_semana0/demo_copy_semantics
./build_semana0/demo_raii
```

En Windows con generadores multi configuracion, los ejecutables pueden quedar en
una carpeta como `build_semana0/Debug`.

#### Como limpiar archivos generados

```bash
rm -rf build_semana0
rm -rf Semana0/Proyecto0/Testing
rm -rf Semana0/ejercicios0_out
```

#### Temas obligatorios

1. Flujo basico con Git.
2. Compilacion con CMake.
3. Pruebas con CTest.
4. Lectura de codigo C++17 basico.
5. Referencias, `const`, copia y RAII.
6. Diferencia entre prueba, benchmark y experimento.
7. Limpieza de artefactos generados.

#### Temas avanzados

1. Niveles de optimizacion de `g++`.
2. Uso inicial de sanitizers.
3. Cobertura con `gcov`.
4. LTO y PGO.
5. Profiling con `gprof`.
6. Experimentos con STL y seleccion de algoritmos.

#### Alcance de esta fase

La Fase 0.2 agrega lectura de C++17 minimo y demos pequenos. No modifica la
logica principal de `Proyecto0` ni adelanta estructuras de datos.
