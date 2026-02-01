#include "gemv_test.hpp"

void gemv_ref(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            y[i] += alpha * a[i * n + j] * x[j];
        }
    }
}