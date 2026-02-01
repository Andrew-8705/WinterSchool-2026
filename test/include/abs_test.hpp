#ifndef ABS_TEST_HPP
#define ABS_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define FABSF_FUNC fabsf_scalar
#define COMMON_TEST(TEST_NAME) TEST(abs_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define FABSF_FUNC fabsf_rvv
#define COMMON_TEST(TEST_NAME) TEST(abs_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void fabsf_ref(float* src, float* dst, size_t n);

#endif // ABS_TEST_HPP