#include "rvv.h"

void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    // Just a placeholder
    gemv_scalar(m, n, alpha, a, x, y);
}
