#include "rvv.h"

extern void gemm_rvv(const float *A, const float *B, float *C, const size_t n, const size_t m, const size_t k)
{
    // Just a placaholder
    gemm_scalar(A, B, C, n, m, k);
}
