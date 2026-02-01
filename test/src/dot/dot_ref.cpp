#include "dot_test.hpp"

float dot_ref(const float* x, const float* y, size_t n) {
    float result = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        result += x[i] * y[i];
    }
    return result;
}
