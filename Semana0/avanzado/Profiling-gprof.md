### Profiling con gprof

#### Propósito

Este documento separa el uso de profiling de la actividad base de Semana0.

El profiling ayuda a identificar funciones que consumen más tiempo, pero no reemplaza pruebas unitarias ni validación con sanitizers.

#### Flujo general

1. Compilar con soporte de profiling.
2. Ejecutar el programa con una carga representativa.
3. Generar el reporte.
4. Identificar funciones costosas.
5. Relacionar el costo con la complejidad esperada.

#### Advertencia

Un reporte de profiling solo tiene sentido si el programa ya es correcto.

Medir un programa incorrecto produce conclusiones inválidas.
