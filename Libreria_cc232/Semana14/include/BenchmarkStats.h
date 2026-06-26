#pragma once

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

namespace cc232::week14 {

struct BenchmarkStats {
    std::string name;
    std::vector<std::int64_t> samplesNanoseconds;
    std::size_t operations = 0;

    void addSample(std::int64_t ns) {
        if (ns < 0) {
            throw std::invalid_argument("El tiempo no puede ser negativo");
        }
        samplesNanoseconds.push_back(ns);
    }

    std::int64_t totalNanoseconds() const {
        return std::accumulate(samplesNanoseconds.begin(), samplesNanoseconds.end(), std::int64_t{0});
    }

    double averageNanoseconds() const {
        if (samplesNanoseconds.empty()) {
            return 0.0;
        }
        return static_cast<double>(totalNanoseconds()) / static_cast<double>(samplesNanoseconds.size());
    }

    std::int64_t minNanoseconds() const {
        if (samplesNanoseconds.empty()) {
            return 0;
        }
        return *std::min_element(samplesNanoseconds.begin(), samplesNanoseconds.end());
    }

    std::int64_t maxNanoseconds() const {
        if (samplesNanoseconds.empty()) {
            return 0;
        }
        return *std::max_element(samplesNanoseconds.begin(), samplesNanoseconds.end());
    }
};

inline bool fasterThan(const BenchmarkStats& a, const BenchmarkStats& b) {
    return a.averageNanoseconds() < b.averageNanoseconds();
}

}  // namespace cc232::week14
