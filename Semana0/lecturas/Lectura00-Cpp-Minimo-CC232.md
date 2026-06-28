### Lectura00: C++17 mínimo para CC232

#### Propósito

Esta lectura fija la base de C++17 que se usará durante el curso CC232.
La meta no es cubrir todo el lenguaje, sino dominar los conceptos necesarios
para implementar estructuras de datos de forma segura, legible y verificable.

Semana0 no adelanta listas, árboles, hashing ni grafos. Prepara al estudiante
para leer código modular, compilarlo, probarlo y razonar sobre copia, referencias,
mutabilidad y vida de objetos.

#### Resultado esperado

Al terminar esta lectura, el estudiante debe poder:

1. Elegir tipos adecuados para índices, tamaños y acumuladores.
2. Explicar la diferencia entre paso por valor, referencia y referencia const.
3. Usar `struct` y `class` con criterio.
4. Reconocer constructores y destructores.
5. Explicar RAII como regla de manejo de recursos.
6. Aplicar `const correctness` en funciones de solo lectura.
7. Distinguir copia superficial y copia profunda.
8. Leer errores comunes antes de implementar estructuras de datos.

#### Tipos básicos

C++ permite trabajar con tipos primitivos y tipos definidos por el programador.
En CC232 se usarán principalmente:

| Tipo          | Uso frecuente                                        |
| ------------- | ---------------------------------------------------- |
| `int`         | valores pequeños, claves enteras, contadores simples |
| `long long`   | acumuladores que pueden crecer mucho                 |
| `bool`        | respuestas lógicas e invariantes                     |
| `char`        | caracteres y alfabetos                               |
| `std::string` | cadenas de texto                                     |
| `std::size_t` | tamaños e índices de contenedores                    |

#### `std::size_t`

`std::size_t` es el tipo que la biblioteca estándar usa para representar tamaños.
Por eso aparece en llamadas como `vector.size()` o `string.size()`.

Ejemplo:

```cpp
std::vector<int> values{1, 2, 3};
for (std::size_t i = 0; i < values.size(); ++i) {
    std::cout << values[i] << '\n';
}
```

Regla práctica:

1. Usa `std::size_t` para recorrer índices de contenedores.
2. Usa `int` cuando el dominio del problema sea naturalmente entero con signo.
3. Evita mezclar índices con signo y sin signo sin revisar la condición.

#### Paso por valor

En paso por valor, la función recibe una copia del argumento.
Modificar el parámetro no cambia el objeto original.

```cpp
void addValue(std::vector<int> values, int x) {
    values.push_back(x);
}
```

Este estilo puede ser correcto cuando se necesita una copia local. También puede
ser costoso si el objeto es grande.

#### Paso por referencia

En paso por referencia, la función recibe el objeto original.
Modificar el parámetro cambia el objeto del llamador.

```cpp
void addInPlace(std::vector<int>& values, int x) {
    values.push_back(x);
}
```

Este estilo se usa cuando la función debe modificar la estructura.

#### Referencia const

Una referencia const evita copiar y protege contra modificaciones accidentales.

```cpp
int sumValues(const std::vector<int>& values) {
    int total = 0;
    for (int value : values) {
        total += value;
    }
    return total;
}
```

Esta forma debe ser la primera opción para funciones de solo lectura que reciben
objetos grandes.

#### `struct` frente a `class`

En C++, `struct` y `class` pueden tener datos y funciones. La diferencia inicial
es el nivel de acceso por defecto.

| Forma    | Acceso por defecto | Uso recomendado en CC232                           |
| -------- | ------------------ | -------------------------------------------------- |
| `struct` | público            | datos simples, resultados, nodos internos pequeños |
| `class`  | privado            | estructuras con invariantes fuertes                |

Ejemplo de `struct`:

```cpp
struct Summary {
    std::size_t count = 0;
    int minimum = 0;
    int maximum = 0;
};
```

Ejemplo de `class`:

```cpp
class Counter {
public:
    void increment() {
        ++value_;
    }

    int value() const {
        return value_;
    }

private:
    int value_ = 0;
};
```

#### Constructores

Un constructor inicializa un objeto. En estructuras de datos, los constructores
permiten dejar un objeto en un estado válido desde el inicio.

```cpp
class Buffer {
public:
    explicit Buffer(std::size_t capacity)
        : data_(capacity) {
    }

    std::size_t size() const {
        return data_.size();
    }

private:
    std::vector<int> data_;
};
```

La palabra `explicit` evita conversiones automáticas no deseadas.

#### Destructores

Un destructor se ejecuta cuando el objeto termina su vida. En C++ moderno,
normalmente no se debe escribir un destructor manual si los miembros ya manejan
sus recursos mediante RAII.

Ejemplo conceptual:

```cpp
class ScopeLogger {
public:
    ScopeLogger() {
        std::cout << "Inicio del objeto\n";
    }

    ~ScopeLogger() {
        std::cout << "Fin del objeto\n";
    }
};
```

#### RAII

RAII significa que un recurso se adquiere al construir un objeto y se libera al
destruirlo. En CC232, esta idea evita fugas y estados inválidos.

Ejemplos de RAII en la biblioteca estándar:

| Tipo                 | Recurso administrado                  |
| -------------------- | ------------------------------------- |
| `std::vector<T>`     | memoria dinámica del arreglo interno  |
| `std::string`        | memoria de la cadena                  |
| `std::unique_ptr<T>` | propiedad única de un objeto dinámico |
| `std::ifstream`      | archivo abierto                       |

Regla práctica:

1. Prefiere contenedores estándar antes que memoria manual.
2. Evita `new` y `delete` en código inicial del curso.
3. Usa objetos que limpian sus recursos al salir de alcance.

#### `const correctness`

Una función miembro que no modifica el objeto debe marcarse como `const`.

```cpp
class Bag {
public:
    std::size_t size() const {
        return size_;
    }

private:
    std::size_t size_ = 0;
};
```

Esto permite usar el objeto desde contextos de solo lectura y ayuda a documentar
intención.

#### Copia superficial

Una copia superficial comparte algún recurso entre dos objetos. Eso puede ser
correcto si se quiere compartir, pero puede ser peligroso si no se entiende la
propiedad del recurso.

En CC232, se evitará iniciar con punteros crudos para explicar propiedad. La idea
se demostrará con un objeto que comparte datos mediante `std::shared_ptr`.

#### Copia profunda

Una copia profunda duplica los datos. Después de copiar, cambiar la copia no
modifica el original.

`std::vector<int>` realiza copia profunda de sus elementos:

```cpp
std::vector<int> a{1, 2, 3};
std::vector<int> b = a;
b.push_back(4);
```

Después de ese código, `a` conserva tres elementos y `b` tiene cuatro.

#### Errores comunes

| Error                                                     | Consecuencia                       |
| --------------------------------------------------------- | ---------------------------------- |
| Pasar vectores grandes por valor sin necesitar copia      | costo innecesario                  |
| Olvidar `const` en funciones de solo lectura              | API menos clara                    |
| Usar `int` para todos los índices                         | advertencias y errores con tamaños |
| Exponer todos los datos públicos en estructuras complejas | invariantes frágiles               |
| Usar memoria manual antes de dominar RAII                 | fugas o doble liberación           |

#### Relación con el resto del curso

Estos conceptos aparecen en casi todas las semanas:

| Concepto                | Uso posterior                               |
| ----------------------- | ------------------------------------------- |
| `std::size_t`           | arreglos, heaps, tablas hash, segment trees |
| referencias const       | búsquedas y consultas sin copia             |
| referencias no const    | actualizaciones e inserciones               |
| RAII                    | nodos, buffers, estructuras auxiliares      |
| copia profunda          | contenedores y pruebas                      |
| `class` con invariantes | estructuras balanceadas y árboles           |

#### Ejercicios de lectura

1. Escribe una función que reciba `const std::vector<int>&` y devuelva el máximo.
2. Explica por qué `std::vector<int> v` como parámetro puede copiar muchos datos.
3. Muestra un caso donde una referencia no const sea necesaria.
4. Explica por qué un método `size()` normalmente debe ser `const`.
5. Describe una diferencia entre copia superficial y copia profunda.
