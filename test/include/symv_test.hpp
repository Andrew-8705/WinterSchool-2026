#ifndef SYMV_TEST_HPP
#define SYMV_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define SYMV_FUNC symv_scalar
#define COMMON_TEST(TEST_NAME) TEST(symv_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define SYMV_FUNC symv_rvv
#define COMMON_TEST(TEST_NAME) TEST(symv_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void symv_ref(size_t n, float alpha, const float* A, const float* x, float* y);

#endif // SYMV_TEST_HPP
