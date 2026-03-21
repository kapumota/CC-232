### Medición y análisis de la complejidad algorítmica

**Resumen.** La evaluación rigurosa de un algoritmo exige criterios que permitan medir su rendimiento con independencia del entorno concreto de ejecución. En ese marco, la **complejidad temporal** y la **complejidad espacial** constituyen los dos ejes centrales del análisis. La primera estudia cómo crece el tiempo de ejecución cuando aumenta el tamaño de la entrada; la segunda examina el crecimiento del espacio de memoria auxiliar requerido por el procedimiento. Para formalizar estas nociones se emplea el **análisis asintótico**, sustentado en la **notación O grande**, la **notación Ω grande** y la **notación Θ grande**, que permiten describir cotas superiores, inferiores y ajustadas del comportamiento de un algoritmo. A partir de estas herramientas es posible clasificar los algoritmos en niveles típicos, como **tiempo constante**, **tiempo logarítmico**, **tiempo lineal**, **tiempo polinómico** y **tiempo exponencial**. Esta clasificación no solo ordena los métodos según su crecimiento, sino que permite distinguir entre algoritmos tratables y problemas de **intratabilidad**. Además, el análisis depende críticamente de cómo se define el **tamaño de entrada**, puesto que una misma tarea puede parecer eficiente o ineficiente según el criterio descriptivo adoptado. 

**Palabras clave:** **complejidad temporal**, **complejidad espacial**, **análisis asintótico**, **notación O grande**, **notación Ω grande**, **notación Θ grande**, **operaciones básicas**, **peor caso**, **mejor caso**, **caso promedio**, **tiempo constante**, **tiempo logarítmico**, **tiempo lineal**, **tiempo polinómico**, **tiempo exponencial**, **jerarquía de complejidades**, **tamaño de entrada**. 

#### Introducción

El estudio de la eficiencia computacional requiere un criterio estable para comparar algoritmos. El tiempo real de ejecución depende de factores variables, como la plataforma de hardware, el sistema operativo o el momento en que se ejecuta el programa. Por ello, el análisis algorítmico se separa de la medición empírica inmediata y adopta una perspectiva abstracta. En lugar de preguntar cuántos segundos tarda una implementación concreta, se pregunta cómo evoluciona el costo computacional cuando el problema crece. Este cambio de enfoque convierte la eficiencia en una propiedad estructural del algoritmo y no en una simple observación circunstancial. Así, el análisis de complejidad busca describir la relación entre el procedimiento, el crecimiento de la entrada y los recursos necesarios para resolverla. 

#### Complejidad temporal

La **complejidad temporal** se expresa mediante una función $T(n)$, donde $n$ representa el tamaño de la entrada. Esta función describe el costo del algoritmo cuando resuelve instancias de ese tamaño.
Sin embargo, un mismo valor de $n$ no determina una única entrada posible. En un problema de ordenamiento, por ejemplo, pueden existir muchas configuraciones distintas para un arreglo de longitud $n$, y cada una puede inducir tiempos de ejecución diferentes. 
Para resolver esta ambigüedad, se adopta con frecuencia una perspectiva conservadora: se toma como $T(n)$ el mayor tiempo requerido entre todas las entradas de tamaño $n$. 
De esta forma, el análisis se orienta al comportamiento más exigente del algoritmo y proporciona una medida robusta de su costo. 

La cuestión fundamental puede formularse de la siguiente manera:

$$
\text{¿Cómo crece } T(n) \text{ cuando aumenta } n?
$$

Esta pregunta resume el propósito del análisis de complejidad: no interesa tanto el tiempo absoluto como la ley de crecimiento del algoritmo frente al aumento del problema. 

#### Análisis asintótico y notaciones fundamentales

El **análisis asintótico** estudia el comportamiento de un algoritmo cuando el tamaño de la entrada se vuelve grande. En lugar de concentrarse en diferencias menores o en constantes de implementación, este enfoque observa la tendencia dominante del crecimiento. Tal perspectiva resulta especialmente útil porque dos algoritmos pueden comportarse de modo similar en instancias pequeñas y, sin embargo, diferir enormemente cuando el problema escala. 

La herramienta más habitual es la **notación O grande**, que proporciona una cota superior asintótica. Si existen una constante positiva $c$ y una función $f(n)$ tales que, para $n$ suficientemente grande, se cumple:

$$
T(n) \leq c \cdot f(n),
$$

entonces se escribe:

$$
T(n) = O(f(n)).
$$

La utilidad de esta notación radica en que permite ignorar constantes multiplicativas positivas y términos de menor grado. Así, por ejemplo,

$$
O(2n^2 - 4n + 2) = O(n^2).
$$

Con ello, el análisis se concentra en la tendencia principal del crecimiento. 

La **notación Ω grande** cumple la función opuesta: establece una cota inferior asintótica. Si existen una constante positiva $c$ y una función $g(n)$ tales que, para $n$ suficientemente grande,

$$
T(n) \geq c \cdot g(n),
$$

entonces:

$$
T(n) = \Omega(g(n)).
$$

Esta notación se emplea para describir el mínimo orden de crecimiento que el algoritmo no puede evitar. 

Por su parte, la **notación Θ grande** expresa una cota ajustada. Si existen constantes positivas $c_1$ y $c_2$ y una función $h(n)$ tales que, para $n$ suficientemente grande,

$$
c_1 h(n) \leq T(n) \leq c_2 h(n),
$$

entonces:

$$
T(n) = \Theta(h(n)).
$$

En ese caso, puede afirmarse que el crecimiento del algoritmo pertenece exactamente a ese orden asintótico. 

#### Medición mediante operaciones básicas

Para evitar la dependencia de factores externos, la **complejidad temporal** se interpreta como el número total de **operaciones básicas** ejecutadas por el algoritmo. 
En modelos abstractos como la **máquina de Turing** o la **máquina de acceso aleatorio**, operaciones como comparar, sumar, desplazar bits o realizar saltos condicionales se consideran de costo constante. 
De este modo, el tiempo total se obtiene contando cuántas veces se ejecutan dichas operaciones. 

Un ejemplo relevante es el **ordenamiento burbuja**. En este procedimiento, cada pasada del bucle interno realiza comparaciones entre pares adyacentes y, cuando es necesario, efectúa intercambios. 
Si en cada pasada se procesan $n-1$ pares, entonces el número de operaciones básicas por pasada queda acotado por:

$$
2(n-1).
$$

Como el bucle externo puede ejecutar a lo sumo $n-1$ pasadas, el total queda limitado por:

$$
2(n-1)^2.
$$

En consecuencia, la complejidad del algoritmo satisface:

$$
T(n) = O(2(n-1)^2) = O(n^2).
$$

Este ejemplo muestra cómo una descripción operativa puede transformarse en una caracterización matemática precisa del costo algorítmico. 

#### Peor caso, mejor caso y caso promedio

La **notación O grande** suele expresar una visión conservadora del comportamiento de un algoritmo. Cuando se afirma que un procedimiento tiene complejidad $O(n^2)$, ello significa que no excede asintóticamente ese orden para entradas de tamaño $n$. 
No obstante, ese límite no impide que existan entradas más favorables. Por ello, el análisis distingue entre **peor caso**, **mejor caso** y **caso promedio**. 

El **peor caso** se refiere a la instancia que exige el mayor tiempo entre todas las de tamaño $n$. El **mejor caso** alude a la más favorable. El **caso promedio** intenta estimar el tiempo medio considerando una distribución sobre las entradas posibles. 
Aunque estas tres nociones son útiles, la más empleada es la del **peor caso**, porque ofrece una garantía robusta y resulta decisiva en entornos donde la confiabilidad temporal no admite márgenes de error. 

#### Complejidad espacial

Además del tiempo, el análisis considera la memoria utilizada durante la ejecución. La **complejidad espacial** mide precisamente el crecimiento de ese consumo. 
En general, no se incluye el espacio de la entrada original, ya que este suele ser el mismo para cualquier algoritmo que resuelva el mismo problema. 
En cambio, sí se cuentan las estructuras auxiliares, los índices, los buffers y otros recursos adicionales. 

En muchos casos, la **complejidad temporal** constituye una cota superior natural para la **complejidad espacial**, porque cada **operación básica** ocupa a lo sumo espacio constante. 
Sin embargo, esto no elimina la necesidad de estudiar explícitamente la memoria cuando el tamaño de la entrada es muy grande o cuando la eficiencia espacial es un requisito crítico. 

### Niveles típicos de complejidad

Una vez introducidas las herramientas del análisis asintótico, es posible distinguir varios niveles típicos de crecimiento. Esta clasificación permite identificar, de forma cualitativa, qué algoritmos permanecen viables cuando el problema crece y cuáles se vuelven rápidamente impracticables. 

#### Tiempo constante

Un algoritmo de **tiempo constante** satisface:

$$
T(n) = O(1).
$$

Su costo no depende del tamaño de la entrada. Un ejemplo consiste en seleccionar un elemento no extremo de un conjunto tomando tres valores, comparándolos e imprimiendo el del medio.
El número de lecturas y comparaciones permanece fijo, por lo que el costo es constante. Este tipo de algoritmos representa el ideal máximo de eficiencia. 

#### Tiempo logarítmico

Un algoritmo de **tiempo logarítmico** cumple:

$$
T(n) = O(\log n).
$$

Aparece cuando el problema se reduce de forma drástica en cada iteración. El ejemplo clásico es contar los bits `1` en la representación binaria de un entero, desplazándolo a la derecha una posición en cada paso. Como cada desplazamiento reduce el valor al menos a la mitad, el número de iteraciones es:

$$
1 + \lfloor \log_2 n \rfloor.
$$

Por tanto, el algoritmo tiene complejidad logarítmica. 

#### Tiempo lineal

Un algoritmo de **tiempo lineal** satisface:

$$
T(n) = O(n).
$$

Esto ocurre cuando cada unidad de entrada debe procesarse una sola vez. El ejemplo típico es sumar los elementos de un arreglo. Si cada iteración realiza una suma de costo constante y se repite $n$ veces, el costo total crece proporcionalmente al tamaño de la entrada. 

#### Tiempo polinómico

Se habla de **tiempo polinómico** cuando:

$$
T(n) = O(p(n)),
$$

donde $p(n)$ es un polinomio. En esta categoría se ubican, por ejemplo, los algoritmos cuadráticos como el **ordenamiento burbuja**, cuya complejidad es $O(n^2)$. 
Dentro de la teoría de la complejidad, el **tiempo polinómico** suele considerarse el umbral de los problemas tratables, es decir, aquellos que pueden resolverse eficientemente en términos asintóticos. 

#### Tiempo exponencial

Un algoritmo de **tiempo exponencial** cumple una relación del tipo:

$$
T(n) = O(a^n), \qquad a > 1.
$$

El ejemplo presentado consiste en calcular $2^n$ mediante duplicaciones sucesivas. Si el tamaño de entrada se mide por el número de bits del exponente,

$$
r = 1 + \lfloor \log_2 n \rfloor,
$$

entonces el costo queda expresado como:

$$
T(r) = O(2^r).
$$

Este resultado muestra que la eficiencia depende críticamente de cómo se define el tamaño del problema. Además, los algoritmos exponenciales se vuelven rápidamente inviablescuando la entrada crece, razón por la cual se los asocia con problemas de **intratabilidad**. 

#### Jerarquía de complejidades

La **jerarquía de complejidades** organiza los algoritmos según la rapidez con la que crece su costo. Entre los niveles más frecuentes se encuentran:

$$
O(1),\ O(\log n),\ O(n),\ O(n\log n),\ O(n^2),\ O(n^3),\ O(2^n).
$$

Esta jerarquía permite ver que las diferencias entre clases bajas y medias pueden ser importantes, pero la ruptura decisiva aparece entre las clases polinómicas y las exponenciales. 
Desde una perspectiva asintótica, esa frontera separa los algoritmos razonablemente utilizables de aquellos cuyo costo se dispara con rapidez intolerable. 

#### Tamaño de entrada y pseudo-complejidad

Todo análisis de complejidad depende del **tamaño de entrada** elegido. Este aspecto es fundamental, porque una misma tarea puede recibir caracterizaciones muy distintas según  el criterio empleado. 
En el ejemplo del conteo de bits, si se toma como tamaño de entrada el valor numérico $n$, la complejidad parece ser $O(\log n)$. Pero si se adopta como tamaño el número de bits necesarios para representar ese valor,

$$
r = 1 + \lfloor \log_2 n \rfloor,
$$

entonces la complejidad pasa a ser:

$$
O(r).
$$

De forma análoga, el algoritmo iterativo para calcular $2^n$ parece lineal si se mide respecto del valor $n$, pero exponencial si se mide respecto de $r$, que es la longitud binaria del dato. Por ello, el criterio más riguroso consiste en definir el **tamaño de entrada** como la cantidad de espacio necesaria para describir la instancia.
Bajo esta perspectiva aparecen nociones como **complejidad pseudo-logarítmica** y **complejidad pseudo-lineal**, que advierten sobre análisis aparentemente correctos, pero construidos sobre una medida inadecuada del problema. 

#### Conclusión

La medición de la complejidad constituye una herramienta esencial para comprender la eficiencia de los algoritmos.  La **complejidad temporal** describe el crecimiento del tiempo de ejecución, la **complejidad espacial** permite evaluar el uso de memoria y el **análisis asintótico** proporciona el lenguaje formal para comparar algoritmos más allá de las particularidades de implementación. 
Las notaciones **O grande**, **Ω grande** y **Θ grande** permiten expresar límites superiores, inferiores y ajustados del crecimiento computacional. 
Gracias a estas herramientas, los algoritmos pueden ubicarse dentro de una **jerarquía de complejidades** que distingue entre comportamientos tratables e instancias de **intratabilidad**. Finalmente, el estudio del **tamaño de entrada** muestra que la eficiencia no es una propiedad absoluta, sino una relación entre el algoritmo, la representación del problema y el criterio de medición adoptado. Comprender esa relación es indispensable para evaluar de forma rigurosa cualquier procedimiento computacional. 

