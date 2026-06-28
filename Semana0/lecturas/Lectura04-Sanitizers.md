### Lectura04: Sanitizers en CC232

#### Propósito

Esta lectura introduce AddressSanitizer y UndefinedBehaviorSanitizer como herramientas obligatorias de depuración durante el curso CC232.

La idea central es simple: primero se prueba la correctitud, luego se ejecuta el código con sanitizers y recién después se mide rendimiento.

#### Qué problema resuelven

C++ permite trabajar cerca de la memoria. Esa potencia también permite cometer errores que pueden pasar desapercibidos durante una ejecución normal.

Los sanitizers ayudan a detectar errores como:

1. Accesos fuera de rango.
2. Uso de memoria después de liberarla.
3. Desbordamiento con enteros con signo.
4. Uso de referencias o iteradores inválidos.
5. Comportamiento indefinido que puede cambiar entre compiladores.

#### AddressSanitizer

AddressSanitizer, abreviado ASan, detecta errores de memoria.

Ejemplos típicos:

1. Leer fuera de un arreglo.
2. Escribir fuera de un arreglo.
3. Usar memoria después de que fue liberada.
4. Usar memoria de pila fuera de su vida útil.

En estructuras de datos, ASan es útil para listas enlazadas, árboles, heaps, tablas hash con almacenamiento dinámico y cualquier estructura que administre nodos.

#### UndefinedBehaviorSanitizer

UndefinedBehaviorSanitizer, abreviado UBSan, detecta comportamientos indefinidos.

Ejemplos típicos:

1. Desbordamiento de enteros con signo.
2. Conversiones inválidas.
3. Accesos con alineamiento incorrecto.
4. Operaciones que el estándar de C++ no define.

Un programa con comportamiento indefinido puede parecer correcto en una máquina y fallar en otra. Por eso no se debe aceptar como correcto.

#### Cómo activar sanitizers en Proyecto0

Desde la raíz del repositorio:

```bash
rm -rf build_semana0_san

cmake -S Semana0/Proyecto0 -B build_semana0_san \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCC232_ENABLE_SANITIZERS=ON

cmake --build build_semana0_san
ctest --test-dir build_semana0_san --output-on-failure
```

Las pruebas normales deben pasar incluso con sanitizers activados.

#### Demostraciones intencionalmente incorrectas

Esta fase agrega tres demos diseñados para fallar cuando se ejecutan manualmente con sanitizers.

```bash
./build_semana0_san/demo_asan_out_of_bounds
./build_semana0_san/demo_ubsan_overflow
./build_semana0_san/demo_iterator_invalid
```

Estas demostraciones no se registran como pruebas de CTest porque su propósito es producir reportes de error.

#### Flujo correcto de uso

El flujo recomendado es:

1. Compilar en modo normal.
2. Ejecutar pruebas normales.
3. Compilar en modo Debug con sanitizers.
4. Ejecutar pruebas con sanitizers.
5. Ejecutar demostraciones de error de forma manual.
6. Leer el reporte del sanitizer.
7. Corregir el error.
8. Repetir la validación.

#### Interpretación de reportes

Un reporte de sanitizer suele indicar:

1. Tipo de error.
2. Archivo y línea donde ocurrió.
3. Traza de llamadas.
4. Región de memoria afectada.
5. Pista sobre el origen del problema.

El estudiante no debe copiar el reporte completo en la entrega. Debe explicar la causa del error y cómo lo corrigió.

#### Regla del curso

Una estructura de datos no debe considerarse terminada si:

1. Las pruebas fallan.
2. Los sanitizers reportan errores.
3. El código depende de comportamiento indefinido.
4. El estudiante no puede explicar la causa de un error detectado.

#### Relación con semanas posteriores

| Semana | Uso de sanitizers |
|---|---|
| Semana1 y Semana2 | índices, capacidad y acceso a arreglos |
| Semana3 y Semana4 | nodos, punteros, listas y colas |
| Semana5 y Semana6 | heaps y árboles |
| Semana7 y Semana8 | balanceo, hashing y colisiones |
| Semana9 | grafos y recorridos |
| Semana12 | segment trees y Fenwick Trees |
| Semana13 | B-Trees, nodos y rangos |

#### Ejercicios de lectura

1. Explica por qué un acceso fuera de rango puede no fallar sin ASan.
2. Explica por qué un desbordamiento con `int` puede ser comportamiento indefinido.
3. Ejecuta un demo de sanitizer y resume el tipo de error detectado.
4. Indica por qué los demos intencionalmente incorrectos no deben estar en CTest.
5. Explica por qué no se debe medir rendimiento con sanitizers activados.
