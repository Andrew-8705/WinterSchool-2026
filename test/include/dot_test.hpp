#ifndef DOT_TEST_HPP
#define DOT_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define DOT_FUNC dot_scalar
#define COMMON_TEST(TEST_NAME) TEST(dot_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define DOT_FUNC dot_rvv
#define COMMON_TEST(TEST_NAME) TEST(dot_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

float dot_ref(const float* x, const float* y, size_t n);

#endif // DOT_HPP
