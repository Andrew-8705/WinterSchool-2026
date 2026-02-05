#include "perf_common.hpp"

#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <sys/ioctl.h>

#if defined(scalar)
#define MOD scalar
#define GEMV_FUNC gemv_scalar
#elif defined(rvv)
#define MOD rvv
#define GEMV_FUNC gemv_rvv
#else
#error "Tested function is not defined"
#endif

static inline void bench_gemv(size_t m, size_t n, int iterations) {
    std::vector<float> A(m * n);
    std::vector<float> x(n);
    std::vector<float> y(m, 0.0f);
    float alpha = 1.5f;

    prepareMatrix(A.data(), m, n);
    prepareVector(x.data(), n);

    volatile uint64_t start = 0,
                    end = 0,
                    totalCycles = 0,
                    minCycles = std::numeric_limits<uint64_t>::max(),
                    diff;

    for(int i = 0; i < iterations; i++){
        start = rdcycle();
        GEMV_FUNC(m, n, alpha, A.data(), x.data(), y.data());
        end = rdcycle();
        
        diff = end - start;
        totalCycles += diff;
        if (diff < minCycles)
            minCycles = diff;
    }

    std::string funcName = std::string{MOD} + " GEMV " + std::to_string(m) + "x" + std::to_string(n);
    printStat(minCycles, totalCycles, iterations, m * n, funcName);
}

int main() {
    struct perf_event_attr pe = { 0 }; 
    pe.type = PERF_TYPE_HARDWARE; 
    pe.size = sizeof pe;
    pe.config = PERF_COUNT_HW_CPU_CYCLES;
    pe.disabled = 0;
    pe.exclude_kernel = 1;
    long fd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);

    // 2 x 2
    bench_gemv(2, 2, 100'000);

    // 4 x 4 
    bench_gemv(4, 4, 100'000);

    // 16 x 16 
    bench_gemv(16, 16, 100'000);

    // 32 x 32
    bench_gemv(32, 32, 10'000);

    // 64 x 64
    bench_gemv(64, 64, 10'000);

    // 128 x 128
    bench_gemv(128, 128, 1'000);

    // 256 x 256
    bench_gemv(256, 256, 2);

    // 512 x 512
    bench_gemv(512, 512, 100);

    // 1024 x 1024
    bench_gemv(1024, 1024, 2);

    // 2048 x 2048
    bench_gemv(2048, 2048, 10);

    // ========= //

    // 3 x 3
    bench_gemv(3, 3, 100'000);

    // 5 x 5 
    bench_gemv(5, 5, 100'000);

    // 7 x 7
    bench_gemv(7, 7, 100'000);

    // ========= //

    // 31 x 31
    bench_gemv(31, 31, 100'000);

    // 33 x 33
    bench_gemv(33, 33, 100'000);

    // 127 x 127
    bench_gemv(127, 127, 1'000);

    // 257 x 257
    bench_gemv(257, 257, 1'000);

    // 1023 x 1023
    bench_gemv(1023, 1023, 100);

    // 2049 x 2049
    bench_gemv(2049, 2049, 10);

    // 2053 x 2053
    bench_gemv(2053, 2053, 10);

    // ========= //

    // 2048 x 32
    bench_gemv(2048, 32, 100);

    // 2048 x 256
    bench_gemv(2048, 256, 100);

    // ========= //

    // 32 x 2048
    bench_gemv(32, 2048, 100);

    // 256 x 2048
    bench_gemv(256, 2048, 100);

    return 0;
}