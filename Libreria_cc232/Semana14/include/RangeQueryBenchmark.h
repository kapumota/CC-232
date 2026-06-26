#pragma once

#include "BenchmarkStats.h"
#include "BenchmarkTimer.h"

#include <vector>

namespace cc232::week14 {

class RangeQueryBenchmark {
public:
    std::vector<BenchmarkStats> run(const std::vector<int>& values, int repetitions = 3) const {
        std::vector<BenchmarkStats> stats;
        stats.push_back(benchPrefixSums(values, repetitions));
        stats.push_back(benchNaive(values, repetitions));
        return stats;
    }

private:
    static BenchmarkStats benchPrefixSums(const std::vector<int>& values, int repetitions) {
        BenchmarkStats stats;
        stats.name = "prefix_sums";
        stats.operations = values.size();
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                std::vector<long long> prefix(values.size() + 1, 0);
                for (std::size_t i = 0; i < values.size(); ++i) {
                    prefix[i + 1] = prefix[i] + values[i];
                }
                volatile long long total = 0;
                for (std::size_t i = 0; i < values.size(); i += 7) {
                    const std::size_t j = std::min(values.size(), i + 11);
                    total += prefix[j] - prefix[i];
                }
                (void)total;
            });
            stats.addSample(ns);
        }
        return stats;
    }

    static BenchmarkStats benchNaive(const std::vector<int>& values, int repetitions) {
        BenchmarkStats stats;
        stats.name = "naive_range_sum";
        stats.operations = values.size();
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                volatile long long total = 0;
                for (std::size_t i = 0; i < values.size(); i += 7) {
                    const std::size_t j = std::min(values.size(), i + 11);
                    long long local = 0;
                    for (std::size_t k = i; k < j; ++k) {
                        local += values[k];
                    }
                    total += local;
                }
                (void)total;
            });
            stats.addSample(ns);
        }
        return stats;
    }
};

}  // namespace cc232::week14
