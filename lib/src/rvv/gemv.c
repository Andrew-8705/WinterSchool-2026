#include "rvv.h"
#include <stdio.h>

// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax = __riscv_vsetvlmax_e32m8();
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

//     for (size_t i = 0; i < m; i++) {
//         const float* ptr_a = a + i * n;
//         const float* ptr_x = x;
//         size_t k = n;

//         vfloat32m8_t new_v = __riscv_vfmv_v_f_f32m8(0.0f, vlmax);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m8(k);
//             vfloat32m8_t vm = __riscv_vle32_v_f32m8(ptr_a, vl);
//             vfloat32m8_t vv = __riscv_vle32_v_f32m8(ptr_x, vl);

//             new_v = __riscv_vfmacc_vv_f32m8(new_v, vm, vv, vl);

//             ptr_a += vl;
//             ptr_x += vl; 
//             k -= vl;
//         }
        
        
//         vfloat32m1_t v_sum = __riscv_vfredusum_vs_f32m8_f32m1(new_v, v_zero, vlmax);
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

//             acc0 = __riscv_vfmacc_vv_f32m2(acc0, va0, vx, vl);
//             acc1 = __riscv_vfmacc_vv_f32m2(acc1, va1, vx, vl);
//             acc2 = __riscv_vfmacc_vv_f32m2(acc2, va2, vx, vl);
//             acc3 = __riscv_vfmacc_vv_f32m2(acc3, va3, vx, vl);

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

//                 acc = __riscv_vfmacc_vv_f32m8(acc, row, vec_x, vl);

//                 ptr_a += vl;
//                 ptr_x += vl;
//                 k -= vl;
//             }

//             vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero, vlmax_m8);
//             y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
//         }
//     }
// }

// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax = __riscv_vsetvlmax_e32m4();
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax);

//     size_t i = 0;

//     for (; i + 2 <= m; i += 2) {
//         const float* ptr_a0 = a + (i + 0) * n;
//         const float* ptr_a1 = a + (i + 1) * n;
//         const float* ptr_x  = x;
//         size_t k = n;

//         vfloat32m4_t acc0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
//         vfloat32m4_t acc1 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m4(k);
            
//             vfloat32m4_t vx = __riscv_vle32_v_f32m4(ptr_x, vl);
            
//             vfloat32m4_t va0 = __riscv_vle32_v_f32m4(ptr_a0, vl);
//             vfloat32m4_t va1 = __riscv_vle32_v_f32m4(ptr_a1, vl);

//             acc0 = __riscv_vfmacc_vv_f32m4(acc0, va0, vx, vl);
//             acc1 = __riscv_vfmacc_vv_f32m4(acc1, va1, vx, vl);

//             ptr_a0 += vl; ptr_a1 += vl;
//             ptr_x += vl;
//             k -= vl;
//         }

//         vfloat32m1_t res0 = __riscv_vfredusum_vs_f32m4_f32m1(acc0, v_zero, vlmax);
//         vfloat32m1_t res1 = __riscv_vfredusum_vs_f32m4_f32m1(acc1, v_zero, vlmax);

//         y[i + 0] += alpha * __riscv_vfmv_f_s_f32m1_f32(res0);
//         y[i + 1] += alpha * __riscv_vfmv_f_s_f32m1_f32(res1);
//     }

//     if (i < m) {
//         size_t vlmax_m8 = __riscv_vsetvlmax_e32m8();

//         for (; i < m; i++) {
//             const float* ptr_a = a + i * n;
//             const float* ptr_x = x;
//             size_t k = n;

//             vfloat32m8_t acc = __riscv_vfmv_v_f_f32m8(0.0f, vlmax_m8);

//             while (k > 0) {
//                 size_t vl = __riscv_vsetvl_e32m8(k);
//                 vfloat32m8_t row = __riscv_vle32_v_f32m8(ptr_a, vl);
//                 vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(ptr_x, vl);

//                 acc = __riscv_vfmacc_vv_f32m8(acc, row, vec_x, vl);

//                 ptr_a += vl; ptr_x += vl; k -= vl;
//             }

//             vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero, vlmax_m8);
//             y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
//         }
//     }
// }



// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax_m2 = __riscv_vsetvlmax_e32m2();
//     size_t vlmax_m1 = __riscv_vsetvlmax_e32m1();
    
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax_m1);

//     size_t i = 0;
//     for (; i + 4 <= m; i += 4) {
//         const float* ptr_a0 = a + (i + 0) * n;
//         const float* ptr_a1 = a + (i + 1) * n;
//         const float* ptr_a2 = a + (i + 2) * n;
//         const float* ptr_a3 = a + (i + 3) * n;
//         const float* ptr_x  = x;
//         size_t k = n;

//         vfloat32m2_t acc0 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax_m2);
//         vfloat32m2_t acc1 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax_m2);
//         vfloat32m2_t acc2 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax_m2);
//         vfloat32m2_t acc3 = __riscv_vfmv_v_f_f32m2(0.0f, vlmax_m2);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m2(k);
            
//             vfloat32m2_t vx = __riscv_vle32_v_f32m2(ptr_x, vl);
            
//             vfloat32m2_t va0 = __riscv_vle32_v_f32m2(ptr_a0, vl);
//             vfloat32m2_t va1 = __riscv_vle32_v_f32m2(ptr_a1, vl);
//             vfloat32m2_t va2 = __riscv_vle32_v_f32m2(ptr_a2, vl);
//             vfloat32m2_t va3 = __riscv_vle32_v_f32m2(ptr_a3, vl);

//             acc0 = __riscv_vfmacc_vv_f32m2(acc0, va0, vx, vl);
//             acc1 = __riscv_vfmacc_vv_f32m2(acc1, va1, vx, vl);
//             acc2 = __riscv_vfmacc_vv_f32m2(acc2, va2, vx, vl);
//             acc3 = __riscv_vfmacc_vv_f32m2(acc3, va3, vx, vl);

//             ptr_a0 += vl; ptr_a1 += vl; ptr_a2 += vl; ptr_a3 += vl;
//             ptr_x += vl;
//             k -= vl;
//         }

//         vfloat32m1_t l0 = __riscv_vget_v_f32m2_f32m1(acc0, 0);
//         vfloat32m1_t h0 = __riscv_vget_v_f32m2_f32m1(acc0, 1);
        
//         vfloat32m1_t l1 = __riscv_vget_v_f32m2_f32m1(acc1, 0);
//         vfloat32m1_t h1 = __riscv_vget_v_f32m2_f32m1(acc1, 1);
        
//         vfloat32m1_t l2 = __riscv_vget_v_f32m2_f32m1(acc2, 0);
//         vfloat32m1_t h2 = __riscv_vget_v_f32m2_f32m1(acc2, 1);
        
//         vfloat32m1_t l3 = __riscv_vget_v_f32m2_f32m1(acc3, 0);
//         vfloat32m1_t h3 = __riscv_vget_v_f32m2_f32m1(acc3, 1);

//         vfloat32m1_t s0 = __riscv_vfadd_vv_f32m1(l0, h0, vlmax_m1);
//         vfloat32m1_t s1 = __riscv_vfadd_vv_f32m1(l1, h1, vlmax_m1);
//         vfloat32m1_t s2 = __riscv_vfadd_vv_f32m1(l2, h2, vlmax_m1);
//         vfloat32m1_t s3 = __riscv_vfadd_vv_f32m1(l3, h3, vlmax_m1);

//         vfloat32m1_t res0 = __riscv_vfredusum_vs_f32m1_f32m1(s0, v_zero, vlmax_m1);
//         vfloat32m1_t res1 = __riscv_vfredusum_vs_f32m1_f32m1(s1, v_zero, vlmax_m1);
//         vfloat32m1_t res2 = __riscv_vfredusum_vs_f32m1_f32m1(s2, v_zero, vlmax_m1);
//         vfloat32m1_t res3 = __riscv_vfredusum_vs_f32m1_f32m1(s3, v_zero, vlmax_m1);

//         y[i + 0] += alpha * __riscv_vfmv_f_s_f32m1_f32(res0);
//         y[i + 1] += alpha * __riscv_vfmv_f_s_f32m1_f32(res1);
//         y[i + 2] += alpha * __riscv_vfmv_f_s_f32m1_f32(res2);
//         y[i + 3] += alpha * __riscv_vfmv_f_s_f32m1_f32(res3);
//     }


//     if (i < m) {
//         size_t vlmax_m8 = __riscv_vsetvlmax_e32m8();
//         vfloat32m1_t v_zero_tail = __riscv_vfmv_v_f_f32m1(0.0f, 1);

//         for (; i < m; i++) {
//             const float* ptr_a = a + i * n;const float* ptr_x = x;
//             size_t k = n;

//             vfloat32m8_t acc = __riscv_vfmv_v_f_f32m8(0.0f, vlmax_m8);

//             while (k > 0) {
//                 size_t vl = __riscv_vsetvl_e32m8(k);
//                 vfloat32m8_t row = __riscv_vle32_v_f32m8(ptr_a, vl);
//                 vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(ptr_x, vl);
//                 acc = __riscv_vfmacc_vv_f32m8(acc, row, vec_x, vl);

//                 ptr_a += vl; ptr_x += vl; k -= vl;
//             }

//             vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero_tail, vlmax_m8);
//             y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
//         }
//     }
// }

// void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     size_t vlmax_m4 = __riscv_vsetvlmax_e32m4();
//     size_t vlmax_m1 = __riscv_vsetvlmax_e32m1();
    
//     vfloat32m1_t v_zero = __riscv_vfmv_v_f_f32m1(0.0f, vlmax_m1);

//     size_t i = 0;
    
//     for (; i + 2 <= m; i += 2) {
//         const float* ptr_a0 = a + (i + 0) * n;
//         const float* ptr_a1 = a + (i + 1) * n;
//         const float* ptr_x  = x;
//         size_t k = n;

//         vfloat32m4_t acc0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax_m4);
//         vfloat32m4_t acc1 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax_m4);

//         while (k > 0) {
//             size_t vl = __riscv_vsetvl_e32m4(k);
            
//             vfloat32m4_t vx = __riscv_vle32_v_f32m4(ptr_x, vl);
            
//             vfloat32m4_t va0 = __riscv_vle32_v_f32m4(ptr_a0, vl);
//             vfloat32m4_t va1 = __riscv_vle32_v_f32m4(ptr_a1, vl);

//             acc0 = __riscv_vfmacc_vv_f32m4(acc0, va0, vx, vl);
//             acc1 = __riscv_vfmacc_vv_f32m4(acc1, va1, vx, vl);

//             ptr_a0 += vl; ptr_a1 += vl;
//             ptr_x += vl;
//             k -= vl;
//         }

//         vfloat32m1_t p0_0 = __riscv_vget_v_f32m4_f32m1(acc0, 0);
//         vfloat32m1_t p1_0 = __riscv_vget_v_f32m4_f32m1(acc0, 1);
//         vfloat32m1_t p2_0 = __riscv_vget_v_f32m4_f32m1(acc0, 2);
//         vfloat32m1_t p3_0 = __riscv_vget_v_f32m4_f32m1(acc0, 3);
        
//         vfloat32m1_t p0_1 = __riscv_vget_v_f32m4_f32m1(acc1, 0);
//         vfloat32m1_t p1_1 = __riscv_vget_v_f32m4_f32m1(acc1, 1);
//         vfloat32m1_t p2_1 = __riscv_vget_v_f32m4_f32m1(acc1, 2);
//         vfloat32m1_t p3_1 = __riscv_vget_v_f32m4_f32m1(acc1, 3);

   
//         vfloat32m1_t sum01_0 = __riscv_vfadd_vv_f32m1(p0_0, p1_0, vlmax_m1);
//         vfloat32m1_t sum23_0 = __riscv_vfadd_vv_f32m1(p2_0, p3_0, vlmax_m1);
        
//         vfloat32m1_t sum01_1 = __riscv_vfadd_vv_f32m1(p0_1, p1_1, vlmax_m1);
//         vfloat32m1_t sum23_1 = __riscv_vfadd_vv_f32m1(p2_1, p3_1, vlmax_m1);


//         vfloat32m1_t total_0 = __riscv_vfadd_vv_f32m1(sum01_0, sum23_0, vlmax_m1);
//         vfloat32m1_t total_1 = __riscv_vfadd_vv_f32m1(sum01_1, sum23_1, vlmax_m1);


//         vfloat32m1_t res0 = __riscv_vfredusum_vs_f32m1_f32m1(total_0, v_zero, vlmax_m1);
//         vfloat32m1_t res1 = __riscv_vfredusum_vs_f32m1_f32m1(total_1, v_zero, vlmax_m1);

//         y[i + 0] += alpha * __riscv_vfmv_f_s_f32m1_f32(res0);
//         y[i + 1] += alpha * __riscv_vfmv_f_s_f32m1_f32(res1);
//     }

//     if (i < m) {
//         size_t vlmax_m8 = __riscv_vsetvlmax_e32m8();
//         vfloat32m1_t v_zero_tail = __riscv_vfmv_v_f_f32m1(0.0f, 1);

//         for (; i < m; i++) {
//             const float* ptr_a = a + i * n;
//             const float* ptr_x = x;
//             size_t k = n;

//             vfloat32m8_t acc = __riscv_vfmv_v_f_f32m8(0.0f, vlmax_m8);

//             while (k > 0) {
//                 size_t vl = __riscv_vsetvl_e32m8(k);
//                 vfloat32m8_t row = __riscv_vle32_v_f32m8(ptr_a, vl);
//                 vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(ptr_x, vl);
                
//                 acc = __riscv_vfmacc_vv_f32m8(acc, row, vec_x, vl);
                
//                 ptr_a += vl; ptr_x += vl; k -= vl;
//             }

//             vfloat32m1_t res = __riscv_vfredusum_vs_f32m8_f32m1(acc, v_zero_tail, vlmax_m8);
//             y[i] += alpha * __riscv_vfmv_f_s_f32m1_f32(res);
//         }
//     }
// }


void gemv_rvv(size_t m, size_t n, float alpha, const float* a, const float* x, float* y) {
    size_t vlmax      = __riscv_vsetvlmax_e32m4();
    size_t vl_m1      = __riscv_vsetvlmax_e32m1();
    vfloat32m1_t v_z0 = __riscv_vfmv_v_f_f32m1(0.0f, vl_m1);

    for(size_t i = 0; i < (m & ~3); i += 4) {
        const float* x_ptr = x;

        vfloat32m4_t vr0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
        vfloat32m4_t vr1 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
        vfloat32m4_t vr2 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
        vfloat32m4_t vr3 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);

        const float* a0 = a;
        const float* a1 = a + n;
        const float* a2 = a + 2 * n;
        const float* a3 = a + 3 * n;

        for(size_t vl, j = n; j > 0; j -= vl, a0 += vl, a1 += vl, a2 += vl, a3 += vl, x_ptr += vl) {
            vl              = __riscv_vsetvl_e32m4(j);
            vfloat32m4_t vx = __riscv_vle32_v_f32m4(x_ptr, vl);

            vr0 = __riscv_vfmacc_vv_f32m4_tu(vr0, __riscv_vle32_v_f32m4(a0, vl), vx, vl);
            vr1 = __riscv_vfmacc_vv_f32m4_tu(vr1, __riscv_vle32_v_f32m4(a1, vl), vx, vl);
            vr2 = __riscv_vfmacc_vv_f32m4_tu(vr2, __riscv_vle32_v_f32m4(a2, vl), vx, vl);
            vr3 = __riscv_vfmacc_vv_f32m4_tu(vr3, __riscv_vle32_v_f32m4(a3, vl), vx, vl);
        }

        vfloat32m1_t v_res0_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 0), __riscv_vget_v_f32m4_f32m1(vr0, 1), vl_m1);
        vfloat32m1_t v_res1_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr1, 0), __riscv_vget_v_f32m4_f32m1(vr1, 1), vl_m1);
        vfloat32m1_t v_res2_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr2, 0), __riscv_vget_v_f32m4_f32m1(vr2, 1), vl_m1);
        vfloat32m1_t v_res3_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr3, 0), __riscv_vget_v_f32m4_f32m1(vr3, 1), vl_m1);

        vfloat32m1_t v_res0_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 2), __riscv_vget_v_f32m4_f32m1(vr0, 3), vl_m1);
        vfloat32m1_t v_res1_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr1, 2), __riscv_vget_v_f32m4_f32m1(vr1, 3), vl_m1);
        vfloat32m1_t v_res2_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr2, 2), __riscv_vget_v_f32m4_f32m1(vr2, 3), vl_m1);
        vfloat32m1_t v_res3_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr3, 2), __riscv_vget_v_f32m4_f32m1(vr3, 3), vl_m1);

        vfloat32m1_t v_res0 = __riscv_vfadd_vv_f32m1(v_res0_lo, v_res0_hi, vl_m1);
        vfloat32m1_t v_res1 = __riscv_vfadd_vv_f32m1(v_res1_lo, v_res1_hi, vl_m1);
        vfloat32m1_t v_res2 = __riscv_vfadd_vv_f32m1(v_res2_lo, v_res2_hi, vl_m1);
        vfloat32m1_t v_res3 = __riscv_vfadd_vv_f32m1(v_res3_lo, v_res3_hi, vl_m1);

        v_res0 = __riscv_vfredusum_vs_f32m1_f32m1(v_res0, v_z0, vl_m1);
        v_res1 = __riscv_vfredusum_vs_f32m1_f32m1(v_res1, v_z0, vl_m1);
        v_res2 = __riscv_vfredusum_vs_f32m1_f32m1(v_res2, v_z0, vl_m1);
        v_res3 = __riscv_vfredusum_vs_f32m1_f32m1(v_res3, v_z0, vl_m1);

        *(y) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res0);
        *(y + 1) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res1);
        *(y + 2) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res2);
        *(y + 3) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res3);

        y += 4;
        a += 4 * n;
    }
    if(m & 2) {
        const float* x_ptr = x;

        vfloat32m4_t vr0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);
        vfloat32m4_t vr1 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);

        const float* a0 = a;
        const float* a1 = a + n;

        for(size_t vl, j = n; j > 0; j -= vl, a0 += vl, a1 += vl, x_ptr += vl) {
            vl              = __riscv_vsetvl_e32m4(j);
            vfloat32m4_t vx = __riscv_vle32_v_f32m4(x_ptr, vl);

            vr0 = __riscv_vfmacc_vv_f32m4_tu(vr0, __riscv_vle32_v_f32m4(a0, vl), vx, vl);
            vr1 = __riscv_vfmacc_vv_f32m4_tu(vr1, __riscv_vle32_v_f32m4(a1, vl), vx, vl);
        }
        vfloat32m1_t v_res0_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 0), __riscv_vget_v_f32m4_f32m1(vr0, 1), vl_m1);
        vfloat32m1_t v_res1_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr1, 0), __riscv_vget_v_f32m4_f32m1(vr1, 1), vl_m1);

        vfloat32m1_t v_res0_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 2), __riscv_vget_v_f32m4_f32m1(vr0, 3), vl_m1);
        vfloat32m1_t v_res1_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr1, 2), __riscv_vget_v_f32m4_f32m1(vr1, 3), vl_m1);

        vfloat32m1_t v_res0 = __riscv_vfadd_vv_f32m1(v_res0_lo, v_res0_hi, vl_m1);
        vfloat32m1_t v_res1 = __riscv_vfadd_vv_f32m1(v_res1_lo, v_res1_hi, vl_m1);

        v_res0 = __riscv_vfredusum_vs_f32m1_f32m1(v_res0, v_z0, vl_m1);
        v_res1 = __riscv_vfredusum_vs_f32m1_f32m1(v_res1, v_z0, vl_m1);

        *(y) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res0);
        *(y + 1) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res1);

        y += 2;
        a += 2 * n;
    }
    if(m & 1) {
        const float* x_ptr = x;

        vfloat32m4_t vr0 = __riscv_vfmv_v_f_f32m4(0.0f, vlmax);

        const float* a0 = a;

        for(size_t vl, j = n; j > 0; j -= vl, a0 += vl, x_ptr += vl) {
            vl              = __riscv_vsetvl_e32m4(j);
            vfloat32m4_t vx = __riscv_vle32_v_f32m4(x_ptr, vl);

            vr0 = __riscv_vfmacc_vv_f32m4_tu(vr0, __riscv_vle32_v_f32m4(a0, vl), vx, vl);
        }

        vfloat32m1_t v_res0_lo =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 0), __riscv_vget_v_f32m4_f32m1(vr0, 1), vl_m1);
        vfloat32m1_t v_res0_hi =
            __riscv_vfadd_vv_f32m1(__riscv_vget_v_f32m4_f32m1(vr0, 2), __riscv_vget_v_f32m4_f32m1(vr0, 3), vl_m1);
        vfloat32m1_t v_res0 = __riscv_vfadd_vv_f32m1(v_res0_lo, v_res0_hi, vl_m1);

        v_res0 = __riscv_vfredusum_vs_f32m1_f32m1(v_res0, v_z0, vl_m1);

        *(y) += alpha * __riscv_vfmv_f_s_f32m1_f32(v_res0);
    }
}