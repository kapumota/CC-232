### Resumen final - Semana 4

#### Pilas, colas, recursión, expresiones, backtracking y simulación

La Semana 4 se concentra en dos estructuras lineales fundamentales: la pila (`Stack`) y la cola (`Queue`).
Aunque ambas pueden parecer más simples que vectores y listas, su importancia aparece cuando dejan de verse solo como contenedores y pasan a funcionar 
como mecanismos de control para resolver problemas. 

Una pila no solo guarda datos: permite modelar lo último pendiente, simular llamadas recursivas, invertir secuencias, verificar anidamientos y explorar
soluciones parciales con retroceso. Una cola no solo almacena elementos: permite modelar espera, atención, turnos, reparto de recursos y procesos donde 
debe respetarse el orden de llegada.

En semanas anteriores se estudiaron estructuras secuenciales más generales. La Semana 2 se enfocó en arreglos y vectores, donde el acceso por í
ndice es natural porque la memoria se organiza de forma contigua o casi contigua.
La Semana 3 se enfocó en listas enlazadas, donde el acceso por posición y la modificación local se vuelven centrales.
La Semana 4 toma esas estructuras como base conceptual y muestra que, al restringir las operaciones permitidas, se obtienen ADT más simples pero muy poderosos.
En una pila se restringen inserción, eliminación y consulta a un mismo extremo, en una cola se inserta por un extremo y se elimina por el otro.

El cambio principal no es solo técnico, sino algorítmico. `Stack` y `Queue` no se estudian únicamente para saber cómo implementar `push`, `pop`, `enqueue` o `dequeue`, sino para entender por qué esas operaciones son suficientes para resolver problemas clásicos. 
La pila aparece en conversión de base, emparejamiento de paréntesis, evaluación de expresiones, notación polaca inversa, N-Reinas y búsqueda en laberintos. 
La cola aparece en planificación, simulación de atención, asignación cíclica de recursos y procesos de espera. 

En ese sentido, la semana conecta estructura de datos, estado parcial, control de flujo e invariantes.

#### 1. Pila (`Stack`): idea central

Una pila es un contenedor lineal con una regla estricta: solo se puede insertar y eliminar por el mismo extremo. 
Ese extremo se llama tope (`top`). El otro extremo se llama fondo (`bottom`) y no es directamente operable. 
La analogía clásica es una pila de sillas o platos: se coloca una silla encima y se retira también la que está encima. No se retira directamente una
silla intermedia sin romper la disciplina de la estructura.

La política de una pila se resume como `LIFO`: *last in, first out*, o "último en entrar, primero en salir". Si se apilan los elementos `5`, `3`, `7`, el primer elemento que sale será `7`, luego `3` y finalmente `5`. 

Esto no depende de la implementación, sino del contrato abstracto de la pila. La implementación puede usar un arreglo, un vector, una lista o incluso una 
estructura más especializada, pero la semántica externa debe ser la misma.

La interfaz básica de una pila contiene:

| Operación | Significado |
|---|---|
| `size()` | Devuelve el número de elementos almacenados. |
| `empty()` | Indica si la pila está vacía. |
| `push(e)` | Inserta `e` en el tope. |
| `pop()` | Elimina y devuelve el elemento del tope. |
| `top()` | Consulta el elemento del tope sin eliminarlo. |
| `clear()` | Vacía la estructura, si la implementación lo ofrece. |

En la lectura de Deng, la pila puede implementarse como una clase derivada de `Vector`, reutilizando `insert(size(), e)`, `remove(size()-1)` y el acceso al último elemento. 
Esta decisión es natural porque el extremo final de un vector suele permitir inserciones y eliminaciones eficientes. 
En el código de Semana 4, la implementación se hace directamente sobre `std::vector`: `push` usa `push_back`, `pop` toma el último elemento y luego 
hace `pop_back`, y `top` retorna `data_.back()`. La estructura se mantiene sencilla y alineada con la idea LIFO.

La complejidad esperada de las operaciones principales es constante amortizada cuando se usa un vector dinámico. `top`, `empty` y `size` son constantes.
`push` suele ser constante amortizada porque el vector puede redimensionarse ocasionalmente. 
`pop` es constante porque elimina el último elemento sin desplazar otros datos. 

Este comportamiento confirma una idea importante: cuando un ADT restringe sus operaciones al extremo adecuado, una estructura aparentemente general puede volverse muy eficiente.

#### 2. Cola (`Queue`): idea central

Una cola también es una estructura lineal, pero su disciplina es opuesta a la de la pila. En una cola, los elementos se insertan por un extremo y se eliminan por el otro. 
El extremo de eliminación se llama frente (`front`) y el extremo de inserción se llama final o cola (`rear`). 

La analogía cotidiana es una fila de atención: quien llegó primero debe ser atendido primero.

La política de una cola se resume como `FIFO`: *first in, first out*, o "primero en entrar, primero en salir". Si se encolan los elementos `5`, `3`, `7`, el primero que se desencola será `5`, luego `3` y finalmente `7`. 
Esta propiedad hace que las colas sean adecuadas para simular procesos de espera, turnos, atención en ventanillas, planificación de tareas y reparto justo de recursos.

La interfaz básica de una cola contiene:

| Operación | Significado |
|---|---|
| `size()` | Devuelve el número de elementos. |
| `empty()` | Indica si la cola está vacía. |
| `enqueue(e)` | Inserta `e` al final. |
| `dequeue()` | Elimina y devuelve el elemento del frente. |
| `front()` | Consulta el elemento del frente sin eliminarlo. |
| `clear()` | Vacía la estructura, si la implementación lo ofrece. |

En Deng, la cola se implementa naturalmente sobre una lista: `enqueue(e)` equivale a insertar al final, `dequeue()` equivale a eliminar el primer nodo y `front()` devuelve el dato del primer nodo. 
Si la lista mantiene acceso eficiente a ambos extremos, estas operaciones son constantes. 
En el código de Semana 4, `Queue.h` usa `std::deque`, una estructura de biblioteca estándar que permite insertar al final y eliminar al frente de forma 
eficiente. `enqueue` usa `push_back`, `dequeue` usa `pop_front` y `front` consulta `data_.front()`.

La cola tiene un papel diferente al de la pila. La pila es excelente cuando importa "lo último pendiente". La cola es excelente cuando importa "lo más antiguo pendiente". 
Por eso una pila sirve para deshacer acciones recientes, recorrer caminos con retroceso o evaluar expresiones anidadas. 
Una cola sirve para repartir atención y mantener justicia temporal.


#### 3. De ADT básico a herramienta algorítmica

La idea más importante de la semana es que `Stack` y `Queue` son ADT simples, pero su simplicidad es precisamente lo que los hace útiles. 
Una pila puede registrar decisiones parciales en el mismo orden en que deberán deshacerse. Una cola puede registrar solicitudes pendientes en el mismo orden en que deberán atenderse. 
La estructura auxiliar no es un detalle: define el modo en que el algoritmo recuerda, avanza, espera o retrocede.

En una pila, la operación natural después de una decisión reciente es revisar o retirar esa misma decisión. Por eso funciona tan bien para:

| Problema | Por qué sirve una pila |
|---|---|
| Conversión de base | Los residuos se calculan de menor a mayor, pero se imprimen de mayor a menor. |
| Paréntesis | Cada cierre debe corresponder a la apertura pendiente más reciente. |
| RPN | Los operandos necesarios para un operador están en la cima. |
| Backtracking | La última decisión tomada es la primera que debe deshacerse. |
| Recursión | La última llamada activa es la primera que retorna. |

En una cola, la operación natural después de una llegada es esperar turno hasta que todos los anteriores hayan sido atendidos. Por eso funciona bien para:

| Problema | Por qué sirve una cola |
|---|---|
| Atención bancaria | El cliente más antiguo en una ventanilla se atiende primero. |
| Round Robin | Cada cliente usa un recurso y vuelve al final. |
| Planificación | Se preserva orden de llegada o rotación. |
| Simulación | Permite modelar estados pendientes en el tiempo. |

Esta diferencia permite responder una pregunta de fondo: no se elige una pila o una cola por costumbre, sino porque el patrón temporal del problema
coincide con `LIFO` o con `FIFO`.

#### 4. Pila de llamadas y recursión

La recursión se implementa mediante una pila de llamadas. Cada vez que una función llama a otra función, o se llama a sí misma, el sistema crea un marco de activación (`frame`). 
Ese marco almacena información necesaria para que la ejecución pueda continuar correctamente: dirección de retorno, parámetros, variables locales y datos administrativos. 
El marco se apila sobre los marcos anteriores. Cuando la función termina, su marco se desapila y el control vuelve a la llamada previa.

La figura de la pila de llamadas en el documento muestra la relación entre el código ejecutable y la pila de ejecución: `main()` llama a una función, esa función llama a otra, y una función puede llamarse recursivamente. 
En cualquier instante, la pila contiene exactamente las funciones activas que todavía no han terminado. 
El marco inferior corresponde normalmente a `main`, el marco superior corresponde a la función que se está ejecutando en ese momento.

Esta observación explica por qué la recursión consume memoria proporcional a la profundidad máxima de llamadas. Si un algoritmo recursivo alcanza profundidad `d`, en el peor momento existen `d` marcos activos. 
Aunque la definición recursiva sea elegante, cada marco tiene costo. Además de los datos realmente necesarios para resolver el problema, el sistema debe guardar información de retorno y restauración. 
Por eso Deng enfatiza que, cuando se busca eficiencia, puede convenir reemplazar la recursión implícita por una pila explícita.

Reemplazar recursión implícita significa que el programador decide qué información debe guardarse. En lugar de dejar que el sistema almacene todo un marco de activación, se define una estructura más pequeña que contenga solo el estado necesario.
Por ejemplo, en N-Reinas basta guardar las reinas ya colocadas, en un laberinto basta guardar las celdas del camino actual y marcas de estado, en evaluación de expresiones se guardan operandos y operadores pendientes. 
Esta técnica reduce control oculto y hace explícitos los invariantes.

La recursión no es "mala". Es expresiva, legible y muchas veces natural. El punto de la semana es más preciso: como la recursión se apoya en una pila 
implícita, podemos sustituirla por una pila explícita cuando queramos controlar mejor el estado, el espacio o el comportamiento del algoritmo.

#### 5. Conversión de base

La conversión de base es una aplicación clásica de pila. Dado un número decimal `n` y una base `b`, los dígitos de la nueva representación se obtienen dividiendo sucesivamente entre `b`. 
En cada paso, el residuo `n % b` produce el siguiente dígito menos significativo, y luego se actualiza `n = n / b`. 
El problema es que los dígitos se calculan desde el menos significativo hacia el más significativo, pero la representación final debe escribirse en el orden contrario.

Por ejemplo, si convertimos un número a base 8, primero aparece el dígito de las unidades, luego el de las "ochos", luego el de las "sesenta y cuatro", y así sucesivamente. 
La pila resuelve exactamente este desfase: se apilan los residuos conforme aparecen y luego se desapilan para obtenerlos en orden inverso. 
La propiedad `LIFO` convierte automáticamente una secuencia calculada de atrás hacia adelante en una salida de adelante hacia atrás.

El algoritmo general es:

```text
mientras n > 0:
    residuo = n % base
    apilar símbolo[residuo]
    n = n / base

mientras la pila no esté vacía:
    desapilar y agregar a la respuesta
```

La versión recursiva y la versión iterativa comparten la misma relación matemática: cociente y residuo. La diferencia está en quién controla el avance. En la versión recursiva, el progreso se expresa mediante llamadas sucesivas con `n / base`. 
En la versión iterativa, el progreso se expresa con un ciclo `while`. En ambos casos, la pila se usa para reconstruir la salida final.

En el código de Semana 4, `BaseConversion.h` define `validateBase(base)`, que exige bases entre 2 y 16. También usa la tabla de símbolos `0123456789ABCDEF`, suficiente para representar bases hasta hexadecimal. 
La función `toBaseRecursive` maneja el caso especial `n == 0`, crea una pila de caracteres y delega el trabajo en `convertRecursive`. 
La función `toBaseIterative` hace lo mismo con `convertIterative`. Finalmente, `popAll` desapila todos los caracteres y forma la cadena final.

La complejidad temporal es `O(log_b n)`, porque cada división reduce el valor de `n` por un factor `b`. La cantidad de dígitos en base `b` también
es `O(log_b n)`, por lo que el espacio auxiliar usado por la pila es proporcional al número de dígitos. 
La diferencia práctica entre recursivo e iterativo no está en el orden asintótico, sino en el control del espacio: la versión recursiva usa además la pila de llamadas, mientras que la iterativa usa solo la pila explícita de dígitos.

#### 6. Permutaciones por pila

El documento introduce las permutaciones por pila para mostrar cómo la disciplina `LIFO` impone restricciones sobre el orden de salida. 
Se consideran tres pilas: una pila de entrada `A`, una pila auxiliar `S` y una pila de salida `B`. Las operaciones permitidas son mover el tope de `A` hacia `S`, y mover el tope de `S` hacia `B`.
Después de `n` apilados y `n` desapilados, se obtiene una permutación de los elementos originales.

La idea esencial es que no todas las permutaciones surgen arbitrariamente: deben poder generarse respetando que `S` solo entrega el último elemento que recibió. 
Cada secuencia válida de operaciones debe cumplir que, en cualquier prefijo, no haya más operaciones de desapilado que de apilado. 
De lo contrario, se intentaría sacar un elemento de una pila vacía.

Este tema sirve como puente conceptual hacia los paréntesis. Una secuencia de `push` y `pop` válida se parece a una expresión con paréntesis balanceados: cada `push` abre una obligación pendiente y cada `pop` la cierra. 
Si en algún punto se intenta cerrar algo que no existe, la secuencia es inválida. Si al final quedan aperturas pendientes, también es inválida.

#### 7. Emparejamiento de paréntesis

El emparejamiento de paréntesis es una aplicación directa de pila. El problema consiste en determinar si una expresión contiene delimitadores correctamente anidados. 
No basta con contar que haya la misma cantidad de aperturas y cierres, también debe respetarse el orden. Por ejemplo, `([{}])` es correcto, pero `([)]` no lo
es, aunque tenga dos aperturas y dos cierres.

Deng presenta primero una versión recursiva para paréntesis redondos. La idea es recortar partes sin paréntesis, verificar que el primer símbolo relevante 
sea `(` y el último sea `)`, buscar el punto donde el balance vuelve a cero y resolver recursivamente el interior y el sufijo restante. 
Esta técnica expresa el anidamiento mediante divide y vencerás, pero tiene limitaciones: puede costar `O(n^2)` en el peor caso y no se generaliza tan cómodamente a varios tipos de delimitadores.

La solución iterativa con pila es más simple y más general. Se recorre la expresión de izquierda a derecha. Cada vez que aparece una apertura `(`, `[` o `{`, se apila. Cada vez que aparece un cierre `)`, `]` o `}`, se revisa el tope. 
Si la pila está vacía, significa que hay un cierre sin apertura. Si el tope no corresponde al tipo de cierre, hay cruce incorrecto. 
Si corresponde, se desapila y se continúa. Al final, la expresión está balanceada solo si la pila queda vacía.

El algoritmo es:

```text
para cada carácter c en la expresión:
    si c es apertura:
        apilar c
    si c es cierre:
        si la pila está vacía: fallar
        si el tope no corresponde a c: fallar
        desapilar

aceptar si la pila quedó vacía
```

En el código de Semana 4, `Parentheses.h` contiene ambas versiones. `parenRecursive` usa las funciones auxiliares `trimParentheses` y `divideParentheses`, y se enfoca en paréntesis redondos. 
`parenIterative` usa una pila de caracteres y soporta `()`, `[]` y `{}`. Esta comparación es didácticamente importante porque muestra cómo una pila 
explícita puede reemplazar un esquema recursivo y, además, mejorar claridad, generalidad y complejidad.

La complejidad de la versión iterativa es `O(n)` en tiempo, porque cada carácter se examina una vez. El espacio auxiliar es `O(d)`, donde `d` es la 
profundidad máxima de anidamiento, en el peor caso, `d = n`, pero en expresiones típicas suele ser mucho menor.

#### 8. Búfer diferido y evaluación de expresiones

La evaluación de expresiones aritméticas es más compleja que recorrer de izquierda a derecha y ejecutar todo inmediatamente. 
En una expresión como `1 + 2 * 3`, no se debe ejecutar `1 + 2` antes de ver el `*`, porque la multiplicación tiene mayor prioridad. 
En una expresión con paréntesis, la situación es todavía más clara: parte del cálculo debe retrasarse hasta que se conozca el cierre del grupo.

Este patrón se llama búfer diferido: durante el escaneo, hay información que todavía no puede procesarse. Debe guardarse temporalmente hasta que el 
contexto permita decidir. Deng usa dos pilas:

| Pila | Qué almacena | Para qué sirve |
|---|---|---|
| `opnd` | Operandos o resultados parciales | Permite aplicar operadores cuando estén listos sus argumentos. |
| `optr` | Operadores pendientes | Permite decidir si se apila, se ejecuta o se cierra un grupo. |

La pila de operadores se controla mediante una tabla de precedencias. La tabla compara el operador que está en el tope de `optr` con el operador actual de
la entrada. El resultado puede ser:

| Relación | Interpretación | Acción típica |
|---|---|---|
| `<` | El operador actual domina al del tope | Apilar el operador actual. |
| `>` | El operador del tope domina al actual | Desapilar y ejecutar el operador del tope. |
| `=` | Hay emparejamiento o fin de expresión | Desapilar el símbolo de control. |
| espacio | Combinación inválida | Reportar error. |

La tabla incluye operadores aritméticos (`+`, `-`, `*`, `/`, `^`, `!`), paréntesis y el símbolo de fin de expresión `\0`. El factorial se trata como operador unario, suma, resta, multiplicación, división y potencia son operadores binarios. 
El uso de `\0` como centinela permite uniformizar el inicio y el final del proceso.

En el código de Semana 4, `OperatorPriority.h` define el enum `Operator`, la tabla `pri`, la función `optr2rank` y `orderBetween`. `ExpressionEvaluator.h` implementa la evaluación real. Primero elimina espacios con `removeSpaces`. Luego agrega `\0` al final de la cadena. 
Usa una pila de operandos `Stack<double>` y una pila de operadores `Stack<char>`. Cuando encuentra un número, lo lee completo con `readNumber`, lo apila y
lo agrega a la RPN. Cuando encuentra un operador, consulta la relación de prioridad y decide entre apilar, emparejar o ejecutar.

El evaluador también incluye mejoras prácticas. Detecta el menos unario cuando `-` aparece al inicio o después de otro operador o paréntesis izquierdo, siempre que lo siga un número. 
Controla división entre cero. Exige que el factorial reciba un operando entero no negativo. Si faltan operandos o la expresión no se reduce a un único valor, lanza error.

Estas decisiones no cambian la idea teórica, pero hacen la implementación más robusta.

La complejidad temporal esperada es lineal respecto a la longitud de la expresión, suponiendo que las operaciones aritméticas básicas sean constantes. Cada token se lee una vez, y cada operador se apila y desapila como máximo una vez. 
El espacio auxiliar es lineal en el peor caso, porque puede haber muchos operadores u operandos pendientes.

#### 9. Notación polaca inversa (`RPN`)

La notación polaca inversa, también llamada notación posfija, coloca cada operador después de sus operandos. Por ejemplo, la expresión infija `1 + 2` se escribe como `1 2 +`. 
Una expresión más compleja como `(1 + 2) * 3` se escribe como `1 2 + 3 *`. 
La ventaja es que ya no se necesitan paréntesis ni reglas de precedencia durante la evaluación: el orden de los operadores en la RPN es exactamente el orden de ejecución.

La evaluación de RPN usa una sola pila de operandos:

```text
para cada token de la expresión RPN:
    si es operando:
        apilarlo
    si es operador:
        desapilar sus operandos
        aplicar operación
        apilar resultado

el resultado final queda en el tope
```

La razón por la que esto funciona es la misma propiedad `LIFO`. Cuando aparece un operador, sus operandos más recientes son exactamente los que están en la cima de la pila. 
Para operadores binarios, se debe cuidar el orden: el primer valor desapilado es el operando derecho, y el segundo valor desapilado es el operando izquierdo. 
Esto importa para resta, división y potencia.

El evaluador de Semana 4 construye la RPN durante la evaluación de la expresión infija. La regla es simple: cada operando se agrega a la salida RPN cuando se lee, cada operador se agrega cuando se desapila y se ejecuta.
Esto reproduce automáticamente la conversión infija-a-posfija. 

La estructura `EvaluationResult` guarda tanto el valor numérico final como la cadena RPN generada. Esta decisión permite verificar al mismo tiempo dos
resultados: la evaluación y la traducción de forma.

Una ventaja conceptual de RPN es que separa dos problemas. Convertir de infija a RPN resuelve precedencia y paréntesis. 
Evaluar RPN resuelve el cálculo ya ordenado. Por eso RPN aparece frecuentemente en compiladores, calculadoras y máquinas virtuales basadas en pila.

#### 10. Prueba y retroceso (`backtracking`)

El backtracking es una estrategia de búsqueda para problemas donde una solución se construye paso a paso. En cada paso se prueba una decisión. 
Si la decisión permite avanzar, se extiende la solución parcial. Si conduce a un callejón sin salida, se retrocede hasta la decisión anterior y se prueba
otra alternativa.

Deng presenta esta idea mediante la historia de Teseo en el laberinto. El hilo representa la ruta actual: permite volver por donde se vino. 
La **tiza** representa las marcas que impiden explorar repetidamente lugares ya descartados. En términos de estructuras de datos, el hilo se modela con una pila y la tiza se modela con estados o marcas. 

La pila guarda la solución parcial, las marcas evitan ciclos y repeticiones inútiles.

El patrón general es:

```text
iniciar solución parcial vacía
mientras queden posibilidades:
    probar una extensión
    si es válida:
        apilar la decisión
        avanzar
    si no hay extensiones posibles:
        desapilar la última decisión
        probar la siguiente alternativa
```

La poda (`pruning`) ocurre cuando se detecta que una solución parcial no puede conducir a una solución completa. En ese momento no se exploran todas sus extensiones: se descarta toda esa rama del espacio de búsqueda. 
La eficiencia del backtracking depende mucho de la calidad de la poda. En el peor caso, muchos problemas siguen siendo exponenciales, pero una poda 
buena puede reducir drásticamente el número de candidatos examinados.

La pila es natural porque la última decisión tomada es la primera que debe deshacerse. Ese es exactamente el comportamiento `LIFO`.

#### 11. N-Reinas

El problema de N-Reinas consiste en colocar `n` reinas en un tablero `n x n` de modo que ninguna ataque a otra. Una reina ataca por fila, columna y diagonales.
Por el principio del problema, se coloca una reina por fila, entonces el algoritmo decide en qué columna poner la reina de cada fila.

La clase `Queen` del código representa una reina mediante dos coordenadas: `x` para fila y `y` para columna. La comparación `operator==` se redefine para 
significar "conflicto": dos reinas se consideran iguales si comparten fila, columna, diagonal principal o diagonal secundaria. 
Las diagonales se detectan con las expresiones `x + y` y `x - y`. Esta sobrecarga es pedagógica: permite preguntar si una reina candidata "coincide" con 
alguna ya colocada en el sentido de atacar.

El algoritmo `placeQueens(n)` usa una pila explícita llamada `solution`. Esa pila contiene las reinas ya colocadas, es decir, la solución parcial. 
La reina candidata `q` indica la fila y columna que se está probando. Si la candidata no entra en conflicto con ninguna reina de la pila, se apila y se pasa a la siguiente fila. 

Si no hay columna válida en una fila, se desapila la reina anterior, se incrementa su columna y se continúa probando.

La lógica puede resumirse así:

```text
solution = pila vacía
q = reina en fila 0, columna 0

mientras queden ramas:
    si la solución está completa o q salió del tablero:
        retroceder: q = pop(solution), q.y++
    si no:
        avanzar q.y hasta encontrar columna sin conflicto
        si existe columna válida:
            push(q)
            pasar a la fila siguiente
```

El resultado del código incluye:

| Campo | Significado |
|---|---|
| `n` | Tamaño del tablero. |
| `solutions` | Número de configuraciones completas encontradas. |
| `checks` | Número de verificaciones de conflicto realizadas. |
| `placements` | Lista de soluciones, si se decide recolectarlas. |

Es importante distinguir `solutions` y `checks`. `solutions` cuenta configuraciones válidas completas. `checks` mide trabajo interno de búsqueda: cada comparación entre una candidata y una reina ya colocada. Dos valores de `n` pueden tener pocas soluciones pero muchísimos chequeos, porque el algoritmo explora y descarta muchas ramas antes de confirmar soluciones o fallos.

El backtracking aparece de forma explícita. Apilar una reina significa aceptar provisionalmente una decisión. Desapilarla significa reconocer que esa rama no funcionó o que ya fue completada, y volver a probar otra columna. La poda ocurre cuando una reina candidata entra en conflicto con una reina existente: no se necesita probar filas posteriores bajo esa configuración, porque ya es inválida.

La complejidad del problema crece rápidamente. El algoritmo evita muchas configuraciones imposibles, pero el espacio de búsqueda sigue siendo combinatorio. Por eso el número de `checks` crece mucho más rápido que `n`.

#### 12. Laberinto

La búsqueda de camino en un laberinto es otro ejemplo de backtracking explícito. El laberinto se representa como una grilla de celdas. 
Cada celda puede estar disponible, formar parte de la ruta actual, haber sido descartada por retroceso o ser una pared.

En el código de Semana 4, `Maze.h` define los estados:

| Estado | Significado |
|---|---|
| `AVAILABLE` | Celda libre todavía no usada. |
| `ROUTE` | Celda que pertenece al camino actual. |
| `BACKTRACKED` | Celda explorada y descartada. |
| `WALL` | Obstáculo. |

También define direcciones:

| Dirección | Significado |
|---|---|
| `UNKNOWN` | Aún no se ha elegido dirección. |
| `EAST`, `SOUTH`, `WEST`, `NORTH` | Direcciones de exploración. |
| `NO_WAY` | Ya no quedan direcciones posibles. |

La pila `path` guarda el camino actual desde la celda inicial hasta la celda en exploración. El fondo de la pila es el inicio, el tope es la posición actual. 
En cada iteración, el algoritmo mira la celda actual. Si es la celda objetivo, encontró un camino. Si no, intenta direcciones en orden hasta encontrar un vecino disponible. 

Si lo encuentra, avanza, marca la celda como `ROUTE` y la apila. Si no encuentra salida, marca la celda como `BACKTRACKED` y la desapila.

El esquema es:

```text
apilar celda inicial
marcarla como ROUTE

mientras path no esté vacía:
    actual = top(path)
    si actual es destino: éxito
    buscar vecino AVAILABLE no probado
    si existe:
        avanzar y apilar vecino
    si no existe:
        marcar actual como BACKTRACKED
        desapilar

si la pila queda vacía: no hay camino
```

La diferencia con N-Reinas está en la representación del estado. En N-Reinas, la solución parcial es una lista de posiciones de reinas, una por fila. 
En el laberinto, la solución parcial es una ruta de celdas adyacentes. 
En ambos casos, la pila registra el camino de decisiones y el retroceso elimina la última decisión. Pero en el laberinto además se necesitan marcas para 
evitar ciclos, sin esas marcas, el algoritmo podría volver una y otra vez a las mismas celdas.

El documento destaca que este algoritmo encuentra un camino si el destino está conectado con el inicio, pero no necesariamente el camino más corto. 
Esto es típico de una búsqueda en profundidad (`DFS`) con pila. Para encontrar caminos mínimos en grafos no ponderados suele usarse una búsqueda en anchura 
(`BFS`) con cola. Esa comparación es muy útil: pila y cola no solo cambian el orden de almacenamiento, también cambian la estrategia de exploración.

La complejidad temporal es proporcional al número de celdas y direcciones exploradas. Si cada celda se marca y no se reexplora indefinidamente, cada celda
participa una cantidad acotada de veces. Por tanto, en una celda de `R x C`, el costo es `O(RC)` en el caso típico de recorrer la región alcanzable, con 
espacio `O(RC)` en el peor caso para la ruta y la celda de estados.


#### 13. Cola y asignación cíclica (`Round Robin`)

Después de las aplicaciones de pila, Deng introduce aplicaciones de cola. La primera idea importante es el asignador cíclico o `Round Robin`. 
Si varios clientes comparten un recurso, una política justa consiste en atender al cliente del frente durante un turno, retirarlo temporalmente, y luego 
reinsertarlo al final de la cola si todavía necesita más atención.

El patrón es:

```text
Q = cola de clientes
mientras el servicio esté abierto:
    e = Q.dequeue()
    serve(e)
    Q.enqueue(e)
```

Esta política aparece en planificación de CPU, turnos, recursos compartidos y simulaciones. La cola garantiza que nadie se quede permanentemente al frente
ni sea saltado indefinidamente. 
El tamaño del turno es una decisión de diseño: si es muy grande, la respuesta puede ser lenta, si es muy pequeño, el costo de cambiar de cliente puede dominar.

Este ejemplo muestra que `FIFO` no significa simplemente "sacar en orden". También puede significar rotación equilibrada. El cliente que acaba de recibir 
servicio vuelve al final, permitiendo que otros avancen.

#### 14. Simulación bancaria

La simulación bancaria es la aplicación principal de colas en Semana 4. Un banco tiene varias ventanillas. Cada ventanilla tiene su propia cola de clientes. 
En cada instante puede llegar un nuevo cliente, se le asigna una ventanilla, y cada ventanilla atiende al cliente que está en su frente. 
Cuando el tiempo restante de atención llega a cero, ese cliente sale de la cola.

El código define:

| Estructura | Significado |
|---|---|
| `Customer` | Cliente con `window` asignada y `time` restante. |
| `Queue<Customer>` | Cola de espera de una ventanilla. |
| `BankSimulationStep` | Estado de las colas en un instante. |
| `BankSimulationResult` | Resultado completo: llegadas, atendidos y línea de tiempo. |

La función `bestWindow` elige la cola más corta. Si hay empate, mantiene la primera mejor encontrada. Esta decisión es simple, determinista y fácil de 
defender: reduce la congestión local inmediata. No garantiza una política óptima global, porque no considera tiempos de servicio restantes ni distribución
futura de llegadas, pero sí es razonable para una simulación básica.

La función `simulate(nWin, servTime, seed)` recibe el número de ventanillas, la duración de la simulación y una semilla aleatoria. 
La semilla permite reproducir experimentos: con los mismos parámetros y la misma semilla, se obtiene la misma secuencia pseudoaleatoria de llegadas y tiempos
de servicio. Esto es importante para comparar resultados de forma controlada.

En cada instante `now` ocurre lo siguiente:

1. Se decide aleatoriamente si llega un cliente.
2. Si llega, se le asigna un tiempo de servicio aleatorio.
3. Se elige la cola más corta.
4. El cliente se encola en esa ventanilla.
5. Cada ventanilla atiende una unidad de tiempo al cliente del frente.
6. Si un cliente termina, se desencola.
7. Se guarda una fotografía de las colas en la línea de tiempo.

La cola es adecuada porque la atención de una ventanilla sigue la regla FIFO: el cliente que lleva más tiempo esperando en esa ventanilla debe ser atendido antes que los que llegaron después. 
Una pila sería conceptualmente incorrecta porque atendería primero al cliente más reciente, generando un comportamiento injusto para quienes esperan desde antes.

La simulación no resuelve un problema en el mismo sentido que N-Reinas o laberinto. En N-Reinas se busca una configuración válida, en laberinto se busca un camino. En banco, se reproduce la evolución de un sistema bajo reglas dadas. 
Por eso la salida no es solo "éxito" o "fracaso", sino una línea de tiempo, conteos de llegadas, conteos de atendidos y tamaños de colas.

#### 15. Organización del código de Semana 4

La carpeta de Semana 4 está organizada como un módulo autocontenido. Usa estilo `header-only`, `namespace ods` y evita depender internamente de las implementaciones concretas de semanas anteriores. Esto facilita compilar la semana por separado o integrarla a la librería completa.

Los componentes principales son:

| Archivo | Función principal |
|---|---|
| `Stack.h` | Implementa una pila LIFO usando `std::vector`. |
| `Queue.h` | Implementa una cola FIFO usando `std::deque`. |
| `BaseConversion.h` | Conversión de base recursiva e iterativa. |
| `Parentheses.h` | Verificación recursiva e iterativa de paréntesis. |
| `OperatorPriority.h` | Tabla de precedencia entre operadores. |
| `ExpressionEvaluator.h` | Evaluación de expresiones y generación de RPN. |
| `Queen.h` | Representación de una reina y conflicto. |
| `NQueens.h` | Backtracking iterativo para N-Reinas. |
| `Maze.h` | Laberinto, celdas, estados, direcciones y búsqueda. |
| `BankSimulation.h` | Simulación bancaria con múltiples colas. |
| `Capitulo4.h` | Header agregador de toda la semana. |

El archivo `Capitulo4.h` incluye todos los componentes principales. Esto permite que una demo o prueba incluya un solo archivo para acceder al conjunto de la semana. Las demos se dividen por tema: pila/cola, conversión de base, paréntesis/RPN, N-Reinas, laberinto, banco y panorama general. 
Las pruebas públicas verifican comportamiento esperado, las pruebas internas agregan cobertura y casos más exigentes.

#### 16. Relación entre documento, código y actividad

El documento de Deng proporciona el marco conceptual: define los ADT, explica las propiedades `LIFO` y `FIFO`, introduce la pila de llamadas, contrasta 
recursión con estructuras explícitas, presenta aplicaciones de pila y cola, y desarrolla problemas clásicos como paréntesis, expresiones, N-Reinas, laberinto
y banco.

El código de Semana 4 convierte esas ideas en implementaciones concretas. Algunas implementaciones son directas, como `Stack` y `Queue`. 
Otras son algorítmicas, como `ExpressionEvaluator`, `NQueens` y `Maze`. Otras son experimentales o de simulación, como `BankSimulation`. 
El objetivo no es solo que el código compile, sino que cada archivo permita defender un concepto.

La actividad de Semana 4 pide precisamente esa defensa. No basta con ejecutar demostraciones o pasar pruebas.
Hay que explicar qué guarda cada estructura auxiliar, por qué esa información es suficiente, qué invariante se conserva, qué diferencia hay entre
recursivo e iterativo, y cómo las decisiones de diseño cambian el comportamiento observable. Por ejemplo:

| Tema | Pregunta conceptual clave |
|---|---|
| Conversión de base | ¿Por qué los residuos deben invertirse? |
| Paréntesis | ¿Por qué el cierre debe compararse con la última apertura pendiente? |
| Expresiones | ¿Por qué hacen falta dos pilas? |
| N-Reinas | ¿Qué representa la pila de solución parcial? |
| Laberinto | ¿Por qué se necesitan marcas además de la pila? |
| Banco | ¿Por qué una cola modela mejor la atención que una pila? |

#### 17. Comparación de complejidades

Una síntesis de complejidades ayuda a ordenar los temas:

| Componente | Operación o problema | Tiempo | Espacio auxiliar | Comentario |
|---|---:|---:|---:|---|
| `Stack` | `push`, `pop`, `top` | `O(1)` amortizado | `O(n)` total | Basado en vector dinámico. |
| `Queue` | `enqueue`, `dequeue`, `front` | `O(1)` esperado | `O(n)` total | Basado en `std::deque`. |
| Conversión de base | Convertir `n` a base `b` | `O(log_b n)` | `O(log_b n)` | Un elemento por dígito. |
| Paréntesis iterativo | Verificar cadena | `O(n)` | `O(d)` | `d` es profundidad máxima. |
| Paréntesis recursivo | Verificar cadena | Hasta `O(n^2)` | `O(d)` call stack | Menos general para varios tipos. |
| Evaluación infija | Evaluar y generar RPN | `O(n)` | `O(n)` | Dos pilas. |
| Evaluación RPN | Evaluar posfija | `O(n)` | `O(n)` | Una pila de operandos. |
| N-Reinas | Buscar soluciones | Exponencial | `O(n)` para solución parcial | Backtracking con poda. |
| Laberinto | Buscar camino DFS | `O(RC)` | `O(RC)` | No garantiza camino mínimo. |
| Banco | Simular `T` instantes y `W` ventanillas | `O(TW + llegadas·W)` aprox. | Según colas | Depende de política de asignación. |

La tabla muestra que la complejidad no depende solo de la estructura, sino también del problema. `Stack` y `Queue` tienen operaciones básicas simples, pero 
cuando se usan como herramientas algorítmicas pueden participar en problemas lineales, exponenciales o de simulación.

#### 18. Invariantes importantes

Un invariante es una propiedad que debe mantenerse durante todo el algoritmo. En Semana 4 aparecen muchos invariantes útiles:

| Algoritmo | Invariante principal |
|---|---|
| Pila | El tope siempre es el último elemento insertado no eliminado. |
| Cola | El frente siempre es el elemento más antiguo no atendido. |
| Conversión de base | La pila contiene dígitos calculados que todavía deben invertirse. |
| Paréntesis | La pila contiene aperturas vistas y aún no cerradas. |
| Evaluación infija | `opnd` contiene valores listos, `optr` contiene operadores pendientes ordenados por precedencia. |
| RPN | Antes de un operador válido, sus operandos están en la cima de la pila. |
| N-Reinas | La pila `solution` contiene reinas no conflictivas, una por fila ya procesada. |
| Laberinto | La pila `path` contiene una ruta válida desde el inicio hasta la celda actual. |
| Banco | Cada cola de ventanilla mantiene orden FIFO de clientes asignados. |

Estos invariantes son la base de la correctitud. Las pruebas pueden mostrar que ciertos casos funcionan, pero los invariantes explican por qué el 
algoritmo funciona en general.


#### 19. Diferencia entre resolver y simular

La semana también permite distinguir dos tipos de tareas algorítmicas. En problemas como paréntesis, evaluación de expresiones, N-Reinas o laberinto, el algoritmo busca producir una respuesta: verdadero/falso, valor numérico, configuración válida o camino. 
Hay una condición de éxito clara. El estado auxiliar existe para llegar a esa respuesta.

En problemas como la simulación bancaria, el objetivo no es encontrar una solución única, sino observar la evolución de un sistema bajo reglas definidas. 
La salida relevante puede ser una línea de tiempo, número de clientes atendidos, congestión promedio o tamaño final de las colas.
Aquí la cola no "resuelve" el banco, sino que modela una política de atención.

Esta diferencia es importante para la defensa de la actividad. En un problema de búsqueda se habla de completitud, poda, solución parcial y retroceso. 
En una simulación se habla de estado, transición, parámetros, aleatoriedad, reproducibilidad y métricas observables.

#### 20. Conclusión general

La Semana 4 muestra que las estructuras de datos más simples pueden tener un alcance algorítmico muy amplio. Una pila restringe las operaciones a un extremo y por eso implementa `LIFO`, una cola separa inserción y eliminación en extremos opuestos y por eso implementa `FIFO`. 
Estas reglas parecen pequeñas, pero determinan cómo se recuerda el pasado y cómo se decide el siguiente paso.

La pila aparece cuando el problema exige volver sobre lo último que se hizo: llamadas recursivas, cierres de paréntesis, operadores pendientes, operandos recientes, decisiones de backtracking y rutas parciales. 
La cola aparece cuando el problema exige respetar llegada, turno o reparto: clientes, procesos, ventanillas y asignación cíclica.

El documento de Deng aporta la explicación conceptual y los ejemplos clásicos. El código de Semana 4 implementa esas ideas en C++ moderno y las organiza  en componentes reutilizables. 
La actividad pide cerrar el ciclo: ejecutar, observar, comparar, justificar y defender. La comprensión completa no consiste solo en saber 
usar `push` o `enqueue`, sino en reconocer cuándo el estado pendiente de un problema tiene naturaleza `LIFO` o `FIFO`, y cómo esa elección afecta la
correctitud, la eficiencia y el comportamiento observable del algoritmo.
