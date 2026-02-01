#include <scalar.h>

float dot_scalar(const float* x, const float* y, size_t n)
{
    int i     = 0;
    float dot = 0.0f;

    while(i < n) {
        dot += y[i] * x[i];
        i++;
    }
    return dot;
}
