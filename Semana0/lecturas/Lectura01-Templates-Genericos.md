### Lectura01: Templates y programación genérica en C++17

#### Propósito

Esta lectura introduce el uso mínimo de templates que se necesita en CC232 antes de implementar estructuras de datos genéricas.

En las semanas posteriores se usarán clases como arreglos, pilas, colas, heaps, árboles, tablas hash, tries, segment trees y B-Trees. Muchas de esas estructuras no deben depender de un único tipo de dato. Por eso se necesita programación genérica.

#### Resultado esperado

Al terminar esta lectura, el estudiante debe poder:

1. Escribir una función genérica simple.
2. Escribir una clase genérica simple.
3. Usar `const T&` para evitar copias innecesarias.
4. Distinguir entre devolver por valor y devolver por referencia.
5. Implementar `operator[]` en versión mutable y constante.
6. Comprender por qué los templates suelen definirse en headers.
7. Leer errores de compilación básicos asociados a templates.

#### Función genérica mínima

Una función genérica permite reutilizar la misma lógica con distintos tipos.

```cpp
namespace cc232 {

template <typename T>
T maximum(const T& a, const T& b) {
    return (b < a) ? a : b;
}

} // namespace cc232
```

Esta función requiere que el tipo `T` pueda compararse con el operador `<`.

Ejemplos válidos:

```cpp
auto x = cc232::maximum(3, 7);
auto y = cc232::maximum(std::string{"beta"}, std::string{"alfa"});
```

#### Por qué se usa `const T&`

El parámetro `const T&` evita copiar objetos grandes y al mismo tiempo impide que la función modifique los argumentos.

```cpp
template <typename T>
void printReadonly(const T& value);
```

Esta forma será frecuente en el curso cuando se lean claves, valores, nodos o contenedores sin modificarlos.

#### Clase genérica mínima

Una clase genérica permite construir una estructura de datos independiente del tipo almacenado.

```cpp
template <typename T>
class SimpleArray {
public:
    explicit SimpleArray(std::size_t n);
    std::size_t size() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
};
```

La misma clase puede usarse con enteros, cadenas o tipos definidos por el estudiante.

```cpp
cc232::SimpleArray<int> numbers(3);
cc232::SimpleArray<std::string> words(2);
```

#### Versión mutable y versión constante de `operator[]`

Una estructura debe permitir escritura cuando el objeto es mutable:

```cpp
numbers[0] = 10;
```

También debe permitir lectura cuando el objeto es constante:

```cpp
const auto& readonly = numbers;
auto first = readonly[0];
```

Por eso se implementan dos versiones:

```cpp
T& operator[](std::size_t index);
const T& operator[](std::size_t index) const;
```

#### Regla práctica para CC232

En este curso se usará esta regla:

1. Si una función no debe modificar un objeto, recibe `const T&`.
2. Si una función debe modificar un objeto, recibe `T&`.
3. Si una función necesita quedarse con una copia, recibe o construye una copia de forma explícita.
4. Si una estructura es genérica, su implementación principal vive en el header.

#### Errores comunes

#### Separar templates en `.cpp` sin instanciación

Si se define una función template solo en un archivo `.cpp`, el compilador puede no encontrar la implementación para el tipo usado.

Para Semana0 se usará una regla simple:

```txt
Los templates se definen en archivos `.h`.
```

#### Copiar más de lo necesario

Esta firma puede copiar objetos grandes:

```cpp
template <typename T>
T maximum(T a, T b);
```

Esta firma evita esas copias de entrada:

```cpp
template <typename T>
T maximum(const T& a, const T& b);
```

#### Devolver referencia a un objeto local

Esto es incorrecto:

```cpp
template <typename T>
const T& badFunction() {
    T value{};
    return value;
}
```

`value` deja de existir cuando la función termina. En estructuras de datos, este error puede producir comportamiento indefinido.

#### Relación con las siguientes semanas

Los templates preparan directamente para:

1. Arreglos dinámicos genéricos.
2. Pilas y colas genéricas.
3. Heaps genéricos.
4. Árboles binarios parametrizados por tipo.
5. Tablas hash parametrizadas por clave y valor.
6. Segment trees parametrizados por operación.
7. B-Trees parametrizados por clave.

#### Ejercicio de lectura

Antes de pasar a la actividad, responde:

1. ¿Por qué `const T&` evita copias innecesarias?
2. ¿Por qué una estructura genérica debe tener `operator[]` constante y no constante?
3. ¿Qué requisito debe cumplir un tipo `T` para usarse con `maximum`?
4. ¿Por qué los templates suelen definirse en headers?.
