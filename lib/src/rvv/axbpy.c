#include "rvv.h"

void axpby_rvv(size_t n, float alpha, const float* x, float beta, float* y)
{
    vfloat32m8_t vx, vy;

    for(size_t vl; n > 0; n -= vl, x += vl, y += vl) {
        vl = __riscv_vsetvl_e32m8(n);
        vx = __riscv_vle32_v_f32m8(x, vl);
        vy = __riscv_vle32_v_f32m8(y, vl);
        vy = __riscv_vfmul_vf_f32m8(vy, beta, vl);
        vy = __riscv_vfmacc_vf_f32m8(vy, alpha, vx, vl);
        __riscv_vse32_v_f32m8(y, vy, vl);
    }
}
