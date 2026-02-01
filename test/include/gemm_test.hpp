#ifndef GEMM_TEST_HPP
#define GEMM_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define GEMM_FUNC gemm_scalar
#define COMMON_TEST(TEST_NAME) TEST(gemm_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define GEMM_FUNC gemm_rvv
#define COMMON_TEST(TEST_NAME) TEST(gemm_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void gemm_ref(const float *A, const float *B, float *C, const size_t n, const size_t m, const size_t k);

#endif // GEMM_TEST_HPP
