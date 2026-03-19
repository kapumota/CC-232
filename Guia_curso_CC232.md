###  Guía de configuración del entorno de desarrollo para CC232

#### Introducción

El curso se puede trabajar con `g++` en Windows usando **MSYS2 UCRT64** porque permite enseñar en el orden correcto: primero **algoritmo y estructura de datos**, luego **correctitud**, después **medición**, y finalmente **optimizaciones del compilador**. 

VS Code permite definir perfiles de terminal por `path` y `args`, elegir un perfil por defecto desde configuración o con **Terminal: Select Default Profile**  y MSYS2 documenta una configuración específica para usar UCRT64 dentro de VS Code. 

CMake, por su parte, es un generador de sistemas de build y su flujo recomendado por línea de comandos es configurar con `cmake -B build` y luego compilar con `cmake --build build`; además, CMake considera mala práctica hacer builds “in-source”. ([Visual Studio Code][1])

#### 1. Preparar el entorno en Windows con MSYS2 UCRT64

MSYS2 tiene varios entornos; **UCRT64** es uno de ellos y se activa mediante la variable `MSYSTEM=UCRT64`. En ese entorno, la toolchain es GCC y el `PATH` de la sesión prioriza `/ucrt64/bin`, por lo que `g++`, `cmake` y demás herramientas salen del entorno correcto. ([MSYS2][2])

Si todavía no tienes instalados compilador y CMake dentro de UCRT64, en la terminal **MSYS2 UCRT64** puedes instalar ambos paquetes así; los nombres de paquete oficiales existen en el repositorio `ucrt64` de MSYS2. ([MSYS2 Packages][3])

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake
```

Para comprobar que realmente estás en UCRT64:

```bash
echo $MSYSTEM
which g++
which cmake
g++ --version
cmake --version
```

Deberías ver `UCRT64` y rutas bajo `/ucrt64/bin`. Eso confirma que la shell está usando la toolchain esperada. ([MSYS2][2])


#### 2. Agregar MSYS2 UCRT64 como terminal en VS Code

La forma más limpia en Windows es **agregar un perfil de terminal** en `settings.json`. VS Code documenta que los perfiles de terminal son configuraciones por plataforma con `path`, `args` y otras opciones; además, puedes elegir el perfil por defecto con `terminal.integrated.defaultProfile.windows` o con el comando **Terminal: Select Default Profile**. 

MSYS2 documenta específicamente para VS Code el uso de `cmd.exe` más `C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64`. ([Visual Studio Code][1])

##### Pasos

1. Abre **VS Code**.
2. Pulsa `Ctrl+Shift+P`.
3. Escribe `Preferences: Open User Settings (JSON)`.
4. Fusiona esta configuración dentro de tu `settings.json`.

##### Configuración recomendada para Windows

```json
{
    "git.openRepositoryInParentFolders": "never",
    "terminal.integrated.profiles.windows": {
        "Git Bash": {
            "path": "C:\\Program Files\\Git\\bin\\bash.exe"
        },
        "MSYS2 UCRT64": {
            "path": "cmd.exe",
            "args": [
                "/c",
                "C:\\msys64\\msys2_shell.cmd -defterm -here -no-start -ucrt64"
            ],
            "icon": "terminal-bash"
        },
        "PowerShell": {
            "source": "PowerShell"
        },
        "Command Prompt": {
            "path": [
                "${env:windir}\\Sysnative\\cmd.exe",
                "${env:windir}\\System32\\cmd.exe"
            ]
        }
    },
    "terminal.integrated.defaultProfile.windows": "MSYS2 UCRT64",
    "makefile.configureOnOpen": true,
    "workbench.colorTheme": "Visual Studio Light",
    "python.createEnvironment.trigger": "off",
    "editor.unicodeHighlight.nonBasicASCII": false,
    "terminal.integrated.defaultProfile.linux": "bash",
    "go.toolsManagement.autoUpdate": true,
    "cmake.additionalCompilerSearchDirs": [
        "C:/msys64/mingw32/bin",
        "C:/msys64/mingw64/bin",
        "C:/msys64/clang32/bin",
        "C:/msys64/clang64/bin",
        "C:/msys64/clangarm64/bin",
        "C:/msys64/ucrt64/bin"
    ]
}
```

##### Nota importante

Tienes que **fusionarlo dentro del mismo bloque** `terminal.integrated.profiles.windows`. No puedes repetir esa clave dos veces al mismo nivel en JSON. 

VS Code usa un único objeto de perfiles por plataforma. ([Visual Studio Code][1])

##### Cómo verificar que quedó bien

Abre una terminal nueva en VS Code, elige **MSYS2 UCRT64** y ejecuta:

```bash
echo $MSYSTEM
which g++
which cmake
g++ --version
cmake --version
```

Si sale `UCRT64` y rutas como `/ucrt64/bin/g++`, quedó bien configurado. Eso es exactamente lo que se espera del entorno UCRT64 documentado por MSYS2. 
([MSYS2][2])

#### 3. Compilar con `g++`

Cuando el programa es un solo archivo, `g++` es la forma más directa. En UCRT64 basta abrir esa terminal y compilar desde la carpeta del archivo. 
Como el entorno ya viene configurado en la shell, `g++` usará la toolchain correcta. CMake documenta justamente que, cuando se usan generadores de línea de comandos, la shell debe tener el entorno del compilador ya configurado,  ese es 
precisamente el papel de abrir la shell UCRT64. ([CMake][4])

##### Compilación básica

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o stl_demo.exe
./stl_demo.exe --light
```

#### Build de depuración

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o stl_demo_debug.exe
./stl_demo_debug.exe --light
```

##### Build con sanitizers

```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o stl_demo_asan.exe
./stl_demo_asan.exe --light
```

##### Compilar varios archivos

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp modulo.cpp util.cpp -o app.exe
./app.exe
```

##### Generar objetos y luego enlazar

```bash
g++ -std=c++17 -O2 -c main.cpp -o main.o
g++ -std=c++17 -O2 -c modulo.cpp -o modulo.o
g++ main.o modulo.o -o app.exe
```

`g++` te conviene cuando quieres algo simple, rápido y transparente: un archivo, pocos módulos o una demostración de clase.

#### 4. Usar CMake

CMake no reemplaza al compilador; **genera el sistema de build** y luego usa la toolchain disponible. La documentación oficial lo describe como la interfaz de línea de comandos del generador de buildsystem, y su tutorial muestra el flujo estándar: configurar con `cmake -B build` y compilar con `cmake --build build`. 

También insiste en que es mejor mantener los archivos generados fuera del árbol fuente. ([CMake][4])

##### Estructura mínima

```text
mi_proyecto/
├─ CMakeLists.txt
├─ src/
│  └─ main.cpp
└─ tests/
   └─ test_demo.cpp
```

##### `src/main.cpp`

```cpp
#include <iostream>

int main() {
    std::cout << "Hola desde CMake + g++\n";
    return 0;
}
```

##### `CMakeLists.txt` mínimo

```cmake
cmake_minimum_required(VERSION 3.20)
project(MiProyecto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mi_app src/main.cpp)
```

##### Configurar y compilar

```bash
cmake -S . -B build
cmake --build build
```

##### Ejecutar

En shells tipo UCRT64 normalmente será:

```bash
./build/mi_app.exe
```

CMake advierte que el ejecutable puede quedar directamente en `build/` o, con generadores multiconfiguración como Visual Studio, dentro de subcarpetas como `build/Debug`. ([CMake][5])

##### Build Debug y Release

En generadores de línea de comandos habituales en UCRT64, suele usarse `CMAKE_BUILD_TYPE`:

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug

cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
```

##### Elegir compilador explícitamente

Si quieres forzar GCC del entorno UCRT64:

```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
cmake --build build
```

##### Limpiar desde cero

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```


#### 5. Agregar pruebas con CMake

CMake separa claramente compilación y pruebas. Su documentación señala que `ctest` es la interfaz de línea de comandos para testing asociada a CMake. ([CMake][4])

##### Ejemplo mínimo

##### `src/suma.cpp`

```cpp
int suma(int a, int b) {
    return a + b;
}
```

##### `src/suma.h`

```cpp
#pragma once
int suma(int a, int b);
```

##### `tests/test_suma.cpp`

```cpp
#include "../src/suma.h"
#include <iostream>

int main() {
    if (suma(2, 3) != 5) {
        std::cerr << "Fallo: suma(2,3) != 5\n";
        return 1;
    }
    std::cout << "OK\n";
    return 0;
}
```

##### `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.20)
project(TestDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(core src/suma.cpp)
target_include_directories(core PUBLIC src)

add_executable(test_suma tests/test_suma.cpp)
target_link_libraries(test_suma PRIVATE core)

add_test(NAME test_suma COMMAND test_suma)
```

##### Configurar, compilar y correr tests

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Esto ya te deja un proyecto base para explicar correctitud, regresión y automatización de pruebas.


#### 6. Cuándo usar `g++` y cuándo usar CMake

Usa **`g++` directo** cuando:

* tienes un archivo o una demo pequeña
* quieres enseñar flags del compilador
* quieres algo rápido de probar en clase.

Usa **CMake** cuando:

* hay varios `.cpp` y `.h`
* quieres separar Debug y Release
* quieres agregar tests con `ctest`
* necesitas un proyecto más limpio y escalable.

La diferencia práctica es sencilla: `g++` te sirve para compilar y CMake te sirve para **organizar el build**.


#### 7.  Comandos mínimos útiles en VS Code + UCRT64

Cuando ya tengas el perfil configurado, esto suele bastar para una clase:

##### Archivo único con `g++`

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o demo.exe
./demo.exe --light
```

##### Proyecto CMake

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

##### Verificación de entorno

```bash
echo $MSYSTEM
which g++
which cmake
g++ --version
cmake --version
```

#### Revisiones obligatorias

* [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)
* [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites)
* [CMake projects in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)

[1]: https://code.visualstudio.com/docs/terminal/profiles "Terminal Profiles"
[2]: https://www.msys2.org/docs/environments/ "Environments - MSYS2"
[3]: https://packages.msys2.org/package/mingw-w64-ucrt-x86_64-gcc "Package: mingw-w64-ucrt-x86_64-gcc"
[4]: https://cmake.org/cmake/help/latest/manual/cmake.1.html "cmake(1) - CMake 4.3.0 Documentation"
[5]: https://cmake.org/cmake/help/latest/guide/tutorial/Getting%20Started%20with%20CMake.html "Step 1: Getting Started with CMake - CMake 4.3.0 Documentation"
[6]: https://code.visualstudio.com/docs/terminal/profiles "Terminal Profiles"
