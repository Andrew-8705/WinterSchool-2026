#include "rvv.h"

size_t strlen_rvv(const char *str)
{
   const char* ptr = str;
   size_t vl;

   size_t vlmax = __riscv_vsetvlmax_e8m8();

   while (1) {
      vuint8m8_t vec = __riscv_vle8ff_v_u8m8((const uint8_t*)ptr, &vl, vlmax);
      vbool1_t zero_mask = __riscv_vmseq_vx_u8m8_b1(vec, 0, vl);
      long f_zero = __riscv_vfirst_m_b1(zero_mask, vl);

      if (f_zero >= 0) {
         return (size_t)(ptr - str) + f_zero;
      }

      ptr += vl;
   }
}