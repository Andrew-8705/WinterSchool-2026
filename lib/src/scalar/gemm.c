#include <scalar.h>

#define BLOCK_SIZE 4

static inline void process_block_nxk(const size_t n, const size_t k, const size_t m, const float *A, const size_t lda, const float *B, const size_t ldb, float *C, const size_t ldc);

/**
 * Multiplies two matrices A and B with dimensions n x m and m x k respectively
 * using a block-based approach.
 *
 * @param A Pointer to the first matrix (size n x m).
 * @param B Pointer to the second matrix (size m x k).
 * @param C Pointer to the resulting matrix (size n x k).
 * @param n Number of rows in matrix A and resulting matrix C.
 * @param m Number of columns in matrix A and number of rows in matrix B.
 * @param k Number of columns in matrix B and resulting matrix C.
 */
extern void gemm_scalar(const float *A, const float *B, float *C, const size_t n, const size_t m, const size_t k)
{
    size_t blocks_n = (n / BLOCK_SIZE) * BLOCK_SIZE;
    size_t blocks_k = (k / BLOCK_SIZE) * BLOCK_SIZE;

    size_t tail_n = n - blocks_n;
    size_t tail_k = k - blocks_k;

    size_t i;
    size_t j;
    for (i = 0; i < blocks_n; i += BLOCK_SIZE) {
        for (j = 0; j < blocks_k; j += BLOCK_SIZE) {
            process_block_nxk(BLOCK_SIZE, BLOCK_SIZE, m, &A[i*m], m, &B[j], k, &C[(i*k) + j], k);
        }
        if (tail_k != 0) {
            process_block_nxk(BLOCK_SIZE, tail_k, m, &A[i*m], m, &B[j], k, &C[(i*k) + j], k);
        }
    }
    if (tail_n != 0) {
        for (j = 0; j < blocks_k; j += BLOCK_SIZE) {
            process_block_nxk(tail_n, BLOCK_SIZE, m, &A[i*m], m, &B[j], k, &C[(i*k) + j], k);
        }
        if (tail_k != 0){
            process_block_nxk(tail_n, tail_k, m, &A[i*m], m, &B[j], k, &C[(i*k) + j], k);
        }
    }
}


static inline void process_block_nxk(const size_t n, const size_t k, const size_t m, const float *A, const size_t lda, const float *B, const size_t ldb, float *C, const size_t ldc) {
    for (size_t i = 0; i < n; i++) { /* Loop over the rows of C */
        for (size_t j = 0; j < k; j++) { /* Loop over the columns of C */
            for (size_t p = 0; p < m; p++) {  /* Update C( i,j ) with the inner
                                                 product of the ith row of A and
                                                 the jth column of B */
                C[i * ldc + j] += A[i * lda + p] * B[p * ldb + j];
            }
        }
    }
}

