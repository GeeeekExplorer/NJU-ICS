#ifndef __FPU_REF_H__
#define __FPU_REF_H__
#include <cpu/reg_fpu.h>
void set_ref();
uint32_t __ref_internal_float_add(uint32_t b, uint32_t a);
uint32_t __ref_internal_float_sub(uint32_t b, uint32_t a);
uint32_t __ref_internal_float_mul(uint32_t b, uint32_t a);
uint32_t __ref_internal_float_div(uint32_t b, uint32_t a);

#endif
