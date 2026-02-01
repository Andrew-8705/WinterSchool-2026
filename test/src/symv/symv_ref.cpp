#include <scalar.h>

void symv_ref(size_t n, float alpha, const float* A, const float* x, float* y)
{
    const size_t lda = n;

    for (size_t j = 0; j < n; ++j) {
        float temp1 = alpha * x[j];
        float temp2 = 0.0;

        y[j] += temp1 * A[j * lda + j];

        for (size_t i = j + 1; i < n; ++i) {
            float aji = A[j * lda + i];
            y[i] += temp1 * aji;
            temp2 += aji * x[i];
        }

        y[j] += alpha * temp2;
    }
}
