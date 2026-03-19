#ifndef CC232_WARMUP_VECTOR_H
#define CC232_WARMUP_VECTOR_H

#include <cstddef>
#include <vector>

namespace cc232 {

// Lee sin copiar: útil para APIs de solo lectura.
int sum_readonly(const std::vector<int>& values);

// Modifica el vector original mediante referencia no-const.
void append_in_place(std::vector<int>& values, int x);

// Recibe una copia y devuelve la copia modificada.
// El vector original del llamador no cambia.
std::vector<int> appended_copy(std::vector<int> values, int x);

std::size_t count_greater_than(const std::vector<int>& values, int limit);
bool is_strictly_increasing(const std::vector<int>& values);

}  // namespace cc232

#endif
