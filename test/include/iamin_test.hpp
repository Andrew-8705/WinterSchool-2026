#ifndef IAMIN_TEST_HPP
#define IAMIN_TEST_HPP

#include "test_common.hpp"

#if defined(scalar)
#define MOD scalar
#define IAMIN_FUNC iamin_scalar
#define COMMON_TEST(TEST_NAME) TEST(iamin_common_scalar, TEST_NAME)
#elif defined(rvv)
#define MOD rvv
#define IAMIN_FUNC iamin_rvv
#define COMMON_TEST(TEST_NAME) TEST(iamin_common_rvv, TEST_NAME)
#else
#error "Tested function is not defined"
#endif

int iamin_ref(size_t n, const float* x);

#endif // IAMIN_TEST_HPP
