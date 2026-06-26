#pragma once

#include "BenchmarkStats.h"
#include "BenchmarkTimer.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace cc232::week14 {

class DictionaryBenchmark {
public:
    std::vector<BenchmarkStats> run(const std::vector<int>& keys, int repetitions = 3) const {
        std::vector<BenchmarkStats> stats;
        stats.push_back(benchUnorderedSet(keys, repetitions));
        stats.push_back(benchOrderedSet(keys, repetitions));
        return stats;
    }

private:
    static BenchmarkStats benchUnorderedSet(const std::vector<int>& keys, int repetitions) {
        BenchmarkStats stats;
        stats.name = "unordered_set";
        stats.operations = keys.size() * 2;
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                std::unordered_set<int> table;
                table.reserve(keys.size() * 2 + 1);
                for (int key : keys) {
                    table.insert(key);
                }
                volatile std::size_t found = 0;
                for (int key : keys) {
                    found += table.count(key);
                }
                (void)found;
            });
            stats.addSample(ns);
        }
        return stats;
    }

    static BenchmarkStats benchOrderedSet(const std::vector<int>& keys, int repetitions) {
        BenchmarkStats stats;
        stats.name = "set";
        stats.operations = keys.size() * 2;
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                std::set<int> tree;
                for (int key : keys) {
                    tree.insert(key);
                }
                volatile std::size_t found = 0;
                for (int key : keys) {
                    found += tree.count(key);
                }
                (void)found;
            });
            stats.addSample(ns);
        }
        return stats;
    }
};

}  // namespace cc232::week14
