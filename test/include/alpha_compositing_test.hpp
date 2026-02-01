#ifndef ALPHA_COMPOSTING_TEST_HPP
#define ALPHA_COMPOSTING_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define ALPHA_COMPOSTING_FUNC alpha_compositing_scalar
#define COMMON_TEST(TEST_NAME) TEST(alpha_compositing_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define ALPHA_COMPOSTING_FUNC alpha_compositing_rvv
#define COMMON_TEST(TEST_NAME) TEST(alpha_compositing_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

void alpha_compositing_ref(uint8_t* foreground, uint8_t* background, float alpha, uint8_t* dst, int width, int height, int channels);

#endif // ALPHA_COMPOSTING_TEST_HPP
