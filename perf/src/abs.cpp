#include "perf_common.hpp"

#if defined(scalar)
#define MOD scalar
#define FABSF_FUNC fabsf_scalar
#elif defined(rvv)
#define MOD rvv
#define FABSF_FUNC fabsf_rvv
#else
#error "Tested function is not defined"
#endif

static inline void bench_abs(int length, int iterations) {
    std::vector<float> src(length, 0);
    std::vector<float> dst(length, 0);

    prepareVector(src.data(), length);

    volatile uint64_t start = 0,
                    end = 0,
                    totalCycles = 0,
                    minCycles = std::numeric_limits<uint64_t>::max(),
                    diff;

    for(int i = 0; i < iterations; i++){
        start = rdcycle();
        FABSF_FUNC(src.data(), dst.data(), length);
        end = rdcycle();
        diff = end - start;
        totalCycles += diff;
        if (diff < minCycles)
            minCycles = diff;
    }
#if defined(scalar)
    std::string funcName = std::string{"Scalar FABS with length "} + std::to_string(length);
#elif defined(rvv)
    std::string funcName = std::string{"RVV FABS with length "} + std::to_string(length);
#else
#error "Tested function is not defined"
#endif

    printStat(minCycles, totalCycles, iterations, length, funcName);
}

int main() {

    //
    // Bench small sizes
    //
    constexpr int small_length = 64;
    constexpr int small_iterations = 100'000;
    bench_abs(small_length, small_iterations);

    //
    // Bench medium sizes
    //
    constexpr int medium_length = 1024;
    constexpr int medium_iterations = 1'000;
    bench_abs(medium_length, medium_iterations);

    //
    // Bench big sizes
    //
    constexpr int big_length = 524288;
    constexpr int big_iterations = 100;
    bench_abs(big_length, big_iterations);

    return 0;
}
