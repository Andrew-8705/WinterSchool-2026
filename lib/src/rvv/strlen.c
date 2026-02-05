#include "rvv.h"

// LMUL = 8
// size_t strlen_rvv(const char *str)
// {
//    const char* ptr = str;
//    size_t vl;

//    size_t vlmax = __riscv_vsetvlmax_e8m8();

//    while (1) {
//       vuint8m8_t vec = __riscv_vle8ff_v_u8m8((const uint8_t*)ptr, &vl, vlmax);
//       vbool1_t zero_mask = __riscv_vmseq_vx_u8m8_b1(vec, 0, vl);
//       long f_zero = __riscv_vfirst_m_b1(zero_mask, vl);

//       if (f_zero >= 0) {
//          return (size_t)(ptr - str) + f_zero;
//       }

//       ptr += vl;
//    }
// }

// // LMUL = 4
// size_t strlen_rvv(const char *str)
// {
//    const char* ptr = str;
//    size_t vl;
//    size_t vlmax = __riscv_vsetvlmax_e8m4();

//    while (1) {
//       vuint8m4_t vec = __riscv_vle8ff_v_u8m4((const uint8_t*)ptr, &vl, vlmax);

//       vbool2_t zero_mask = __riscv_vmseq_vx_u8m4_b2(vec, 0, vl);
      
//       long f_zero = __riscv_vfirst_m_b2(zero_mask, vl);

//       if (f_zero >= 0) {
//          return (size_t)(ptr - str) + f_zero;
//       }

//       ptr += vl;
//    }
// }

// // LMUL = 2
// size_t strlen_rvv(const char *str)
// {
//    const char* ptr = str;
//    size_t vl;
   
//    size_t vlmax = __riscv_vsetvlmax_e8m2();

//    while (1) {
//       vuint8m2_t vec = __riscv_vle8ff_v_u8m2((const uint8_t*)ptr, &vl, vlmax);

//       vbool4_t zero_mask = __riscv_vmseq_vx_u8m2_b4(vec, 0, vl);
      
//       long f_zero = __riscv_vfirst_m_b4(zero_mask, vl);

//       if (f_zero >= 0) {
//          return (size_t)(ptr - str) + f_zero;
//       }

//       ptr += vl;
//    }
// }

// LMUL = 1
size_t strlen_rvv(const char *str)
{
   const char* ptr = str;
   size_t vl;
   size_t vlmax = __riscv_vsetvlmax_e8m1();

   while (1) {
      vuint8m1_t vec = __riscv_vle8ff_v_u8m1((const uint8_t*)ptr, &vl, vlmax);
      vbool8_t zero_mask = __riscv_vmseq_vx_u8m1_b8(vec, 0, vl);
      
      long f_zero = __riscv_vfirst_m_b8(zero_mask, vl);

      if (f_zero >= 0) {
         return (size_t)(ptr - str) + f_zero;
      }

      ptr += vl;
   }
}