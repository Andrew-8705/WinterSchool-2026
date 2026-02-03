#include "rvv.h"

void fabsf_rvv(const float* src, float* dst, size_t n)
{
    uint32_t mask = 0x7fffffff;

    for(size_t vl; n > 0; n -= vl, src += vl, dst += vl) {
        vl = __riscv_vsetvl_e32m8(n);
        vfloat32m8_t vs = __riscv_vle32_v_f32m8(src, vl);
        vuint32m8_t vu = __riscv_vreinterpret_v_f32m8_u32m8(vs);
        vuint32m8_t res = __riscv_vand_vx_u32m8(vu, mask, vl);
        vfloat32m8_t v_res =  __riscv_vreinterpret_v_u32m8_f32m8(res);
        __riscv_vse32_v_f32m8(dst, v_res, vl);
    }
}
