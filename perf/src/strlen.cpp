#include "perf_common.hpp"

#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <sys/ioctl.h>

#if defined(scalar)
#define MOD scalar
#define STRLEN_FUNC strlen_scalar
#elif defined(rvv)
#define MOD rvv
#define STRLEN_FUNC strlen_rvv
#else
#error "Tested function is not defined"
#endif

static inline void bench_strlen(int length, int iterations) {
    std::vector<uint8_t> str_buf(length);
    
    prepareString(str_buf.data(), length);

    volatile uint64_t start = 0,
                    end = 0,
                    totalCycles = 0,
                    minCycles = std::numeric_limits<uint64_t>::max(),
                    diff;


    volatile size_t res = 0;

    for(int i = 0; i < iterations; i++){
        start = rdcycle();
            res = STRLEN_FUNC((const char*)str_buf.data());
        end = rdcycle();
        
        diff = end - start;
        totalCycles += diff;
        if (diff < minCycles)
            minCycles = diff;
    }

#if defined(scalar)
    std::string funcName = std::string{"Scalar STRLEN with length "} + std::to_string(length);
#elif defined(rvv)
    std::string funcName = std::string{"RVV STRLEN with length "} + std::to_string(length);
#endif

    printStat(minCycles, totalCycles, iterations, length, funcName);
}

int main() {
    struct perf_event_attr pe = { 0 }; 
    pe.type = PERF_TYPE_HARDWARE; 
    pe.size = sizeof pe;
    pe.config = PERF_COUNT_HW_CPU_CYCLES;
    pe.disabled = 0;
    pe.exclude_kernel = 1;
    long fd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);

    constexpr int small_length1 = 32;
    constexpr int small_iterations1 = 100'000;
    bench_strlen(small_length1, small_iterations1);

    constexpr int small_length2 = 64;
    constexpr int small_iterations2 = 100'000;
    bench_strlen(small_length2, small_iterations2);

    constexpr int small_length3 = 128;
    constexpr int small_iterations3 = 100'000;
    bench_strlen(small_length3, small_iterations3);

    constexpr int small_length4 = 256;
    constexpr int small_iterations4 = 10'000;
    bench_strlen(small_length4, small_iterations4);

    constexpr int small_length5 = 512;
    constexpr int small_iterations5 = 10'000;
    bench_strlen(small_length5, small_iterations5);

    constexpr int medium_length6 = 1024;
    constexpr int medium_iterations6 = 1'000;
    bench_strlen(medium_length6, medium_iterations6);

    constexpr int small_length7 = 32768;
    constexpr int small_iterations7 = 100;
    bench_strlen(small_length7, small_iterations7);

    constexpr int big_length = 524288;
    constexpr int big_iterations = 100;
    bench_strlen(big_length, big_iterations);

    return 0;
}