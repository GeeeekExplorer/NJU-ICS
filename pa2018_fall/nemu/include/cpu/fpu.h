#ifndef __FPU_H__
#define __FPU_H__

#include "cpu/cpu.h"
#include "cpu/reg_fpu.h"
#include <cpu-ref/fpu_ref.h>

extern FPU fpu;
extern CPU_STATE cpu;

#define P_ZERO_F 0X0
#define N_ZERO_F 0X80000000
#define P_INF_F 0X7f800000
#define N_INF_F 0Xff800000
#define P_NAN_F 0X7fc00000
#define N_NAN_F 0Xffc00000

typedef struct {
	uint32_t a;
	uint32_t b;
	uint32_t res;
} CORNER_CASE_RULE;

void fpu_load(uint32_t val);
uint32_t fpu_store();
uint32_t fpu_peek();
void fpu_add(uint32_t val);
void fpu_add_idx(uint32_t idx, uint32_t store_idx);
void fpu_sub(uint32_t val);
void fpu_mul(uint32_t val);
void fpu_mul_idx(uint32_t idx, uint32_t store_idx);
void fpu_div(uint32_t val);
void fpu_xch(uint32_t idx);
void fpu_copy(uint32_t idx);
void fpu_cmp(uint32_t idx);
void fpu_cmpi(uint32_t idx);

// a + b
uint32_t internal_float_add(uint32_t b, uint32_t a);
// a - b
uint32_t internal_float_sub(uint32_t b, uint32_t a);
// a * b
uint32_t internal_float_mul(uint32_t b, uint32_t a);
// a / b
uint32_t internal_float_div(uint32_t b, uint32_t a);

//void fpu_test();
#endif
