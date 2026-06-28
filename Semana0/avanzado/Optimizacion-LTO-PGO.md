### Optimización LTO y PGO

#### Propósito

Este documento separa los temas de optimización avanzada de la actividad base de Semana0.

#### LTO

LTO significa **Link Time Optimization**.

Permite que el compilador optimice usando información de varias unidades de traducción durante la etapa de enlace.

#### PGO

PGO significa **Profile Guided Optimization**.

Consiste en ejecutar el programa con cargas representativas, recolectar información de perfil y recompilar usando esa información.

#### Por qué es avanzado

Estas técnicas pueden cambiar tiempos de ejecución y decisiones de optimización. Por eso no son adecuadas para evaluar la primera correctitud de una estructura.

#### Regla del curso

Primero se valida correctitud. Después se activan sanitizers. Recién al final se estudia optimización avanzada.
