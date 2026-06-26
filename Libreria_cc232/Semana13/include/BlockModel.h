#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace cc232::week13 {

class BlockModel {
public:
    BlockModel(std::size_t block_size_bytes,
               std::size_t key_size_bytes,
               std::size_t pointer_size_bytes,
               std::size_t payload_size_bytes = 0)
        : block_size_bytes_(block_size_bytes),
          key_size_bytes_(key_size_bytes),
          pointer_size_bytes_(pointer_size_bytes),
          payload_size_bytes_(payload_size_bytes) {
        if (block_size_bytes_ == 0 || key_size_bytes_ == 0 || pointer_size_bytes_ == 0) {
            throw std::invalid_argument("Los tamaños de bloque, clave y puntero deben ser positivos");
        }
    }

    [[nodiscard]] std::size_t blockSizeBytes() const { return block_size_bytes_; }
    [[nodiscard]] std::size_t keySizeBytes() const { return key_size_bytes_; }
    [[nodiscard]] std::size_t pointerSizeBytes() const { return pointer_size_bytes_; }
    [[nodiscard]] std::size_t payloadSizeBytes() const { return payload_size_bytes_; }

    [[nodiscard]] std::size_t maxKeysInBTreeNode() const {
        // Un nodo interno con k claves usa k claves y k + 1 punteros.
        if (block_size_bytes_ <= pointer_size_bytes_) {
            return 1;
        }
        const std::size_t per_key_cost = key_size_bytes_ + pointer_size_bytes_;
        return std::max<std::size_t>(1, (block_size_bytes_ - pointer_size_bytes_) / per_key_cost);
    }

    [[nodiscard]] std::size_t maxRecordsInLeafPage() const {
        const std::size_t record_cost = key_size_bytes_ + std::max<std::size_t>(1, payload_size_bytes_);
        return std::max<std::size_t>(1, block_size_bytes_ / record_cost);
    }

    [[nodiscard]] std::size_t approximateFanout() const {
        return maxKeysInBTreeNode() + 1;
    }

private:
    std::size_t block_size_bytes_;
    std::size_t key_size_bytes_;
    std::size_t pointer_size_bytes_;
    std::size_t payload_size_bytes_;
};

inline std::size_t ceilLogBase(std::size_t value, std::size_t base) {
    if (value <= 1) {
        return 0;
    }
    if (base <= 1) {
        throw std::invalid_argument("La base debe ser mayor que uno");
    }
    std::size_t height = 0;
    std::size_t capacity = 1;
    while (capacity < value) {
        const std::size_t previous = capacity;
        capacity *= base;
        ++height;
        if (capacity < previous) {
            return height;
        }
    }
    return height;
}

inline std::size_t approximateBTreeHeight(std::size_t keys, std::size_t fanout) {
    return ceilLogBase(std::max<std::size_t>(1, keys + 1), std::max<std::size_t>(2, fanout));
}

inline std::size_t worstCaseBstHeight(std::size_t keys) {
    return keys == 0 ? 0 : keys - 1;
}

inline std::size_t balancedBstHeight(std::size_t keys) {
    return ceilLogBase(std::max<std::size_t>(1, keys + 1), 2);
}

}  // namespace cc232::week13
