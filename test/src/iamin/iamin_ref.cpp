#include <scalar.h>

int iamin_ref(size_t n, const float* x) {
    if (n == 0 || x == NULL) {
        return 0;
    }

    int min_index = 0;
    float min_value = fabs(x[0]);

    for (size_t i = 1; i < n; ++i) {
        float abs_value = fabs(x[i]);
        if (abs_value < min_value) {
            min_value = abs_value;
            min_index = i;
        }
    }

    return min_index;
}
