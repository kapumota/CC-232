#include "mini_test.h"
#include "simple_array.h"

#include <stdexcept>
#include <string>

namespace {

void testMaximumWithIntegers() {
    cc232::test::expect(cc232::maximum(3, 9) == 9, "maximum debe elegir el entero mayor");
    cc232::test::expect(cc232::maximum(-2, -5) == -2, "maximum debe funcionar con enteros negativos");
}

void testMaximumWithStrings() {
    const std::string a = "arbol";
    const std::string b = "grafo";
    cc232::test::expect(cc232::maximum(a, b) == "grafo", "maximum debe usar el orden del tipo string");
}

void testSimpleArrayBasicAccess() {
    cc232::SimpleArray<int> values(3);
    values[0] = 10;
    values[1] = 20;
    values[2] = 30;

    cc232::test::expect(values.size() == 3, "SimpleArray debe reportar su tamano");
    cc232::test::expect(!values.empty(), "SimpleArray con elementos no debe estar vacio");
    cc232::test::expect(values[1] == 20, "operator[] debe permitir lectura mutable");

    const auto& readonly = values;
    cc232::test::expect(readonly[2] == 30, "operator[] const debe permitir lectura");
}

void testSimpleArrayFillAndAt() {
    cc232::SimpleArray<std::string> words(2);
    words.fill("dato");

    cc232::test::expect(words.at(0) == "dato", "fill debe escribir la primera posicion");
    cc232::test::expect(words.at(1) == "dato", "fill debe escribir la segunda posicion");

    bool threw = false;
    try {
        (void)words.at(2);
    } catch (const std::out_of_range&) {
        threw = true;
    }

    cc232::test::expect(threw, "at debe lanzar excepcion cuando el indice esta fuera de rango");
}

void testSimpleArrayDeepCopy() {
    cc232::SimpleArray<int> original(2);
    original[0] = 4;
    original[1] = 8;

    cc232::SimpleArray<int> copy = original;
    copy[0] = 99;

    cc232::test::expect(original[0] == 4, "la copia no debe modificar el arreglo original");
    cc232::test::expect(copy[0] == 99, "la copia debe conservar su propio almacenamiento");
}

void testSimpleArrayCopyAssignment() {
    cc232::SimpleArray<int> left(1);
    left[0] = 5;

    cc232::SimpleArray<int> right(3);
    right[0] = 1;
    right[1] = 2;
    right[2] = 3;

    left = right;
    right[0] = 100;

    cc232::test::expect(left.size() == 3, "la asignacion debe copiar el tamano");
    cc232::test::expect(left[0] == 1, "la asignacion debe hacer copia profunda");
    cc232::test::expect(right[0] == 100, "el arreglo derecho debe seguir siendo modificable");
}

} // namespace

int main() {
    testMaximumWithIntegers();
    testMaximumWithStrings();
    testSimpleArrayBasicAccess();
    testSimpleArrayFillAndAt();
    testSimpleArrayDeepCopy();
    testSimpleArrayCopyAssignment();

    cc232::test::pass();
    return 0;
}
