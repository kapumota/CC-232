#pragma once

#include "BenchmarkStats.h"
#include "BenchmarkTimer.h"

#include <string>
#include <vector>

namespace cc232::week14 {

class TextIndexBenchmark {
public:
    BenchmarkStats benchNaiveFind(const std::string& text, const std::vector<std::string>& patterns, int repetitions = 3) const {
        BenchmarkStats stats;
        stats.name = "naive_text_find";
        stats.operations = patterns.size();
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                volatile std::size_t found = 0;
                for (const auto& pattern : patterns) {
                    found += text.find(pattern) != std::string::npos;
                }
                (void)found;
            });
            stats.addSample(ns);
        }
        return stats;
    }
};

}  // namespace cc232::week14
