#pragma once

#include <chrono>
#include <cstdint>
#include <utility>

namespace cc232::week14 {

class BenchmarkTimer {
public:
    template <class Func>
    static std::int64_t measureNanoseconds(Func&& func) {
        const auto start = std::chrono::steady_clock::now();
        std::forward<Func>(func)();
        const auto finish = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    }
};

}  // namespace cc232::week14
