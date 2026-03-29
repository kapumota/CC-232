###  Resumen final - Semana 1

#### 1. Algoritmo

Un **algoritmo** es un procedimiento preciso, finito y efectivo que, a partir de una **entrada**, produce una **salida** mediante una secuencia de pasos bien definidos.

**Ejemplos del código:**
- `sumI(A,n)`: suma los elementos de un arreglo.
- `maxI(A,n)`: halla el mayor elemento.
- `power(a,n)`: calcula $a^n$.
- `bubbleSortBasic(A,n)`: ordena un arreglo.

**Idea clave:** un algoritmo describe cómo resolver un problema paso a paso.

#### 2. Entrada
La **entrada** es la información que recibe el algoritmo para trabajar.

**Ejemplos:**
- En `sumI(A,n)`, la entrada es el arreglo `A` y su tamaño `n`.
- En `gcdCN(a,b)`, la entrada son dos enteros.
- En `solveHanoi(n,...)`, la entrada es el número de discos y las torres.

#### 3. Salida
La **salida** es el resultado que produce el algoritmo.

**Ejemplos:**
- `sumI(A,n)` devuelve la suma total.
- `maxI(A,n)` devuelve el valor máximo.
- `gcdCN(a,b)` devuelve el máximo común divisor.
- `solveHanoi(...)` produce una secuencia de movimientos.

#### 4. Operaciones básicas
Son las operaciones elementales del modelo RAM: asignar, comparar, sumar, multiplicar, acceder a una posición, intercambiar, desplazar bits.

**Ejemplos en el código:**
- `acc += A[i]`
- `A[i - 1] > A[i]`
- `std::swap(A[i], A[j])`
- `n >>= 1`
- `pow *= p`

**Idea clave:** el costo computacional se mide contando este tipo de operaciones.

#### 5. Determinismo
Un algoritmo es **determinista** si, dada la misma entrada, siempre sigue los mismos pasos y produce la misma salida.

**Ejemplos:**
- `sumI`
- `power`
- `bubbleSort`
- `fib`
- `gcdCN`

**Idea clave:** no hay azar en su comportamiento.


#### 6. Factibilidad
Un algoritmo es **factible** si sus pasos pueden ejecutarse realmente con operaciones permitidas.

**Ejemplos:**
- `sumI`, `maxI` y `power` son claramente factibles.
- `fib(n)` ingenuo también lo es, pero deja de ser práctico cuando `n` crece mucho.

**Idea clave:** que un algoritmo exista no significa que sea útil para entradas grandes.

#### 7. Finitud
Un algoritmo cumple **finitud** si termina después de una cantidad finita de pasos.

**Ejemplos:**
- En `sumI`, `i` aumenta hasta `n`.
- En `sum(A,n)`, `n` baja hasta 0.
- En `power(a,n)`, `n` se reduce con `n >>= 1`.
- En `bubbleSortOptimized`, el arreglo se ordena o se detecta que ya no hay cambios.

**Idea clave:** un algoritmo que no termina no resuelve el problema.

#### 8. Corrección
Un algoritmo es **correcto** si, para toda entrada válida, produce la salida esperada.

**Ejemplos:**
- `sumI`, `sum(A,n)` y `sum(A,lo,hi)` deben dar el mismo resultado.
- `powerBF` y `power` deben calcular la misma potencia.
- `countOnes1` y `countOnes2` deben contar igual la cantidad de bits en 1.

**Idea clave:** no basta con que el algoritmo termine; además debe responder bien.


#### 9. Orden local
Existe **orden local** cuando no hay pares consecutivos desordenados.

En un arreglo, significa que no existe un índice `i` tal que:

$$
A[i] > A[i+1]
$$

**En el código:**
- `inversionWitnesses(A,n)` detecta ejemplos de desorden local.


#### 10. Orden global
Hay **orden global** cuando todo el arreglo está ordenado de principio a fin.

**En el código:**
- `isSortedNonDecreasing(A,n)` verifica si el arreglo completo está ordenado.

**Relación importante:**
En arreglos lineales, si desaparece todo desorden local, se obtiene orden global.


#### 11. Invariancia
Una **invariante** es una propiedad que se mantiene verdadera durante la ejecución de un algoritmo.

Sirve para demostrar corrección.

### Ejemplos

**`sumI`**
- Antes de cada iteración:

$$
acc = \text{suma de } A[0..i-1]
$$

**`bubbleSort`**
- Después de cada pasada, el mayor elemento del tramo recorrido queda en su posición final.

**`power(a,n)`**
- Se conserva la relación:

$$
pow \cdot p^n = a^{n_{\text{original}}}
$$

**`fibI`**
- Las variables mantienen la relación entre Fibonacci consecutivos.

**ADT de secuencia**
- En `FixedArraySequence`, se mantiene:

$$
0 \le n \le capacidad
$$

**Idea clave:** la invariante explica por qué el algoritmo no pierde el rumbo.


#### 12. Monotonicidad
La **monotonicidad** es una medida de progreso que cambia siempre en una misma dirección.

**Ejemplos:**
- en `sumI`, `i` solo aumenta;
- en `sum(A,n)`, `n` solo disminuye;
- en `power`, `n` se reduce por mitades;
- en `bubbleSort`, el desorden disminuye;
- en Hanoi, la cantidad mínima de movimientos crece con `n`.

**Idea clave:** la monotonicidad ayuda a probar finitud y corrección.

#### 13. Prueba de finitud
Para demostrar que un algoritmo termina, se muestra que existe una medida que se acerca al caso final.

**Ejemplos:**
- `sumI`: cada vez faltan menos elementos.
- `sum(A,n)`: `n` disminuye hasta 0.
- `reverseRecursive(A,n)`: el tamaño se reduce a `n-2`.
- `power2(n)`: el tamaño se reduce a la mitad.
- `solveHanoi(n,...)`: se llama con `n-1`.

#### 14. Prueba de corrección
La corrección se demuestra usando:
- invariantes, en algoritmos iterativos;
- inducción, en algoritmos recursivos;
- poscondiciones, al finalizar.

**Ejemplos:**
- `sumI`: al final del ciclo, `acc` contiene la suma total.
- `sum(A,n)`: si `sum(A,n-1)` es correcta, al sumar `A[n-1]` se obtiene el caso `n`.
- `maxRDivide`: si cada mitad resuelve bien su máximo, el máximo total es el mayor entre ambos.
- `bubbleSort`: si en cada pasada el mayor queda al final, tras suficientes pasadas el arreglo queda ordenado.


#### 15. Calidad práctica de los algoritmos
No basta con que un algoritmo sea correcto; también debe ser útil en la práctica.

Esto incluye:
- degeneración,
- robustez,
- reutilización,
- eficiencia.


#### 16. Degeneración
La **degeneración** ocurre cuando el algoritmo, aunque correcto, se comporta muy mal en ciertos casos.

**Ejemplos:**
- `bubbleSortBasic` sigue siendo $O(n^2)$ aunque el arreglo esté casi ordenado.
- `fib(n)` ingenuo se vuelve muy costoso por recomputar.
- `solveHanoi` crece exponencialmente.

**Idea clave:** algunos algoritmos empeoran mucho cuando la entrada crece o tiene cierta forma.

#### 17. Robustez
Un algoritmo es **robusto** si maneja correctamente casos borde o entradas poco cómodas.

**Ejemplos del código:**
- sumar un arreglo vacío,
- `gcdCN(-270,192)`,
- `gcdCN(0,5)`,
- `shiftLeftByK` con `k > n`,
- bubble sort con duplicados.

**Idea clave:** un algoritmo robusto no falla fácilmente ante entradas especiales.

#### 18. Reutilización
La **reutilización** consiste en aprovechar una solución o componente en varios contextos.

**Ejemplos:**
- `reverseIterative` se usa dentro de `shiftLeftByK`.
- `IntSequence` permite varias implementaciones bajo la misma interfaz.
- `Semana1.h` agrupa componentes que pueden reutilizarse.

**Idea clave:** reutilizar reduce errores y mejora el diseño.

#### 19. Eficiencia de los algoritmos
La **eficiencia** mide qué tan económico es un algoritmo en tiempo y memoria.

Se conecta con:
- computabilidad,
- intratabilidad,
- eficiencia computacional.


#### 20. Computabilidad
Un problema es **computable** si existe un algoritmo que lo resuelve en tiempo finito.

**Ejemplos computables del código:**
- sumar,
- hallar máximos,
- invertir arreglos,
- ordenar,
- calcular Fibonacci,
- hallar MCD,
- resolver Hanoi.

#### 21. Intratabilidad
Un problema puede ser computable, pero no práctico para tamaños grandes.

**Ejemplos:**
- `fib(n)` ingenuo tiene costo exponencial.
- `solveHanoi` requiere:

$$
2^n - 1
$$

movimientos.

**Idea clave:** computable no siempre significa eficiente.


#### 22. Eficiencia computacional
Se refiere a la cantidad de recursos que consume un algoritmo.

**Ejemplos:**
- `power(a,n)` es mucho mejor que `powerBF(a,n)`.
- `bubbleSortOptimized` mejora el mejor caso respecto a `bubbleSortBasic`.
- `sumI` usa menos pila que `sum(A,n)`.


#### 23. Relación entre algoritmos y estructuras de datos
Un algoritmo depende de cómo están organizados los datos sobre los que trabaja.

En `demo_adt_secuencia.cpp` aparece el ADT `IntSequence` con operaciones:
- `size()`
- `get(i)`
- `set(i,x)`
- `add(i,x)`
- `remove(i)`

y dos implementaciones:
- `FixedArraySequence`
- `VectorSequence`

**Idea clave:**
- el **ADT** define qué operaciones existen;
- la **estructura de datos** define cómo se representan internamente;
- el **algoritmo** se apoya en esa representación.

**Ejemplo:**
- `get(i)` suele costar $O(1)$,
- `add(i,x)` en medio suele costar $O(n)$, porque hay que desplazar elementos.


#### 24. Medición del costo computacional
Consiste en contar cuántas operaciones básicas realiza un algoritmo según el tamaño de la entrada.

No se mide por segundos exactos, sino por crecimiento.

**Ejemplos:**
- `sumI(A,n)` recorre una vez el arreglo.
- `bubbleSortBasic(A,n)` hace comparaciones en varias pasadas.
- `power(a,n)` reduce el exponente por mitades.


#### 25. Complejidad temporal
La **complejidad temporal** indica cómo crece el tiempo de ejecución.

### Ejemplos
- `sumI`: $O(n)$
- `sum(A,n)`: $O(n)$
- `sum(A,lo,hi)`: $O(n)$
- `powerBF(a,n)`: $O(n)$
- `power(a,n)`: $O(\log n)$
- `bubbleSortBasic`: $O(n^2)$
- `bubbleSortOptimized`: mejor caso $O(n)$, peor caso $O(n^2)$
- `fib(n)` ingenuo: $O(2^n)$
- `solveHanoi`: $O(2^n)$


#### 26. Complejidad espacial
La **complejidad espacial** mide cuánta memoria adicional necesita el algoritmo.

**Ejemplos**

- `sumI`: $O(1)$
- `sum(A,n)`: $O(n)$ por la pila recursiva
- `power(a,n)`: $O(1)$
- `power2(n)`: $O(\log n)$
- `bubbleSortBasic`: $O(1)$
- Hanoi con almacenamiento de movimientos: hasta $O(2^n)$ para la lista


#### 27. Complejidad asintótica
La **complejidad asintótica** estudia el comportamiento del algoritmo cuando el tamaño de entrada crece mucho.

No importa tanto el costo exacto para valores pequeños, sino la tendencia de crecimiento.

**Ejemplo:**
- `powerBF(a,n)` hace `n` multiplicaciones.
- `power(a,n)` hace aproximadamente $\log_2 n$ iteraciones.

Para `n = 1024`:
- el primero hace alrededor de 1024 pasos,
- el segundo alrededor de 10.


#### 28. Notación O grande
La notación **$O$** da una cota superior del crecimiento.

$$
T(n)=O(f(n))
$$

significa que el algoritmo no crece más rápido que una constante por $f(n)$, para `n` grande.

**Ejemplo:**
- `bubbleSortBasic` es $O(n^2)$.


#### 29. Notación $\Omega$ grande
La notación **$\Omega$** da una cota inferior.

$$
T(n)=\Omega(f(n))
$$

significa que el algoritmo crece al menos como $f(n)$.

**Ejemplo:**
- `sumI` es $\Omega(n)$, porque para sumar todos los elementos hay que leerlos.


#### 30. Notación $\Theta$ grande
La notación **$\Theta$** da una cota ajustada.

$$
T(n)=\Theta(f(n))
$$

significa que el algoritmo crece exactamente en ese orden.

**Ejemplos:**
- `sumI`: $\Theta(n)$
- `power(a,n)`: $\Theta(\log n)$
- `bubbleSortBasic`: $\Theta(n^2)$


#### 31. Peor caso
El **peor caso** es la entrada que hace trabajar más al algoritmo.

**Ejemplo:**
- `bubbleSortBasic` con arreglo invertido tiene costo $O(n^2)$.


#### 32. Mejor caso
El **mejor caso** es la entrada que hace trabajar menos al algoritmo.

**Ejemplo:**
- `bubbleSortOptimized` sobre un arreglo ya ordenado termina en una sola pasada: $O(n)$.


#### 33. Caso promedio
El **caso promedio** representa el comportamiento esperado en entradas típicas.

**Ejemplo:**
- Bubble sort sigue siendo cuadrático en promedio.


#### 34. Jerarquía de crecimiento
De menor a mayor crecimiento:

$$
O(1) < O(\log n) < O(n) < O(n^2) < O(2^n)
$$

**Interpretación:**
- constante: no depende de `n`,
- logarítmico: crece muy lentamente,
- lineal: crece proporcionalmente,
- cuadrático: crece mucho más rápido,
- exponencial: se vuelve impracticable.

#### 35. Nivel $O(1)$
Costo constante.

**Ejemplos:**
- acceso a `A[i]`,
- comparación,
- asignación,
- una operación de intercambio simple.


#### 36. Nivel $O(\log n)$
El problema se reduce por mitades o por bits.

**Ejemplos:**
- `power(a,n)`
- `power2(n)`

**Razón:**

$$
n \gets \frac{n}{2}
$$

en cada paso.


#### 37. Nivel $O(n)$
El algoritmo recorre la entrada una vez o pocas veces.

**Ejemplos:**
- `sumI`
- `sum(A,n)`
- `sum(A,lo,hi)` en tiempo total
- `maxI`
- `maxRLinear`
- `reverseIterative`
- `reverseRecursive`

#### 38. Nivel $O(n^2)$
El trabajo crece cuadráticamente.

**Ejemplos:**
- `bubbleSortBasic`
- `bubbleSortOptimized` en peor caso


#### 39. Nivel $O(2^n)$
El crecimiento es explosivo.

**Ejemplos:**
- `fib(n)` ingenuo
- `solveHanoi`
- `hanoiMoveCount`


#### 40. Tamaño de entrada
El **tamaño de entrada** es la medida del problema usada para analizar el costo.

##### En arreglos
Suele ser el número de elementos:
- `sumI(A,n)`
- `bubbleSortBasic(A,n)`
- `reverseIterative(A,n)`

##### En enteros
Puede ser:
- el valor del número,
- o la cantidad de bits necesarios para representarlo.

**Ejemplos:**
- En `power(a,n)`, importa el exponente `n`.
- En `countOnes`, también puede analizarse según el número de bits.


#### 41. Efecto del tamaño de entrada en el análisis
El mismo problema puede cambiar mucho según el algoritmo usado.

**Ejemplo:**
- potencia ingenua: $O(n)$
- potencia rápida: $O(\log n)$

**Idea clave:** elegir un mejor algoritmo cambia radicalmente el comportamiento cuando la entrada crece.

#### 42. Recursión
La **recursión** es una técnica donde un algoritmo se define en términos de sí mismo sobre instancias más pequeñas del problema.

#### 43. Caso base
Es la condición de parada de la recursión.

**Ejemplos:**
- `sum(A,n)`: `n <= 0`
- `power2(n)`: `n == 0`
- `reverseRecursive(A,n)`: `n < 2`
- `solveHanoi`: `n <= 0`

**Idea clave:** sin caso base, la recursión no termina.


#### 44. Reducción del problema
Cada llamada recursiva debe trabajar sobre una versión más pequeña del problema.

**Ejemplos:**
- `sum(A,n)` reduce a `n-1`
- `reverseRecursive` reduce a `n-2`
- `power2(n)` reduce a `n/2`
- `solveHanoi` reduce a `n-1`

#### 45. Trazado recursivo
Consiste en seguir las llamadas recursivas paso a paso.

**Ejemplo con `sum(A,n)` para `A=[4,7,2]`:**

$$
sum(A,3)=sum(A,2)+2
$$

$$
sum(A,2)=sum(A,1)+7
$$

$$
sum(A,1)=sum(A,0)+4
$$

$$
sum(A,0)=0
$$

Al regresar:
- `sum(A,1)=4`
- `sum(A,2)=11`
- `sum(A,3)=13`


#### 46. Patrones de recursión
Son formas típicas en que aparece la recursión.

##### a. Recursión lineal
Cada llamada genera una sola llamada recursiva.

**Ejemplos:**
- `sum(A,n)`
- `maxRLinear`
- `power2BF`

##### b. Divide y vencerás
El problema se divide en partes, se resuelven y se combinan.

**Ejemplos:**
- `sum(A,lo,hi)`
- `maxRDivide`
- `power2(n)`

##### c. Múltiples ramas
Cada llamada genera varias subllamadas.

**Ejemplos:**
- `fib(n)` ingenuo
- `solveHanoi`

**Idea clave:** este patrón puede crecer muy rápido.

#### 47. Idea final de la semana
La Semana 1 enseña que estudiar algoritmos no es solo programar funciones. También implica:

1. definir claramente el problema;
2. diseñar una solución;
3. demostrar que termina;
4. demostrar que es correcta;
5. medir su costo;
6. comparar alternativas;
7. relacionar el algoritmo con la estructura de datos.


#### 48. Síntesis final para memorizar
Un algoritmo debe tener:
- **entrada**
- **salida**
- **determinismo**
- **factibilidad**
- **finitud**
- **corrección**

Su calidad práctica depende de:
- **robustez**
- **reutilización**
- **eficiencia**
- **comportamiento ante casos difíciles**

La eficiencia se estudia con:
- **complejidad temporal**
- **complejidad espacial**
- **notaciones asintóticas**
- **mejor, peor y caso promedio**

La recursión exige:
- **caso base**
- **reducción**
- **combinación correcta**

Y el código de `Semana1` muestra ejemplos de:
- algoritmos lineales como `sumI`,
- logarítmicos como `power`,
- cuadráticos como `bubbleSort`,
- exponenciales como `fib` ingenuo y `Hanoi`.

