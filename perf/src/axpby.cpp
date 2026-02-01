#include "perf_common.hpp"

#if defined(scalar)
#define MOD scalar
#define AXPBY_FUNC axpby_scalar
#elif defined(rvv)
#define MOD rvv
#define AXPBY_FUNC axpby_rvv
#else
#error "Tested function is not defined"
#endif

static inline void bench_axpby(int length, int iterations) {
    std::vector<float> src(length, 0);
    std::vector<float> dst(length, 0);

    // prepareVector(src.data(), length);
    // prepareVector(dst.data(), length);

    volatile uint64_t start = 0,
                    end = 0,
                    totalCycles = 0,
                    minCycles = std::numeric_limits<uint64_t>::max(),
                    diff;

    for(int i = 0; i < iterations; i++){
        start = rdcycle();
        AXPBY_FUNC(length, 1.5, src.data(), 1.5, dst.data());
        end = rdcycle();
        diff = end - start;
        totalCycles += diff;
        if (diff < minCycles)
            minCycles = diff;
    }
#if defined(scalar)
    std::string funcName = std::string{"Scalar AXPBY with length "} + std::to_string(length);
#elif defined(rvv)
    std::string funcName = std::string{"RVV AXPBY with length "} + std::to_string(length);
#else
#error "Tested function is not defined"
#endif

    printStat(minCycles, totalCycles, iterations, length, funcName);
}

int main() {
    //
    // Bench medium sizes
    //
    constexpr int medium_length = 1024;
    constexpr int medium_iterations = 15;
    bench_axpby(medium_length, medium_iterations);

    return 0;
}