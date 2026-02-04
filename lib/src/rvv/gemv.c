#include "rvv.h"
#include <stdio.h>

// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax = __riscv_vsetvlmax_e32m1();
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

//     for (size_t i = 0; i < m; i++) {
//         const float* ptr_a = a + i * n;
//         const float* ptr_x = x;
//         size_t k = n;

//         vfloat32m1_t new_v = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m1(k);
//             vfloat32m1_t vm = __riscv_vle32_v_f32m1(ptr_a, vl);
//             vfloat32m1_t vv = __riscv_vle32_v_f32m1(ptr_x, vl);

//             new_v = __riscv_vfmacc_vv_f32m1(new_v, vm, vv, vl);

//             ptr_a += vl;
//             ptr_x += vl; 
//             k -= vl;
//         }
        
        
//         vfloat32m1_t v_sum = __riscv_vfredusum_vs_f32m1_f32m1(new_v, v_zero, vlmax);
//         float sum = __riscv_vfmv_f_s_f32m1_f32(v_sum);

//         y[i] += alpha * sum;
//     }
// }



// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax = __riscv_vsetvlmax_e32m2();
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

//     size_t i = 0;
//     for (; i + 4 <= m; i += 4) {
//         const float* ptr_a0 = a + (i + 0) * n;
//         const float* ptr_a1 = a + (i + 1) * n;
//         const float* ptr_a2 = a + (i + 2) * n;
//         const float* ptr_a3 = a + (i + 3) * n;
//         const float* ptr_x  = x;
        
//         size_t k = n;

//         vfloat32m2_t acc0 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax);
//         vfloat32m2_t acc1 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax);
//         vfloat32m2_t acc2 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax);
//         vfloat32m2_t acc3 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m2(k);
            
//             vfloat32m2_t vx = __riscv_vle32_v_f32m2(ptr_x, vl);
            
//             vfloat32m2_t va0 = __riscv_vle32_v_f32m2(ptr_a0, vl);
//             vfloat32m2_t va1 = __riscv_vle32_v_f32m2(ptr_a1, vl);
//             vfloat32m2_t va2 = __riscv_vle32_v_f32m2(ptr_a2, vl);
//             vfloat32m2_t va3 = __riscv_vle32_v_f32m2(ptr_a3, vl);

//             acc0 = __riscv_vfmacc_vv_f32m2_tu(acc0, va0, vx, vl);
//             acc1 = __riscv_vfmacc_vv_f32m2_tu(acc1, va1, vx, vl);
//             acc2 = __riscv_vfmacc_vv_f32m2_tu(acc2, va2, vx, vl);
//             acc3 = __riscv_vfmacc_vv_f32m2_tu(acc3, va3, vx, vl);

//             ptr_a0 += vl; ptr_a1 += vl; ptr_a2 += vl; ptr_a3 += vl;
//             ptr_x += vl;
//             k -= vl;
//         }

//         vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, 1);

//         vfloat32m1_t res0 = __riscv_vfredusum_vs_f32m2_f32m1(acc0, v_zero, vlmax);
//         vfloat32m1_t res1 = __riscv_vfredusum_vs_f32m2_f32m1(acc1, v_zero, vlmax);
//         vfloat32m1_t res2 = __riscv_vfredusum_vs_f32m2_f32m1(acc2, v_zero, vlmax);
//         vfloat32m1_t res3 = __riscv_vfredusum_vs_f32m2_f32m1(acc3, v_zero, vlmax);

//         y[i + 0] += alpha * __riscv_vfmv_f_s_f32m1_f32(res0);
//         y[i + 1] += alpha * __riscv_vfmv_f_s_f32m1_f32(res1);
//         y[i + 2] += alpha * __riscv_vfmv_f_s_f32m1_f32(res2);
//         y[i + 3] += alpha * __riscv_vfmv_f_s_f32m1_f32(res3);
//     }

//     if (i < m) {
//         size_t vlmax_m8 = __riscv_vsetvlmax_e32m8();
//         vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, 1);

//         for (; i < m; i++) {
//             const float* ptr_a = a + i * n;
//             const float* ptr_x = x;
//             size_t k = n;

//             vfloat32m8_t acc = __riscv_vfmv_v_f_f32m8(0.0f, vlmax_m8);

//             while (k > 0) {
//                 size_t vl = __riscv_vsetvl_e32m8(k);
                
//                 vfloat32m8_t row = __riscv_vle32_v_f32m8(ptr_a, vl);
//                 vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(ptr_x, vl);

//                 acc = __riscv_vfmacc_vv_f32m8_tu(acc, row, vec_x, vl);

//                 ptr_a += vl;
//                 ptr_x += vl;
//                 k -= vl;
//             }

//             vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero, vlmax_m8);
//             y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
//         }
//     }
// }

void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    size_t vlmax = __riscv_vsetvlmax_e32m4();
    vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

    size_t i = 0;

    for (; i + 2 <= m; i += 2) {
        const float* ptr_a0 = a + (i + 0) * n;
        const float* ptr_a1 = a + (i + 1) * n;
        const float* ptr_x  = x;
        size_t k = n;

        vfloat32m4_t acc0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
        vfloat32m4_t acc1 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);

        while (k > 0) {
            size_t vl = __riscv_vsetvl_e32m4(k);
            
            vfloat32m4_t vx = __riscv_vle32_v_f32m4(ptr_x, vl);
            
            vfloat32m4_t va0 = __riscv_vle32_v_f32m4(ptr_a0, vl);
            vfloat32m4_t va1 = __riscv_vle32_v_f32m4(ptr_a1, vl);

            acc0 = __riscv_vfmacc_vv_f32m4(acc0, va0, vx, vl);
            acc1 = __riscv_vfmacc_vv_f32m4(acc1, va1, vx, vl);

            ptr_a0 += vl; ptr_a1 += vl;
            ptr_x += vl;
            k -= vl;
        }

        vfloat32m1_t res0 = __riscv_vfredusum_vs_f32m4_f32m1(acc0, v_zero, vlmax);
        vfloat32m1_t res1 = __riscv_vfredusum_vs_f32m4_f32m1(acc1, v_zero, vlmax);

        y[i + 0] += alpha * __riscv_vfmv_f_s_f32m1_f32(res0);
        y[i + 1] += alpha * __riscv_vfmv_f_s_f32m1_f32(res1);
    }

    if (i < m) {
        size_t vlmax_m8 = __riscv_vsetvlmax_e32m8();

        for (; i < m; i++) {
            const float* ptr_a = a + i * n;
            const float* ptr_x = x;
            size_t k = n;

            vfloat32m8_t acc = __riscv_vfmv_v_f_f32m8(0.0f, vlmax_m8);

            while (k > 0) {
                size_t vl = __riscv_vsetvl_e32m8(k);
                vfloat32m8_t row = __riscv_vle32_v_f32m8(ptr_a, vl);
                vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(ptr_x, vl);

                acc = __riscv_vfmacc_vv_f32m8(acc, row, vec_x, vl);

                ptr_a += vl; ptr_x += vl; k -= vl;
            }

            vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero, vlmax_m8);
            y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
        }
    }
}