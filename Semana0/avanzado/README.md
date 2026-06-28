### Material avanzado de Semana0

#### Propósito

Esta carpeta contiene material complementario para profundizar en experimentos de compilación, medición, optimización y análisis del código.

Este material apoya el curso, pero no debe mezclarse con la primera validación técnica del estudiante. Antes de usarlo, el estudiante debe poder compilar, probar, depurar y limpiar `Proyecto0` de forma confiable.

#### Contenido

| Archivo                             | Propósito                                                                      |
| ----------------------------------- | ------------------------------------------------------------------------------ |
| `Ejercicios0_experimentos_gpp.md`   | Propone experimentos con optimización, sanitizers, cobertura, profiling y STL. |
| `INSTRUCCIONES_Ejercicios0_v4_2.md` | Explica cómo ejecutar el script de experimentos.                               |
| `Optimizacion-LTO-PGO.md`           | Introduce optimización LTO y PGO como temas posteriores a la validación base.  |
| `Profiling-gprof.md`                | Presenta profiling básico con `gprof` para identificar funciones costosas.     |
| `Cobertura-Avanzada.md`             | Resume cobertura de líneas, ramas y funciones como apoyo a pruebas.            |

#### Criterio de uso

El material avanzado se usa cuando el estudiante ya puede:

1. Compilar `Proyecto0` con CMake.
2. Ejecutar pruebas con CTest.
3. Activar sanitizers y entender reportes básicos.
4. Limpiar artefactos generados.
5. Distinguir entre correctitud, medición y optimización.
6. Explicar por qué un programa debe ser correcto antes de medir rendimiento.

#### Temas que se mantienen como avanzados

Los siguientes temas se mantienen fuera del flujo inicial obligatorio:

1. LTO.
2. PGO.
3. Profiling con `gprof`.
4. Cobertura con herramientas externas.
5. Warnings dependientes de optimización.
6. Experimentos comparativos con STL.
7. Interpretación de resultados de rendimiento.
8. Comparación entre compilaciones normales y compilaciones optimizadas.

#### Regla principal

La primera validación de Semana0 debe concentrarse en correctitud, compilación limpia, pruebas unitarias, sanitizers y limpieza del proyecto.

La optimización y la medición avanzada solo deben estudiarse después de confirmar que el código funciona correctamente.

#### Relación con el curso

Este material será útil en fases posteriores, especialmente cuando el estudiante deba:

1. Comparar implementaciones propias contra STL.
2. Medir tiempos de ejecución.
3. Interpretar resultados de benchmarks.
4. Analizar cuellos de botella.
5. Justificar decisiones de diseño con evidencia experimental.
6. Evitar conclusiones erróneas basadas en programas incorrectos o mediciones no controladas.
