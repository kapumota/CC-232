### Rúbrica de Semana0

#### Propósito

Esta rúbrica evalúa Semana0 como prerrequisito técnico formal de CC232.

La calificación total es de 20 puntos.

#### Distribución de puntos

| Criterio | Puntaje |
|---|---:|
| Compilación y CMake | 4 |
| Pruebas con CTest | 3 |
| C++ básico | 3 |
| Templates | 3 |
| Sanitizers | 3 |
| Benchmark simple | 2 |
| Reporte y estilo | 2 |
| Total | 20 |

#### Compilación y CMake

Puntaje máximo: 4 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Configura y compila `Proyecto0` limpiamente con CMake desde la raíz del repositorio. | 4 |
| Parcial alto | Compila, pero requiere ajustes menores no documentados. | 3 |
| Parcial bajo | Compila solo en un entorno específico o con comandos incompletos. | 2 |
| Insuficiente | No logra compilar el proyecto. | 0 a 1 |

#### Pruebas con CTest

Puntaje máximo: 3 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Ejecuta CTest, todas las pruebas pasan y explica el resultado. | 3 |
| Parcial | Ejecuta CTest, pero no interpreta bien la salida. | 2 |
| Insuficiente | No ejecuta CTest o ignora fallos. | 0 a 1 |

#### C++ básico

Puntaje máximo: 3 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Explica referencias, `const`, RAII, copia superficial y copia profunda. | 3 |
| Parcial | Explica algunos conceptos, pero con confusiones menores. | 2 |
| Insuficiente | No distingue conceptos básicos necesarios para estructuras de datos. | 0 a 1 |

#### Templates

Puntaje máximo: 3 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Implementa `maximumValue` y `SimpleArray<T>` con pruebas adecuadas. | 3 |
| Parcial | Implementa templates, pero con validación incompleta. | 2 |
| Insuficiente | La implementación no compila o no es genérica. | 0 a 1 |

#### Sanitizers

Puntaje máximo: 3 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Ejecuta ASan y UBSan, identifica errores y explica causa y línea. | 3 |
| Parcial | Ejecuta sanitizers, pero interpreta parcialmente los reportes. | 2 |
| Insuficiente | No ejecuta sanitizers o confunde los errores detectados. | 0 a 1 |

#### Benchmark simple

Puntaje máximo: 2 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Ejecuta un benchmark simple e interpreta el resultado sin confundirlo con correctitud. | 2 |
| Parcial | Ejecuta el benchmark, pero la interpretación es débil. | 1 |
| Insuficiente | No ejecuta benchmark. | 0 |

#### Reporte y estilo

Puntaje máximo: 2 puntos.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Completo | Presenta reporte breve, claro, reproducible y con comandos verificables. | 2 |
| Parcial | Presenta reporte incompleto o poco claro. | 1 |
| Insuficiente | No presenta reporte o no permite reproducir resultados. | 0 |

#### Penalizaciones

Se pueden aplicar penalizaciones por:

1. Subir carpetas de compilación.
2. Subir archivos generados por CMake.
3. Presentar salidas sin explicación.
4. No limpiar artefactos locales.
5. Modificar código no solicitado.
6. Entregar un reporte no reproducible.
7. Confundir rendimiento con correctitud.

#### Criterio mínimo de aprobación

Para aprobar Semana0, el estudiante debe cumplir como mínimo:

1. Compilar `Proyecto0`.
2. Ejecutar CTest.
3. Presentar evidencia de ASan y UBSan.
4. Entregar reporte corto.
5. No subir artefactos generados.
