#include "rvv.h"
#include <stdio.h>

void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    size_t vlmax = __riscv_vsetvlmax_e32m8();
    vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

    for (size_t i = 0; i < m; i++) {
        const float* ptr_a = a + i * n;
        const float* ptr_x = x;
        size_t k = n;

        vfloat32m8_t new_v = __riscv_vfmv_v_f_f32m8(0.0f, vlmax);

        while (k > 0) {
            size_t vl = __riscv_vsetvl_e32m8(k);
            vfloat32m8_t vm = __riscv_vle32_v_f32m8(ptr_a, vl);
            vfloat32m8_t vv = __riscv_vle32_v_f32m8(ptr_x, vl);

            new_v = __riscv_vfmacc_vv_f32m8(new_v, vm, vv, vl);

            ptr_a += vl;
            ptr_x += vl; 
            k -= vl;
        }
        
        
        vfloat32m1_t v_sum = __riscv_vfredusum_vs_f32m8_f32m1(new_v, v_zero, vlmax);
        float sum = __riscv_vfmv_f_s_f32m1_f32(v_sum);

        y[i] = alpha * sum;
    }
}

/*
const float* a_ptr = a;
for(size_t j = 0; j < m; j++) {
    float temp = 0.0;
    for(size_t i = 0; i < n; i++) {
        temp += a_ptr[i] * x[i];
    }
    y[j] += alpha * temp;
    a_ptr += n;
}

*/