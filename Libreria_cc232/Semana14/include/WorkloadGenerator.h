#pragma once

#include <algorithm>
#include <numeric>
#include <random>
#include <string>
#include <vector>

namespace cc232::week14 {

class WorkloadGenerator {
public:
    explicit WorkloadGenerator(unsigned seed = 23214) : rng_(seed) {}

    std::vector<int> randomIntegers(std::size_t n, int low = 0, int high = 1000000) {
        std::uniform_int_distribution<int> dist(low, high);
        std::vector<int> values(n);
        for (auto& value : values) {
            value = dist(rng_);
        }
        return values;
    }

    std::vector<int> sortedIntegers(std::size_t n) const {
        std::vector<int> values(n);
        std::iota(values.begin(), values.end(), 0);
        return values;
    }

    std::vector<int> reversedIntegers(std::size_t n) const {
        auto values = sortedIntegers(n);
        std::reverse(values.begin(), values.end());
        return values;
    }

    std::vector<int> repeatedIntegers(std::size_t n, int modulo = 16) const {
        std::vector<int> values(n);
        for (std::size_t i = 0; i < n; ++i) {
            values[i] = static_cast<int>(i % static_cast<std::size_t>(modulo));
        }
        return values;
    }

    std::vector<std::string> syntheticWords(std::size_t n) const {
        std::vector<std::string> words;
        words.reserve(n);
        const std::vector<std::string> roots = {"alg", "tree", "hash", "graph", "range", "text", "data"};
        for (std::size_t i = 0; i < n; ++i) {
            words.push_back(roots[i % roots.size()] + std::to_string(i));
        }
        return words;
    }

private:
    std::mt19937 rng_;
};

}  // namespace cc232::week14
