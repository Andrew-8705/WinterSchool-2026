#include "scalar.h"

static inline float fabsf_kernel(float arg)
{
    float    res;
    uint32_t i_arg;
    __builtin_memcpy((unsigned char*)&i_arg, (unsigned char*)(&arg), 4);
    i_arg = i_arg & 0x7fffffff;
    __builtin_memcpy((unsigned char*)&res, (unsigned char*)(&i_arg), 4);
    return res;
}

void fabsf_scalar(const float* src, float* dst, size_t n)
{
    for (int i = 0; i < n; i++) {
        dst[i] = fabsf_kernel(src[i]);
    }
}
