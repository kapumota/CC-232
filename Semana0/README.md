### Semana0: Preparacion tecnica para CC232

#### Proposito

Semana0 es la entrada tecnica al curso CC232. Su objetivo es asegurar que cada estudiante pueda compilar, probar, medir y documentar codigo C++17 antes de implementar estructuras de datos.

Esta semana no busca adelantar listas, arboles, hashing ni grafos. Su funcion es preparar el entorno, fijar el flujo de trabajo y ordenar los conceptos minimos que se usaran durante todo el curso.

#### Resultado esperado

Al terminar Semana0, el estudiante debe poder:

1. Compilar un proyecto C++17 con CMake.
2. Ejecutar pruebas con CTest.
3. Leer una estructura basica de proyecto con `include`, `src`, `apps`, `tests` y `bench`.
4. Usar referencias, `const`, `std::vector` y funciones auxiliares sencillas.
5. Distinguir pruebas, benchmarks y experimentos de optimizacion.
6. Ejecutar el flujo local sin dejar archivos temporales en el repositorio.
7. Entender que las herramientas avanzadas se estudian de forma progresiva.

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
| `lecturas/` | Lecturas de apoyo necesarias para empezar el curso. |

#### Material avanzado

| Recurso | Uso |
|---|---|
| `avanzado/Ejercicios0_experimentos_gpp.md` | Experimentos con optimizacion, sanitizers, cobertura y profiling. |
| `avanzado/INSTRUCCIONES_Ejercicios0_v4_2.md` | Guia de uso del script de experimentos. |
| `resolver_ejercicios0_v4.2.sh` | Script de apoyo para experimentos avanzados. |
| `stl_optimizacion_demostracion.cpp` | Programa base para experimentos con STL y optimizacion. |

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
5. Diferencia entre prueba, benchmark y experimento.
6. Limpieza de artefactos generados.

#### Temas avanzados

1. Niveles de optimizacion de `g++`.
2. Uso inicial de sanitizers.
3. Cobertura con `gcov`.
4. LTO y PGO.
5. Profiling con `gprof`.
6. Experimentos con STL y seleccion de algoritmos.

#### Alcance de esta fase

La Fase 0.1 solo reorganiza documentacion. No cambia headers, fuentes, pruebas ni CMake de `Proyecto0`.
