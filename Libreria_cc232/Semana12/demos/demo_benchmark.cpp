#include "CapituloConsultasRango.h"

#include <chrono>
#include <iostream>
#include <vector>

int main() {
    using namespace cc232::week12;
    using Clock = std::chrono::steady_clock;

    const int n = 20000;
    std::vector<long long> values(n, 1);

    auto startFenwick = Clock::now();
    FenwickTree bit(values);
    long long fenwickAnswer = 0;
    for (int i = 0; i < n; i += 7) {
        fenwickAnswer += bit.rangeSum(i, std::min(n - 1, i + 50));
    }
    auto endFenwick = Clock::now();

    auto startSegment = Clock::now();
    SegmentTree segment(values);
    long long segmentAnswer = 0;
    for (int i = 0; i < n; i += 7) {
        segmentAnswer += segment.rangeSum(i, std::min(n - 1, i + 50));
    }
    auto endSegment = Clock::now();

    std::cout << "### Demo: comparacion experimental minima\n";
    std::cout << "Respuesta Fenwick: " << fenwickAnswer << "\n";
    std::cout << "Respuesta SegmentTree: " << segmentAnswer << "\n";
    std::cout << "Tiempo Fenwick en microsegundos: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endFenwick - startFenwick).count() << "\n";
    std::cout << "Tiempo SegmentTree en microsegundos: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endSegment - startSegment).count() << "\n";
    return 0;
}
