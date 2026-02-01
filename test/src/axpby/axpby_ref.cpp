#include "blur_filter_test.hpp"

void axpby_ref(size_t n, float alpha, const float* x, float beta, float* y) {
    size_t i = 0;

    while(i < n) {
        y[i] = alpha * x[i] + beta * y[i];
        i++;
    }
}
