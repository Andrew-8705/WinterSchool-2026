#include <scalar.h>

int iamin_scalar(size_t n, const float* x)
{
    int min = 0;
    if(n == 0)
        return min;

    float minf = fabsf(x[0]);
    size_t i   = 1;

    while(i < n) {
        if(fabsf(x[i]) < minf) {
            min  = i;
            minf = fabsf(x[i]);
        }
        i++;
    }
    return min;
}