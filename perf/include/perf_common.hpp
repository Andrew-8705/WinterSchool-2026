#ifndef PERF_COMMON_HPP
#define PERF_COMMON_HPP

extern "C" {
#include "rvv.h"
}

#include <iostream>
#include <limits>
#include <random>
#include <algorithm>
#include <functional>

[[maybe_unused]]
static void prepareString(uint8_t* str, int length) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<uint8_t> dist(0, 255);

    std::generate(str, str + length, [&]() { return dist(rng); });
    str[length-1] = '\0';
}

[[maybe_unused]]
static void prepareVector(float* vec, int length) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    std::generate(vec, vec + length, [&]() { return dist(rng); });
}

[[maybe_unused]]
static void prepareMatrix(float* matrix, int rows, int cols) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    std::generate(matrix, matrix + rows * cols, [&]() { return dist(rng); });
}

[[maybe_unused]]
static void prepareImage(uint8_t* image, int width, int height, int channels) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<uint8_t> dist(0, 255);

    std::generate(image, image + width * height * channels, [&]() { return dist(rng); });
}

[[maybe_unused]]
static void printStat(uint64_t minCycles, uint64_t totalCycles, int iterations, int size, const std::string& funcName = {}) {
    (void)size;
    const uint64_t avgCycles = totalCycles / iterations;

    std::cout << "================================" << std::endl;
    std::cout << "Testing " << funcName << std::endl;
    std::cout << minCycles << " cycles min" << std::endl;
    std::cout << avgCycles << " cycles average" << std::endl;
    std::cout << "================================" << std::endl;
}

#ifdef __riscv
static inline uint64_t __attribute__((__always_inline__, __artificial__)) rdcycle(void)
{
    uint64_t dst;
    asm volatile ("csrrs %0, 0xc00, x0" : "=r" (dst));
    return dst;
}
#endif // __riscv

#ifdef __x86_64__
static __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__)) uint64_t rdcycle(void){
#ifdef C_MSVC
  return __rdtsc();
#else
  uint64_t a, d;

  __asm__ __volatile__ ("rdtsc" : "=a" (a), "=d" (d));

  return ((uint64_t)a + ((uint64_t)d << 32));
#endif
}
#endif // __x86_64__

#endif // PERF_COMMON_H
