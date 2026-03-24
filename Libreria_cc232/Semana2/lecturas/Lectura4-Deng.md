### Estructura, gestión dinámica y operaciones del vector

**Resumen.** El **vector** es una estructura lineal cuya importancia radica en que combina **orden secuencial**, **acceso directo** y una implementación eficiente sobre **memoria contigua**. A diferencia del arreglo entendido solo como mecanismo de almacenamiento, el vector introduce una formulación más abstracta basada en el **rango** de los elementos y en una **interfaz ADT** que separa el comportamiento observable de los detalles internos de implementación. Sobre esta base, el vector soporta operaciones de **lectura**, **actualización**, **inserción**, **eliminación**, **búsqueda**, **recorrido**, **mezcla aleatoria** y **eliminación de duplicados**, manteniendo un equilibrio entre eficiencia temporal y uso razonable del espacio. Su estudio es particularmente relevante porque muestra cómo una estructura aparentemente elemental obliga a tratar cuestiones centrales del diseño algorítmico: **manejo de memoria**, **copias profundas**, **invariantes de correctitud**, **costos de desplazamiento** y **análisis amortizado**.   

**Palabras clave:** **vector**, **arreglo lineal**, **rango**, **memoria contigua**, **ADT**, **capacidad**, **tamaño**, **factor de carga**, **expansión**, **reducción**, **análisis amortizado**, **búsqueda secuencial**, **inserción**, **eliminación**, **deduplicación**, **recorrido**.

### Introducción

Las **estructuras de datos lineales** organizan sus elementos bajo una relación de precedencia y sucesión. En ese marco, la forma más básica de organización es la **secuencia**, donde cada elemento ocupa una posición definida dentro de un orden total. El **vector** pertenece a esta familia, pero presenta una propiedad distintiva: la disposición lógica de los elementos coincide con su disposición física en memoria. Esta coincidencia explica por qué el vector ofrece **acceso por posición en tiempo constante** y por qué se convierte en una herramienta central para representar colecciones indexadas. 

La relevancia del vector no proviene solo de su frecuencia de uso, sino de su valor formativo. En él convergen varios temas fundamentales: la diferencia entre **interfaz** e **implementación**, la conveniencia de modelar operaciones como parte de un **tipo de dato abstracto**, la necesidad de administrar memoria dinámica sin perder eficiencia y la utilidad del **análisis amortizado** para describir con mayor fidelidad el comportamiento real de una secuencia de operaciones. Por ello, estudiar el vector equivale también a estudiar una metodología general para razonar sobre estructuras de datos.  

### Desarrollo

#### 1. Del arreglo lineal al concepto de vector

El punto de partida es el **arreglo lineal**, entendido como un bloque **contiguo** de memoria en el que se almacenan elementos ordenados. Cada elemento queda asociado a un **índice**, y la dirección física de la celda correspondiente puede calcularse a partir de una dirección base y un desplazamiento proporcional al índice. Si el bloque comienza en la dirección **A** y cada elemento ocupa **s** unidades de memoria, entonces la dirección del elemento de índice **i** queda determinada por la expresión **A + i × s**. Esta relación lineal entre índice y dirección física es la base del **acceso directo**. 

Sobre esa base aparece el **vector** como una generalización conceptual. Ya no se trata solo de un bloque de memoria indexado, sino de una secuencia cuyos elementos se distinguen por su **rango**, es decir, por el número de predecesores que poseen dentro de la colección. Si un elemento tiene exactamente **r** predecesores, entonces su rango es **r**, y dicho rango permite identificarlo de manera unívoca. Esta idea introduce una formulación más abstracta: el acceso deja de entenderse únicamente como acceso por índice de arreglo y pasa a interpretarse como **acceso por rango**, que constituye la característica definitoria del vector. 

La abstracción del vector tiene una consecuencia decisiva: libera a la estructura de depender exclusivamente de tipos básicos. Mediante **plantillas**, el vector puede almacenar enteros, flotantes, caracteres, vectores anidados u objetos más complejos. Así, el vector se transforma en una estructura genérica y reutilizable, lo que fortalece tanto su valor práctico como su elegancia teórica. 

#### 2. El vector como tipo de dato abstracto

En sentido estricto, un **ADT** no se define por la forma exacta en que ocupa memoria, sino por las operaciones que promete ofrecer. En el caso del vector, esas operaciones incluyen **size()**, **get(r)**, **put(r, e)**, **insert(r, e)**, **remove(r)**, **find(e)**, **search(e)**, **sort()**, **deduplicate()**, **uniquify()**, **unsort()** y **traverse()**. Algunas de ellas son generales para cualquier vector, otras dependen de condiciones adicionales, como el hecho de que el vector esté **ordenado**. Esta organización muestra que el vector no es solo un contenedor pasivo, sino una estructura dotada de un repertorio algorítmico propio.  

La separación entre **interfaz externa** e **implementación interna** es uno de los principios más relevantes del diseño. Dos estructuras con detalles internos distintos pueden ser intercambiables si respetan el mismo contrato de operaciones. En el caso del vector, ello permite cambiar políticas de almacenamiento, copia o redimensionamiento sin alterar el código que lo utiliza. Desde una perspectiva académica, esta separación también facilita el análisis comparativo de complejidad, porque la misma interfaz puede sostener implementaciones con rendimientos diferentes. 

Otra observación importante es que el conjunto de operaciones disponibles depende de la información estructural presente. Un vector **no ordenado** admite de manera natural la búsqueda secuencial mediante **find()**; un vector **ordenado**, en cambio, habilita búsquedas más eficientes mediante **search()** y procedimientos más económicos para eliminar duplicados. Esto evidencia que el orden no es un simple atributo adicional, sino una propiedad que modifica radicalmente el repertorio de algoritmos aplicables.  

#### 3. Representación interna y ciclo de vida del vector

La implementación clásica del vector se apoya en tres campos privados: **_elem**, que apunta al arreglo interno, **_size**, que registra el número real de elementos válidos y **_capacity**, que indica cuántas celdas han sido reservadas. Esta tripleta resume la lógica completa del almacenamiento. El punto esencial es que **tamaño** y **capacidad** no son lo mismo: el tamaño pertenece al plano lógico de la secuencia; la capacidad, al plano físico de la memoria disponible. La posibilidad de que la capacidad exceda al tamaño es precisamente lo que hace viable el crecimiento dinámico sin reasignaciones en cada inserción. 

El ciclo de vida del vector incluye **constructores**, **copia**, **asignación** y **destrucción**. El constructor por defecto reserva un área inicial y establece **_size = 0**. Los constructores por copia y por intervalo delegan el trabajo a una rutina como **copyFrom()**, que crea un nuevo arreglo y copia en orden los elementos del intervalo solicitado. Este detalle no es meramente técnico: garantiza que el nuevo vector posea su propia área de almacenamiento. Sin esa política de **copia profunda**, dos vectores podrían compartir el mismo bloque interno y producir errores al modificarse o destruirse. 

La sobrecarga del operador de asignación responde exactamente a esa necesidad. Dado que el vector administra memoria dinámica, la asignación por defecto del lenguaje no basta para clonar correctamente el área de datos. El procedimiento correcto exige liberar el contenido anterior, reservar espacio nuevo y copiar los elementos del vector origen. El **destructor**, por su parte, libera el arreglo interno y devuelve esos recursos al sistema. En consecuencia, el vector no solo organiza datos; también asume responsabilidad explícita sobre la propiedad y liberación de la memoria que utiliza. 

#### 4. Gestión dinámica del espacio

##### 4.1. Limitaciones de la gestión estática

Si la capacidad del arreglo interno fuera fija durante toda la vida de la estructura, aparecerían dos problemas opuestos. El primero es el **overflow**, que surge cuando las inserciones consumen toda la capacidad disponible. El segundo es el **desperdicio de espacio**, que aparece cuando se reserva demasiada memoria por anticipado. Para medir esta relación se utiliza el **factor de carga**, definido como el cociente entre **_size** y **_capacity**. Un factor demasiado alto anuncia saturación, uno demasiado bajo revela mala eficiencia espacial. La solución no consiste en adivinar mejor cuánta memoria reservar al inicio, sino en adoptar una política de **gestión dinámica**. 

##### 4.2. Expansión del vector

La expansión parte de una dificultad material: un arreglo exige **memoria contigua**, de modo que no puede suponerse que habrá espacio libre inmediatamente después del bloque actual. Por ello, cuando la capacidad se agota, la solución correcta es reservar un nuevo arreglo con mayor tamaño, copiar allí todos los elementos, liberar el arreglo antiguo y continuar la operación pendiente. La implementación estándar de **expand()** sigue exactamente esa secuencia y fija como política que la nueva capacidad sea el **doble** de la anterior. 

```text
procedimiento EXPANDIR()
    si tamaño < capacidad entonces
        retornar
    fin si

    si capacidad < capacidad_mínima entonces
        capacidad <- capacidad_mínima
    fin si

    viejo <- arreglo
    capacidad <- 2 × capacidad
    arreglo <- nuevo bloque de tamaño capacidad

    para i desde 0 hasta tamaño - 1 hacer
        arreglo[i] <- viejo[i]
    fin para

    liberar viejo
fin procedimiento
```

Lo importante aquí no es solo que el vector "crezca", sino cómo lo hace. Si se añadiera una pequeña cantidad fija de celdas cada vez, habría que expandir con demasiada frecuencia. La duplicación reduce drásticamente el número de reasignaciones y hace posible una eficiencia mucho mayor a lo largo de secuencias largas de inserciones.  

##### 4.3. Sentido del análisis amortizado

A primera vista, la expansión parece costosa, porque copiar todos los elementos puede requerir tiempo **O(n)**. Sin embargo, esa observación es incompleta. Si la capacidad se duplica, después de pagar el costo de una expansión deben ocurrir muchas inserciones adicionales antes de que otra expansión vuelva a ser necesaria. El análisis correcto no se concentra en una operación aislada, sino en la suma total del trabajo a lo largo de una secuencia amplia de operaciones. 

Ese es precisamente el papel del **análisis amortizado**. En lugar de calcular una esperanza probabilística sobre entradas hipotéticas, se toma una secuencia real de operaciones y se distribuye el costo total entre todas ellas. Bajo la estrategia de duplicación, el costo acumulado de las expansiones forma una suma geométrica dominada por la última capacidad alcanzada, por lo que el tiempo total invertido en expandir a lo largo de **n** inserciones es **Θ(n)**. Al repartirlo entre esas operaciones, el costo amortizado por inserción resulta **O(1)**. Así se explica por qué un vector dinámico puede ser, en términos prácticos, tan eficiente como una estructura aparentemente más simple.  

##### 4.4. Reducción y underflow

El problema opuesto ocurre cuando el tamaño real del vector cae muy por debajo de su capacidad. En ese escenario, el factor de carga se aproxima a cero y aparece el **underflow** en sentido espacial: no hay error de ejecución, pero sí una utilización pobre de la memoria reservada. Para enfrentar esta situación se introduce **shrink()**, que reduce la capacidad cuando la ocupación cae por debajo de un umbral, ilustrado con el **25%**. La reducción reserva un nuevo arreglo más pequeño, copia los elementos válidos y libera el bloque antiguo. 

La reducción, igual que la expansión, cuesta tiempo lineal cuando ocurre. No obstante, si se activa con prudencia, también conserva costo amortizado **O(1)** por operación distribuida. Esto muestra que la gestión dinámica del vector no persigue únicamente crecer sin límites, sino mantener un equilibrio razonable entre **disponibilidad temporal** y **eficiencia espacial**. 

#### 5. Operaciones fundamentales del vector

##### 5.1. Acceso directo y notación natural

Aunque el ADT define operaciones como **get()** y **put()**, la forma más natural de acceso sigue siendo la notación de índice. Por ello, la sobrecarga del operador **[ ]** permite recuperar el estilo de acceso del arreglo sin renunciar a la encapsulación del vector. Esta decisión mejora la claridad del código y acerca la implementación al modelo mental intuitivo del programador. 

##### 5.2. Mezcla aleatoria

La operación **unsort()** o mezcla aleatoria recorre el vector desde el final hacia el inicio e intercambia cada posición con una posición aleatoria dentro del prefijo aún no fijado. El procedimiento es relevante no solo como técnica de programación, sino también como ejemplo de uso del vector en **pruebas de software**, **simulación** y validación experimental. Su complejidad es lineal y su diseño depende del acceso directo a cualquier posición. 

##### 5.3. Búsqueda en vectores no ordenados

En un vector **no ordenado** no existe información estructural que permita descartar regiones del arreglo. Por ello, la búsqueda de un elemento igual a **e** se realiza mediante **búsqueda secuencial**. El algoritmo recorre el vector de atrás hacia adelante para devolver, en caso de éxito, la coincidencia de **mayor rango**. Si no encuentra el elemento, devuelve **-1**. Esta convención simplifica el manejo de errores y fija una semántica precisa para la operación. 

La complejidad de la búsqueda secuencial depende de la instancia concreta. En el mejor caso, el elemento aparece al final del intervalo considerado y el tiempo es **O(1)**. En el peor caso, el elemento no aparece o se encuentra al inicio, y el tiempo asciende a **O(n)**. Por ello, se trata de un algoritmo **sensible a la entrada**. 

##### 5.4. Inserción y costo de preservar contigüidad

La operación **insert(r, e)** muestra con especial claridad la lógica del vector. Primero debe llamarse a **expand()** para evitar overflow. Después, todos los elementos del sufijo **[r, _size)** deben desplazarse una posición hacia la derecha, y ese desplazamiento debe realizarse de atrás hacia adelante para no sobrescribir datos todavía no copiados. Solo cuando la posición **r** queda libre puede almacenarse el nuevo elemento y actualizarse el tamaño. 

```text
función INSERTAR(V, r, e)
    EXPANDIR(V)

    para i desde tamaño(V) hasta r + 1 hacer
        V[i] <- V[i - 1]
    fin para

    V[r] <- e
    tamaño(V) <- tamaño(V) + 1
    retornar r
fin función
```

El costo depende de la posición elegida. Insertar al final cuesta **O(1)** en el mejor caso, insertar al inicio obliga a mover todos los elementos existentes y cuesta **O(n)**. En términos más precisos, el tiempo es proporcional a la longitud del sufijo desplazado. De esta manera, el vector exhibe una de sus tensiones estructurales básicas: su gran eficiencia para acceder se compensa con un costo elevado cuando debe preservar contigüidad frente a modificaciones internas. 

##### 5.5. Eliminación por intervalo y caso particular

La eliminación también revela una decisión de diseño importante. Podría pensarse que eliminar un intervalo consiste en eliminar uno por uno sus elementos, pero eso repetiría innecesariamente desplazamientos sobre el mismo sufijo. La estrategia correcta es la inversa: implementar la eliminación de un elemento como caso particular de la eliminación por intervalo **[lo, hi)**. Así, el sufijo restante se desplaza una sola vez hacia la izquierda para ocupar el espacio liberado.  

La complejidad de **remove(lo, hi)** depende únicamente del número de elementos que quedan después del intervalo eliminado. Por ello, eliminar cerca del final es barato, mientras que eliminar cerca del inicio puede ser costoso. La eliminación individual **remove(r)** hereda exactamente esta lógica, con complejidad **O(_size - r)**. Tras actualizar el tamaño, la estructura puede llamar a **shrink()** si la utilización de memoria cae por debajo del umbral definido. 

##### 5.6. Eliminación de duplicados e invariantes

La operación **deduplicate()** para vectores no ordenados recorre la secuencia de izquierda a derecha y, para cada elemento actual, pregunta si ya existe una copia en el prefijo anterior. Si no existe, avanza; si existe, elimina la ocurrencia actual. La corrección del algoritmo se apoya en un **invariante** muy preciso: antes de cada iteración, todos los elementos del prefijo ya procesado son mutuamente distintos. Este detalle es relevante porque muestra que la validez del algoritmo no se basa solo en intuición operativa, sino en una propiedad lógica que se conserva durante toda la ejecución. 

El costo total de **deduplicate()** en un vector no ordenado es **O(n²)**. Cada iteración puede requerir una búsqueda lineal en el prefijo y, además, una eliminación cuyo costo depende del número de sucesores. Así, el algoritmo es correcto pero no especialmente eficiente, lo que anticipa por qué el ordenamiento previo puede abrir la puerta a estrategias más económicas. 

##### 5.7. Recorrido uniforme

La operación **traverse()** permite tratar el vector como un todo y aplicar una misma transformación o acción sobre cada uno de sus elementos. Puede implementarse mediante **punteros a función** o mediante **objetos función**. Más allá del detalle técnico, esta operación refleja una idea de alto nivel: el vector no solo sirve para almacenar, sino también para soportar procesamiento uniforme sobre una colección completa. Su costo es lineal respecto del tamaño de la secuencia, multiplicado por el costo de la operación aplicada a cada elemento. 

#### 6. Evaluación conceptual de la estructura

La principal fortaleza del vector reside en la conjunción de **acceso directo**, **simplicidad estructural** y una política de redimensionamiento que, gracias al **análisis amortizado**, permite un comportamiento eficiente en secuencias largas de operaciones. Esta combinación lo vuelve especialmente útil cuando predominan las lecturas, las actualizaciones por posición y las inserciones al final. Además, su formulación como **ADT** lo convierte en una pieza central para construir estructuras más complejas.  

Su límite aparece cuando las operaciones modificadoras se concentran en posiciones iniciales o intermedias. En esos casos, la necesidad de conservar la **contigüidad física** obliga a desplazar un gran número de elementos, y el costo crece linealmente. En otras palabras, el vector obtiene eficiencia de acceso precisamente porque paga con reacomodos costosos cuando debe preservar su forma interna. Esa tensión resume, en buena medida, toda su teoría de complejidad. 

### Conclusión

El **vector** es una estructura de datos lineal cuya riqueza excede con mucho la idea elemental de "arreglo con índice". En él convergen la noción de **rango**, la separación entre **interfaz** e **implementación**, la distinción entre **tamaño** y **capacidad**, el uso disciplinado de **memoria dinámica** y el valor del **análisis amortizado** para explicar costos reales de operación. Esta combinación lo convierte en una estructura fundamental tanto para la práctica de la programación como para la formación rigurosa en algoritmos.  

Desde una perspectiva académica, el vector enseña una lección particularmente importante: la eficiencia nunca depende de un solo aspecto. Surge de la interacción entre representación, contrato de operaciones, propiedades invariantes y estrategia de crecimiento o reducción del almacenamiento. Por eso, comprender el vector no equivale solo a dominar una estructura específica, sino a comprender un modelo general para pensar con precisión sobre **datos**, **operaciones** y **complejidad**.   


