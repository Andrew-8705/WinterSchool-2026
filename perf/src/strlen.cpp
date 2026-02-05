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

    bench_strlen(32, 100'000);

    bench_strlen(64, 100'000);

    bench_strlen(128, 100'000);

    bench_strlen(256, 10'000);

    bench_strlen(512, 10'000);

    bench_strlen(1024, 1'000);

    bench_strlen(32768, 100);

    bench_strlen(524288, 100);

    // ========= //

    bench_strlen(1, 100'000);

    bench_strlen(4, 100'000);

    bench_strlen(8, 100'000);

    bench_strlen(15, 100'000);

    bench_strlen(16, 100'000);

    bench_strlen(17, 100'000);

    bench_strlen(31, 100'000);

    // ========= //

    bench_strlen(4090, 1'000);

    bench_strlen(4096, 1'000);

    bench_strlen(4097, 1'000);

    // ========= //

    bench_strlen(32760, 1'000);

    bench_strlen(32768, 1'000);

    bench_strlen(32770, 1'000);

    // ========= //

    bench_strlen(262144, 1'000);

    return 0;
}