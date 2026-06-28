### Lectura00: C++17 minimo para CC232

#### Proposito

Esta lectura fija la base de C++17 que se usara durante el curso CC232.
La meta no es cubrir todo el lenguaje, sino dominar los conceptos necesarios
para implementar estructuras de datos de forma segura, legible y verificable.

Semana0 no adelanta listas, arboles, hashing ni grafos. Prepara al estudiante
para leer codigo modular, compilarlo, probarlo y razonar sobre copia, referencias,
mutabilidad y vida de objetos.

#### Resultado esperado

Al terminar esta lectura, el estudiante debe poder:

1. Elegir tipos adecuados para indices, tamanos y acumuladores.
2. Explicar la diferencia entre paso por valor, referencia y referencia const.
3. Usar `struct` y `class` con criterio.
4. Reconocer constructores y destructores.
5. Explicar RAII como regla de manejo de recursos.
6. Aplicar `const correctness` en funciones de solo lectura.
7. Distinguir copia superficial y copia profunda.
8. Leer errores comunes antes de implementar estructuras de datos.

#### Tipos basicos

C++ permite trabajar con tipos primitivos y tipos definidos por el programador.
En CC232 se usaran principalmente:

| Tipo | Uso frecuente |
|---|---|
| `int` | valores pequenos, claves enteras, contadores simples |
| `long long` | acumuladores que pueden crecer mucho |
| `bool` | respuestas logicas e invariantes |
| `char` | caracteres y alfabetos |
| `std::string` | cadenas de texto |
| `std::size_t` | tamanos e indices de contenedores |

#### `std::size_t`

`std::size_t` es el tipo que la biblioteca estandar usa para representar tamanos.
Por eso aparece en llamadas como `vector.size()` o `string.size()`.

Ejemplo:

```cpp
std::vector<int> values{1, 2, 3};
for (std::size_t i = 0; i < values.size(); ++i) {
    std::cout << values[i] << '\n';
}
```

Regla practica:

1. Usa `std::size_t` para recorrer indices de contenedores.
2. Usa `int` cuando el dominio del problema sea naturalmente entero con signo.
3. Evita mezclar indices con signo y sin signo sin revisar la condicion.

#### Paso por valor

En paso por valor, la funcion recibe una copia del argumento.
Modificar el parametro no cambia el objeto original.

```cpp
void addValue(std::vector<int> values, int x) {
    values.push_back(x);
}
```

Este estilo puede ser correcto cuando se necesita una copia local. Tambien puede
ser costoso si el objeto es grande.

#### Paso por referencia

En paso por referencia, la funcion recibe el objeto original.
Modificar el parametro cambia el objeto del llamador.

```cpp
void addInPlace(std::vector<int>& values, int x) {
    values.push_back(x);
}
```

Este estilo se usa cuando la funcion debe modificar la estructura.

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

Esta forma debe ser la primera opcion para funciones de solo lectura que reciben
objetos grandes.

#### `struct` frente a `class`

En C++, `struct` y `class` pueden tener datos y funciones. La diferencia inicial
es el nivel de acceso por defecto.

| Forma | Acceso por defecto | Uso recomendado en CC232 |
|---|---|---|
| `struct` | publico | datos simples, resultados, nodos internos pequenos |
| `class` | privado | estructuras con invariantes fuertes |

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
permiten dejar un objeto en un estado valido desde el inicio.

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

La palabra `explicit` evita conversiones automaticas no deseadas.

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
destruirlo. En CC232, esta idea evita fugas y estados invalidos.

Ejemplos de RAII en la biblioteca estandar:

| Tipo | Recurso administrado |
|---|---|
| `std::vector<T>` | memoria dinamica del arreglo interno |
| `std::string` | memoria de la cadena |
| `std::unique_ptr<T>` | propiedad unica de un objeto dinamico |
| `std::ifstream` | archivo abierto |

Regla practica:

1. Prefiere contenedores estandar antes que memoria manual.
2. Evita `new` y `delete` en codigo inicial del curso.
3. Usa objetos que limpian sus recursos al salir de alcance.

#### `const correctness`

Una funcion miembro que no modifica el objeto debe marcarse como `const`.

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
intencion.

#### Copia superficial

Una copia superficial comparte algun recurso entre dos objetos. Eso puede ser
correcto si se quiere compartir, pero puede ser peligroso si no se entiende la
propiedad del recurso.

En CC232, se evitara iniciar con punteros crudos para explicar propiedad. La idea
se demostrara con un objeto que comparte datos mediante `std::shared_ptr`.

#### Copia profunda

Una copia profunda duplica los datos. Despues de copiar, cambiar la copia no
modifica el original.

`std::vector<int>` realiza copia profunda de sus elementos:

```cpp
std::vector<int> a{1, 2, 3};
std::vector<int> b = a;
b.push_back(4);
```

Despues de ese codigo, `a` conserva tres elementos y `b` tiene cuatro.

#### Errores comunes

| Error | Consecuencia |
|---|---|
| Pasar vectores grandes por valor sin necesitar copia | costo innecesario |
| Olvidar `const` en funciones de solo lectura | API menos clara |
| Usar `int` para todos los indices | advertencias y errores con tamanos |
| Exponer todos los datos publicos en estructuras complejas | invariantes fragiles |
| Usar memoria manual antes de dominar RAII | fugas o doble liberacion |

#### Relacion con el resto del curso

Estos conceptos aparecen en casi todas las semanas:

| Concepto | Uso posterior |
|---|---|
| `std::size_t` | arreglos, heaps, tablas hash, segment trees |
| referencias const | busquedas y consultas sin copia |
| referencias no const | actualizaciones e inserciones |
| RAII | nodos, buffers, estructuras auxiliares |
| copia profunda | contenedores y pruebas |
| `class` con invariantes | estructuras balanceadas y arboles |

#### Ejercicios de lectura

1. Escribe una funcion que reciba `const std::vector<int>&` y devuelva el maximo.
2. Explica por que `std::vector<int> v` como parametro puede copiar muchos datos.
3. Muestra un caso donde una referencia no const sea necesaria.
4. Explica por que un metodo `size()` normalmente debe ser `const`.
5. Describe una diferencia entre copia superficial y copia profunda.
