### Lectura18: Lower bound para ordenamiento por comparación

#### Problema

Queremos ordenar `n` elementos distintos usando únicamente comparaciones entre pares. Una comparación solo puede producir información binaria del tipo:

```txt
a < b
a >= b
```

Por eso, cualquier algoritmo de comparación puede representarse como un árbol binario de decisión.

#### Árbol de decisión

Cada nodo interno representa una comparación. Cada rama representa el resultado de esa comparación. Cada hoja representa una conclusión posible del algoritmo.

Para que el algoritmo sea correcto, debe distinguir todas las permutaciones posibles de los `n` elementos.

La cantidad de permutaciones posibles es:

```txt
n!
```

Por tanto, el árbol debe tener al menos `n!` hojas.

#### Altura mínima

Un árbol binario de altura `h` tiene a lo más:

```txt
2^h
```

hojas. Entonces debe cumplirse:

```txt
2^h >= n!
```

Aplicando logaritmo base 2:

```txt
h >= log2(n!)
```

Como `log2(n!) = Omega(n log n)`, cualquier algoritmo basado únicamente en comparaciones requiere `Omega(n log n)` comparaciones en algún caso.

#### Consecuencia

MergeSort y HeapSort son asintóticamente óptimos en el modelo de comparación porque alcanzan `O(n log n)` y ningún algoritmo de comparación puede mejorar ese orden asintótico en el caso general.

#### Por qué counting sort no contradice la cota

Counting sort no solo compara elementos. Usa el valor de una clave para indexar un arreglo de frecuencias. Ese acceso a memoria entrega más estructura que una comparación binaria. Por eso puede lograr `O(n + k)` cuando las claves están en un rango pequeño.

#### Por qué radix sort no contradice la cota

Radix sort procesa dígitos. Si hay `d` dígitos y base `b`, puede ordenar en `O(d(n + b))`, siempre que cada pasada sea estable. Tampoco pertenece al modelo puro de comparación.

#### Pregunta de reflexión

Si un algoritmo usa comparaciones y además usa las claves como índices, ¿sigue siendo un algoritmo de comparación puro? Justifica tu respuesta con un ejemplo.
