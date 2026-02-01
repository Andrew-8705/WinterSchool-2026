#ifndef RVV_H
#define RVV_H

#include "riscv_vector.h"

#include "common.h"
#include "scalar.h"

// libm
extern void fabsf_rvv(const float* src, float* dst, size_t n);

// libc
extern size_t strlen_rvv(const char *str);

// BLAS level-1
extern float dot_rvv(const float* x, const float* y, size_t n);
extern void axpby_rvv(size_t n, float alpha, const float* x, float beta, float* y);
extern float nrm2_rvv(size_t n, const float* x);
extern int iamin_rvv(size_t n, const float* x);

// BLAS level-2
extern void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y);

// BLAS level-3
extern void gemm_rvv(const float *A, const float *B, float *C, const size_t n, const size_t m, const size_t k);
extern void symv_rvv(size_t n, float alpha, const float* a, const float* x, float* y);

// Image processing
extern void blur_filter_rvv(uint8_t* src, uint8_t* dst, int width, int height, int kernel_size);
extern void alpha_compositing_rvv(uint8_t* foreground, uint8_t* background, float alpha, uint8_t* dst, int width, int height, int channels);

#endif // RVV_H