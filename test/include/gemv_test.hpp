#ifndef GEMV_TEST_HPP
#define GEMV_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define GEMV_FUNC gemv_scalar
#define COMMON_TEST(TEST_NAME) TEST(gemv_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define GEMV_FUNC gemv_rvv
#define COMMON_TEST(TEST_NAME) TEST(gemv_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void gemv_ref(size_t m, size_t n, float alpha, const float* a, const float* x, float* y);

#endif // GEMV_TEST_HPP
