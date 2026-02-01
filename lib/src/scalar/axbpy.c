#include <scalar.h>

void axpby_scalar(size_t n, float alpha, const float* x, float beta, float* y)
{
    size_t i = 0;

    while(i < n) {
        y[i] = alpha * x[i] + beta * y[i];
        i++;
    }
}