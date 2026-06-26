#pragma once

#include <cstddef>
#include <string>

namespace cc232::week13 {

struct IoStats {
    std::size_t block_reads = 0;
    std::size_t block_writes = 0;
    std::size_t comparisons = 0;

    void reset() {
        block_reads = 0;
        block_writes = 0;
        comparisons = 0;
    }

    void recordRead(std::size_t count = 1) {
        block_reads += count;
    }

    void recordWrite(std::size_t count = 1) {
        block_writes += count;
    }

    void recordComparison(std::size_t count = 1) {
        comparisons += count;
    }

    [[nodiscard]] std::size_t totalIo() const {
        return block_reads + block_writes;
    }

    [[nodiscard]] std::string summary() const {
        return "lecturas=" + std::to_string(block_reads) +
               ", escrituras=" + std::to_string(block_writes) +
               ", comparaciones=" + std::to_string(comparisons);
    }
};

}  // namespace cc232::week13
