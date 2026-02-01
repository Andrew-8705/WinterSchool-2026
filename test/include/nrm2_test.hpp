#ifndef NRM2_TEST_HPP
#define NRM2_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define NRM2_FUNC nrm2_scalar
#define COMMON_TEST(TEST_NAME) TEST(nrm2_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define NRM2_FUNC nrm2_rvv
#define COMMON_TEST(TEST_NAME) TEST(nrm2_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

float nrm2_ref(size_t n, const float* x);

#endif // NRM2_TEST_HPP
