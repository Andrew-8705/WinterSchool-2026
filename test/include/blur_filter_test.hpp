#ifndef BLUR_FILTER_TEST_HPP
#define BLUR_FILTER_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define BLUR_FILTER_FUNC blur_filter_scalar
#define COMMON_TEST(TEST_NAME) TEST(blur_filter_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define BLUR_FILTER_FUNC blur_filter_rvv
#define COMMON_TEST(TEST_NAME) TEST(blur_filter_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void blur_filter_ref(uint8_t* src, uint8_t* dst, int width, int height, int kernel_size);

#endif // BLUR_FILTER_TEST_HPP
