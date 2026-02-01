#ifndef STRLEN_TEST_HPP
#define STRLEN_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define STRLEN_FUNC strlen_scalar
#define COMMON_TEST(TEST_NAME) TEST(strlen_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define STRLEN_FUNC strlen_rvv
#define COMMON_TEST(TEST_NAME) TEST(strlen_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

size_t strlen_ref(const char *str);

#endif // STRLEN_TEST_HPP