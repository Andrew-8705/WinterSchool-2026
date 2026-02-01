#include "abs_test.hpp"

void fabsf_ref(float* src, float* dst, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        dst[i] = fabsf(src[i]);
    }
}
