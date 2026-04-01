### Rubrica - Semana 3

#### 1. Comprensión conceptual
- **Logrado:** define con claridad listas enlazadas, acceso por rango frente a acceso por posición o enlace, diferencias entre `SLList`, `DLList` y `SEList`, papel de los nodos, punteros y centinelas, y la relación entre estas estructuras y los adaptadores construidos en la semana.
- **En proceso:** reconoce las ideas principales de la semana, pero todavía mezcla algunos conceptos, por ejemplo entre lista simplemente enlazada y doblemente enlazada, o entre acceso por índice y acceso por referencia a nodo.
- **Por reforzar:** no logra distinguir las ideas centrales de la semana ni explicar cómo se relacionan las distintas estructuras enlazadas.

#### 2. Sustentación de correctitud
- **Logrado:** justifica por qué las operaciones funcionan, explicando mantenimiento de enlaces, invariantes de `head`, `tail`, `dummy` y `n`, casos borde en listas vacías o de un solo elemento, inversión de listas, búsqueda de nodos por posición, reconexión local en inserciones y borrados, transferencia entre pilas en `MinQueue`, rebalanceo en `MinDeque` y redistribución de bloques en `SEList`.
- **En proceso:** da intuiciones correctas sobre el funcionamiento de las operaciones, pero con una justificación parcial, incompleta o poco precisa en los detalles de punteros, invariantes o casos especiales.
- **Por reforzar:** afirma que la estructura "funciona" sin sustento conceptual, sin explicar el papel de los enlaces ni por qué las operaciones preservan la representación.

#### 3. Análisis de eficiencia
- **Logrado:** identifica y compara correctamente costos temporales y espaciales usando lenguaje asintótico básico, incluyendo `O(1)` en operaciones locales sobre nodos ya ubicados, `O(n)` en recorridos lineales, `O(1 + min{i, n-i})` en `DLList`, `O(1 + min{i, n-i}/b)` en `SEList`, y el compromiso entre acceso, actualización local y uso de memoria en estructuras enlazadas y por bloques.
- **En proceso:** reconoce qué operaciones son más rápidas o más lentas, pero confunde algunos costos, omite supuestos importantes o no justifica bien la diferencia entre localizar un nodo y modificarlo.
- **Por reforzar:** no logra relacionar las operaciones con su costo o presenta explicaciones incorrectas sobre eficiencia en listas enlazadas, adaptadores o estructuras con mínimo.

#### 4. Aplicación al código de la semana
- **Logrado:** conecta la teoría con implementaciones concretas de la semana, explicando con precisión decisiones de diseño y operaciones en `SLList`, `DLList`, `SEList`, `LinkedStack`, `LinkedQueue`, `LinkedDeque`, `MinStack`, `MinQueue`, `MinDeque`, `DengList` y `MorinDengBridge`.
- **En proceso:** menciona ejemplos del código de la semana y reconoce algunas decisiones de implementación, pero con análisis parcial, superficial o poco preciso en los detalles del código.
- **Por reforzar:** no logra vincular la teoría con las implementaciones ni con los ejercicios y pruebas trabajadas en Semana 3.

#### 5. Claridad de comunicación
- **Logrado:** responde de forma ordenada, precisa y entendible, usando ejemplos, comparaciones, diagramas mentales o trazas breves cuando ayudan a sustentar la respuesta.
- **En proceso:** comunica la idea general, pero con desorden, ambigüedad o poca precisión en algunos términos.
- **Por reforzar:** da respuestas vagas, contradictorias o difíciles de seguir.

#### Orientación para la sustentación de semana 3
Se espera especialmente que el estudiante pueda:
- Explicar por qué una lista enlazada reemplaza acceso por rango por acceso por posición o enlace
- Justificar por qué `SLList` implementa bien pila y cola, pero no un deque completo
- Sustentar el papel de `head`, `tail` y `n`, así como los casos borde al insertar o eliminar en listas vacías o de un solo elemento
- Explicar por qué el nodo centinela `dummy` simplifica `DLList` y cómo permite insertar o eliminar sin casos especiales adicionales
- Describir cómo `getNode(i)` decide recorrer desde el inicio o desde el final y justificar el costo `O(1 + min{i, n-i})`
- Explicar cómo `SEList` organiza elementos por bloques, qué hace `getLocation(i)` y cómo intervienen `spread()` y `gather()`
- Relacionar el tamaño de bloque `b` con el compromiso entre eficiencia espacial y tiempo de acceso o actualización
- Explicar cómo `LinkedStack`, `LinkedQueue` y `LinkedDeque` reutilizan listas enlazadas como estructuras base
- Justificar cómo `MinStack`, `MinQueue` y `MinDeque` mantienen consultas de mínimo eficientes
- Sustentar el propósito de `DengList` y del puente `MorinDengBridge`, incluyendo el beneficio y el costo de convertir estructuras antes de aplicar operaciones como `sort`, `dedup` o `reverse`.
