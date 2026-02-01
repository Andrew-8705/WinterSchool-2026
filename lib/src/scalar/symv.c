#include <scalar.h>

void symv_scalar(size_t n, float alpha, const float* a, const float* x, float* y)
{
    const size_t inc_x  = 1;
    const size_t inc_y  = 1;
    const size_t lda    = n;
    const size_t offset = n;

    size_t jx = 0;
    size_t jy = 0;

    for(size_t j = 0; j < offset; j++) {
        float temp1 = alpha * x[jx];
        float temp2 = 0.0;
        y[jy] += temp1 * a[j * lda + j];

        size_t iy = jy;
        size_t ix = jx;

        for(size_t i = j + 1; i < n; i++) {
            ix += inc_x;
            iy += inc_y;
            y[iy] += temp1 * a[j * lda + i];
            temp2 += a[j * lda + i] * x[ix];
        }
        y[jy] += alpha * temp2;
        jx += inc_x;
        jy += inc_y;
    }
}
