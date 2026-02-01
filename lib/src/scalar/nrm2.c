#include "scalar.h"

float nrm2_scalar(size_t n, const float* x)
{
    size_t i       = 0;
    float scale = 0.0f;
    float ssq   = 1.0f;
    float absxi = 0.0f;

    while(i < n) {
        if(x[i] != 0.0f) {
            absxi = fabsf(x[i]);
            if(scale < absxi) {
                ssq   = 1 + ssq * (scale / absxi) * (scale / absxi);
                scale = absxi;
            }
            else {
                ssq += (absxi / scale) * (absxi / scale);
            }
        }
        i++;
    }

    return scale * sqrtf(ssq);
}