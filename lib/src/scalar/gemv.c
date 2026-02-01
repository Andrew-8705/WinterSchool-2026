#include <scalar.h>

void gemv_scalar(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    const float* a_ptr = a;
    for(size_t j = 0; j < m; j++) {
        float temp = 0.0;
        for(size_t i = 0; i < n; i++) {
            temp += a_ptr[i] * x[i];
        }
        y[j] += alpha * temp;
        a_ptr += n;
    }
}