#pragma once

#include "BenchmarkStats.h"
#include "BenchmarkTimer.h"

#include <queue>
#include <vector>

namespace cc232::week14 {

class GraphBenchmark {
public:
    BenchmarkStats benchBfsAdjacencyList(std::size_t vertices, int repetitions = 3) const {
        std::vector<std::vector<int>> graph(vertices);
        for (std::size_t i = 1; i < vertices; ++i) {
            graph[i - 1].push_back(static_cast<int>(i));
            graph[i].push_back(static_cast<int>(i - 1));
        }
        BenchmarkStats stats;
        stats.name = "bfs_adjacency_list";
        stats.operations = vertices;
        for (int r = 0; r < repetitions; ++r) {
            auto ns = BenchmarkTimer::measureNanoseconds([&]() {
                std::vector<int> dist(vertices, -1);
                std::queue<int> q;
                dist[0] = 0;
                q.push(0);
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : graph[static_cast<std::size_t>(u)]) {
                        if (dist[static_cast<std::size_t>(v)] == -1) {
                            dist[static_cast<std::size_t>(v)] = dist[static_cast<std::size_t>(u)] + 1;
                            q.push(v);
                        }
                    }
                }
            });
            stats.addSample(ns);
        }
        return stats;
    }
};

}  // namespace cc232::week14
