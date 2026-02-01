#ifndef AXPBY_TEST_HPP
#define AXPBY_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define AXPBY_FUNC axpby_scalar
#define COMMON_TEST(TEST_NAME) TEST(axpby_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define AXPBY_FUNC axpby_rvv
#define COMMON_TEST(TEST_NAME) TEST(axpby_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void axpby_ref(size_t n, float alpha, const float* x, float beta, float* y);

#endif // AXPBY_TEST_HPP
