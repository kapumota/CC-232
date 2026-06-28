### Instrucciones para los experimentos avanzados de Semana0

#### Proposito

Este archivo explica como ejecutar los experimentos avanzados usando el script:

```text
Semana0/resolver_ejercicios0_v4.2.sh
```

El programa base es:

```text
Semana0/stl_optimizacion_demostracion.cpp
```

#### Archivos necesarios

Los archivos principales son:

```text
Semana0/resolver_ejercicios0_v4.2.sh
Semana0/stl_optimizacion_demostracion.cpp
Semana0/avanzado/Ejercicios0_experimentos_gpp.md
```

#### Dar permiso de ejecucion

Desde `Semana0`:

```bash
chmod +x resolver_ejercicios0_v4.2.sh
```

#### Ver ayuda

```bash
./resolver_ejercicios0_v4.2.sh help
```

#### Ejecutar todos los experimentos

```bash
./resolver_ejercicios0_v4.2.sh all
```

La salida se genera en:

```text
ejercicios0_out/
```

#### Ejecutar un experimento especifico

```bash
./resolver_ejercicios0_v4.2.sh 1
./resolver_ejercicios0_v4.2.sh 2
./resolver_ejercicios0_v4.2.sh 3
./resolver_ejercicios0_v4.2.sh 4
./resolver_ejercicios0_v4.2.sh 5
./resolver_ejercicios0_v4.2.sh 6
./resolver_ejercicios0_v4.2.sh 7
./resolver_ejercicios0_v4.2.sh 8
./resolver_ejercicios0_v4.2.sh 9
./resolver_ejercicios0_v4.2.sh 10
```

#### Aliases utiles

```bash
./resolver_ejercicios0_v4.2.sh opt
./resolver_ejercicios0_v4.2.sh stl
./resolver_ejercicios0_v4.2.sh pgo
./resolver_ejercicios0_v4.2.sh san
./resolver_ejercicios0_v4.2.sh cov
./resolver_ejercicios0_v4.2.sh gprof
```

#### Uso con ruta explicita

Si el archivo base esta en otra ubicacion:

```bash
./resolver_ejercicios0_v4.2.sh ./stl_optimizacion_demostracion.cpp 2
```

#### Limpieza

```bash
rm -rf ejercicios0_out
rm -f demo_* stl_demo tests_cov *.gcda *.gcno *.gcov gmon.out
```

#### Recomendacion

Primero se debe validar `Proyecto0` con CMake y CTest. Luego se ejecutan estos experimentos avanzados.
