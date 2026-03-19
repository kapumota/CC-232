#include "mini_bench.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <list>
#include <numeric>
#include <random>
#include <vector>

namespace {

volatile std::int64_t sink = 0;

std::int64_t sum_vector_sequential(const std::vector<int>& values) {
    std::int64_t total = 0;
    for (const int value : values) {
        total += value;
    }
    return total;
}

std::int64_t sum_vector_random_access(const std::vector<int>& values, const std::vector<std::size_t>& order) {
    std::int64_t total = 0;
    for (const std::size_t index : order) {
        total += values[index];
    }
    return total;
}

std::int64_t sum_list(const std::list<int>& values) {
    std::int64_t total = 0;
    for (const int value : values) {
        total += value;
    }
    return total;
}

}  // namespace

int main() {
    constexpr std::size_t n = 2000000;
    constexpr int trials = 5;

    std::vector<int> values(n);
    std::iota(values.begin(), values.end(), 1);

    std::vector<std::size_t> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::mt19937 rng(232);
    std::shuffle(order.begin(), order.end(), rng);

    std::list<int> linked(values.begin(), values.end());

    const double avg_vector_seq = cc232::bench::average_us(trials, [&] {
        sink = sum_vector_sequential(values);
    });

    const double avg_vector_random = cc232::bench::average_us(trials, [&] {
        sink = sum_vector_random_access(values, order);
    });

    const double avg_list = cc232::bench::average_us(trials, [&] {
        sink = sum_list(linked);
    });

    cc232::bench::print_header("Benchmark inicial: conceptos basicos de cache/localidad", n, trials);
    cc232::bench::print_result("recorrido secuencial de vector", avg_vector_seq);
    cc232::bench::print_result("acceso aleatorio en vector", avg_vector_random);
    cc232::bench::print_result("recorrido de std::list", avg_list);
    return 0;
}