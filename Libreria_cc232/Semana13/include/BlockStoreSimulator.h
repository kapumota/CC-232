#pragma once

#include "IoStats.h"

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace cc232::week13 {

template <typename Block>
class BlockStoreSimulator {
public:
    using BlockId = std::size_t;

    BlockId placeBlock(const Block& block) {
        const BlockId id = next_id_++;
        blocks_[id] = block;
        stats_.recordWrite();
        return id;
    }

    [[nodiscard]] bool contains(BlockId id) const {
        return blocks_.find(id) != blocks_.end();
    }

    Block readBlock(BlockId id) {
        const auto it = blocks_.find(id);
        if (it == blocks_.end()) {
            throw std::out_of_range("El bloque solicitado no existe");
        }
        stats_.recordRead();
        return it->second;
    }

    void writeBlock(BlockId id, const Block& block) {
        if (!contains(id)) {
            throw std::out_of_range("No se puede escribir un bloque inexistente");
        }
        blocks_[id] = block;
        stats_.recordWrite();
    }

    void freeBlock(BlockId id) {
        blocks_.erase(id);
        stats_.recordWrite();
    }

    [[nodiscard]] const IoStats& stats() const {
        return stats_;
    }

    void resetStats() {
        stats_.reset();
    }

    [[nodiscard]] std::size_t size() const {
        return blocks_.size();
    }

    [[nodiscard]] std::vector<BlockId> ids() const {
        std::vector<BlockId> result;
        result.reserve(blocks_.size());
        for (const auto& entry : blocks_) {
            result.push_back(entry.first);
        }
        return result;
    }

private:
    std::unordered_map<BlockId, Block> blocks_;
    BlockId next_id_ = 1;
    IoStats stats_;
};

}  // namespace cc232::week13
