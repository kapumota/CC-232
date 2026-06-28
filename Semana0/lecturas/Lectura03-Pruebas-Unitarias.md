### Lectura03: Pruebas unitarias en CC232

#### Propósito

Las pruebas unitarias permiten verificar que una función, clase o módulo cumple su contrato en casos normales y casos borde o frontera.

En CC232, las pruebas son parte del diseño de una estructura de datos. No son un paso decorativo al final.

#### Idea central

Una estructura de datos debe cumplir invariantes. Las pruebas ayudan a detectar cuando una operación rompe esos invariantes.

Ejemplos:

1. Un arreglo dinámico debe conservar el orden de los elementos insertados.
2. Una pila debe retirar primero el último elemento insertado.
3. Un heap debe mantener la propiedad de prioridad.
4. Un árbol balanceado debe respetar orden e invariantes de altura o color.

#### Pruebas con assert

Una prueba mínima puede usar `assert`:

```cpp id="tbkemc"
#include <cassert>

int add(int a, int b) {
    return a + b;
}

int main() {
    assert(add(2, 3) == 5);
}
```

#### Patrón AAA

El patrón AAA organiza una prueba en tres partes:

| Parte   | Significado                                 |
| ------- | ------------------------------------------- |
| Arrange | Preparar datos y objeto bajo prueba.        |
| Act     | Ejecutar la operación que se quiere probar. |
| Assert  | Verificar el resultado esperado.            |

#### Pruebas públicas

Las pruebas públicas son visibles para el estudiante. Sirven para confirmar el contrato mínimo de la actividad.

#### Pruebas internas

Las pruebas internas no deben estar en el repositorio público del estudiante. Sirven para evaluar casos borde, invariantes y errores frecuentes.

#### CTest

CTest permite ejecutar pruebas registradas desde CMake. En este curso se usa para tener un flujo uniforme:

```bash id="go5mtv"
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

#### Diferencia entre prueba y benchmark

| Elemento  | Pregunta principal                   |
| --------- | ------------------------------------ |
| Prueba    | El resultado es correcto.            |
| Benchmark | Cuánto tarda o cuántos recursos usa. |

Primero se prueba correctitud. Después se mide rendimiento.

#### Recomendación para el curso

Cada estructura de datos debe tener pruebas que cubran:

1. Caso vacío.
2. Un elemento.
3. Varios elementos.
4. Repetidos si el contrato los permite.
5. Eliminaciones.
6. Casos borde.
7. Invariantes después de muchas operaciones.
