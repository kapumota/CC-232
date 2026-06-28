### Lectura03: Pruebas unitarias en CC232

#### Proposito

Las pruebas unitarias permiten verificar que una funcion, clase o modulo cumple su contrato en casos normales y casos borde o frontera.

En CC232, las pruebas son parte del diseño de una estructura de datos. No son un paso decorativo al final.

#### Idea central

Una estructura de datos debe cumplir invariantes. Las pruebas ayudan a detectar cuando una operacion rompe esos invariantes.

Ejemplos:

1. Un arreglo dinamico debe conservar el orden de los elementos insertados.
2. Una pila debe retirar primero el ultimo elemento insertado.
3. Un heap debe mantener la propiedad de prioridad.
4. Un arbol balanceado debe respetar orden e invariantes de altura o color.

#### Pruebas con assert

Una prueba minima puede usar `assert`:

```cpp
#include <cassert>

int add(int a, int b) {
    return a + b;
}

int main() {
    assert(add(2, 3) == 5);
}
```

#### Patron AAA

El patron AAA organiza una prueba en tres partes:

| Parte | Significado |
|---|---|
| Arrange | Preparar datos y objeto bajo prueba. |
| Act | Ejecutar la operacion que se quiere probar. |
| Assert | Verificar el resultado esperado. |

#### Pruebas publicas

Las pruebas publicas son visibles para el estudiante. Sirven para confirmar el contrato minimo de la actividad.

#### Pruebas internas

Las pruebas internas no deben estar en el repositorio publico del estudiante. Sirven para evaluar casos borde, invariantes y errores frecuentes.

#### CTest

CTest permite ejecutar pruebas registradas desde CMake. En este curso se usa para tener un flujo uniforme:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

#### Diferencia entre prueba y benchmark

| Elemento | Pregunta principal |
|---|---|
| Prueba | El resultado es correcto. |
| Benchmark | Cuanto tarda o cuantos recursos usa. |

Primero se prueba correctitud. Despues se mide rendimiento.

#### Recomendacion para el curso

Cada estructura de datos debe tener pruebas que cubran:

1. Caso vacio.
2. Un elemento.
3. Varios elementos.
4. Repetidos si el contrato los permite.
5. Eliminaciones.
6. Casos borde.
7. Invariantes despues de muchas operaciones.
