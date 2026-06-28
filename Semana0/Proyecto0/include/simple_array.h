#ifndef CC232_SIMPLE_ARRAY_H
#define CC232_SIMPLE_ARRAY_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace cc232 {

template <typename T>
T maximum(const T& a, const T& b) {
    return (b < a) ? a : b;
}

template <typename T>
class SimpleArray {
public:
    explicit SimpleArray(std::size_t n)
        : size_(n), data_(n == 0 ? nullptr : std::make_unique<T[]>(n)) {}

    SimpleArray(const SimpleArray& other)
        : size_(other.size_), data_(other.size_ == 0 ? nullptr : std::make_unique<T[]>(other.size_)) {
        std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
    }

    SimpleArray& operator=(const SimpleArray& other) {
        if (this == &other) {
            return *this;
        }

        SimpleArray copy(other);
        swap(copy);
        return *this;
    }

    SimpleArray(SimpleArray&& other) noexcept = default;
    SimpleArray& operator=(SimpleArray&& other) noexcept = default;
    ~SimpleArray() = default;

    std::size_t size() const noexcept {
        return size_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    T& operator[](std::size_t index) noexcept {
        return data_[index];
    }

    const T& operator[](std::size_t index) const noexcept {
        return data_[index];
    }

    T& at(std::size_t index) {
        validateIndex(index);
        return data_[index];
    }

    const T& at(std::size_t index) const {
        validateIndex(index);
        return data_[index];
    }

    void fill(const T& value) {
        std::fill(data_.get(), data_.get() + size_, value);
    }

    void swap(SimpleArray& other) noexcept {
        using std::swap;
        swap(size_, other.size_);
        swap(data_, other.data_);
    }

private:
    void validateIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("indice fuera de rango en SimpleArray");
        }
    }

    std::size_t size_{};
    std::unique_ptr<T[]> data_{};
};

template <typename T>
void swap(SimpleArray<T>& a, SimpleArray<T>& b) noexcept {
    a.swap(b);
}

} // namespace cc232

#endif
