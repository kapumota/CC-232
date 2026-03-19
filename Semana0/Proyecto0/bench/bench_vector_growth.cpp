#include "mini_bench.h"

#include <cstddef>
#include <numeric>
#include <vector>

namespace {

void push_without_reserve(std::size_t n) {
    std::vector<int> values;
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i));
    }
    volatile long long checksum = std::accumulate(values.begin(), values.end(), 0LL);
    (void)checksum;
}

void push_with_reserve(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i));
    }
    volatile long long checksum = std::accumulate(values.begin(), values.end(), 0LL);
    (void)checksum;
}

}  // namespace

int main() {
    constexpr std::size_t n = 300000;
    constexpr int trials = 5;

    const double avg_no_reserve = cc232::bench::average_us(trials, [=] { push_without_reserve(n); });
    const double avg_reserve = cc232::bench::average_us(trials, [=] { push_with_reserve(n); });

    cc232::bench::print_header("Benchmark inicial: crecimiento de vector", n, trials);
    cc232::bench::print_result("push_back sin reserve", avg_no_reserve);
    cc232::bench::print_result("push_back con reserve", avg_reserve);
    return 0;
}