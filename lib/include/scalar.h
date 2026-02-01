#ifndef SCALAR_H
#define SCALAR_H

#include "common.h"

// libm
extern void fabsf_scalar(const float* src, float* dst, size_t n);

// libc
extern size_t strlen_scalar(const char *str);

// BLAS level-1
extern float dot_scalar(const float* x, const float* y, size_t n);
extern void axpby_scalar(size_t n, float alpha, const float* x, float beta, float* y);
extern float nrm2_scalar(size_t n, const float* x);
extern int iamin_scalar(size_t n, const float* x);

// BLAS level-2
extern void gemv_scalar(size_t m, size_t n, float alpha, const float* a, const float* x, float* y);

// BLAS level-3
extern void gemm_scalar(const float *A, const float *B, float *C, const size_t n, const size_t m, const size_t k);
extern void symv_scalar(size_t n, float alpha, const float* a, const float* x, float* y);

// Image processing
extern void blur_filter_scalar(uint8_t* src, uint8_t* dst, int width, int height, int kernel_size);
extern void alpha_compositing_scalar(uint8_t* foreground, uint8_t* background, float alpha, uint8_t* dst, int width, int height, int channels);

#endif // SCALAR_H
