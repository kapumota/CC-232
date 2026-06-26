#pragma once

#include "BenchmarkStats.h"
#include "BenchmarkTimer.h"

#include <algorithm>
#include <vector>

namespace cc232::week14 {

class SortingBenchmark {
public:
    std::vector<BenchmarkStats> run(const std::vector<int>& values, int repetitions = 3) const {
        std::vector<BenchmarkStats> stats;
        stats.push_back(benchStdSort(values, repetitions));
        stats.push_back(benchInsertionSort(values, repetitions));
        return stats;
    }

private:
    static BenchmarkStats benchStdSort(const std::vector<int>& values, int repetitions) {
        BenchmarkStats stats;
        stats.name = "std_sort";
        stats.operations = values.size();
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                auto copy = values;
                std::sort(copy.begin(), copy.end());
            });
            stats.addSample(ns);
        }
        return stats;
    }

    static BenchmarkStats benchInsertionSort(const std::vector<int>& values, int repetitions) {
        BenchmarkStats stats;
        stats.name = "insertion_sort";
        stats.operations = values.size();
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                auto copy = values;
                for (std::size_t i = 1; i < copy.size(); ++i) {
                    int key = copy[i];
                    std::size_t j = i;
                    while (j > 0 && copy[j - 1] > key) {
                        copy[j] = copy[j - 1];
                        --j;
                    }
                    copy[j] = key;
                }
            });
            stats.addSample(ns);
        }
        return stats;
    }
};

}  // namespace cc232::week14
