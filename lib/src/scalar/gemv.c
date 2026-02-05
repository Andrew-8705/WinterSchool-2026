#include <scalar.h>

// void gemv_scalar(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     const float* a_ptr = a;
//     for(size_t j = 0; j < m; j++) {
//         float temp = 0.0;
//         for(size_t i = 0; i < n; i++) {
//             temp += a_ptr[i] * x[i];
//         }
//         y[j] += alpha * temp;
//         a_ptr += n;
//     }
// }

// void gemv_scalar(size_t m, size_t n, float alpha, const float* restrict a, const float* restrict x, float* restrict y)
// {
//     const float* a_ptr = a;
//     #pragma clang loop interleave_count(4)
//     for(size_t j = 0; j < m; j++) {
//         float temp = 0.0;
//         #pragma clang loop interleave_count(4)
//         for(size_t i = 0; i < n; i++) {
//             temp += a_ptr[i] * x[i];
//         }
//         y[j] += alpha * temp;
//         a_ptr += n;
//     }
// }



void gemv_scalar(size_t m, size_t n, float alpha, const float* restrict a, const float* restrict x, float* restrict y)
{

    #pragma clang loop unroll_count(4)
    for(size_t j = 0; j < m; j++) {
        
        float temp = 0.0f;
        const float* row_ptr = a + j * n;

        #pragma clang loop vectorize(disable) interleave_count(4)
        for(size_t i = 0; i < n; i++) {
            temp = __builtin_fmaf(row_ptr[i], x[i], temp);
        }
        
        y[j] += alpha * temp;
    }
}
