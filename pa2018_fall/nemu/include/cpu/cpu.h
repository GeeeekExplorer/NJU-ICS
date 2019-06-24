#ifndef __CPU_H__
#define __CPU_H__

// interface for cpu functions

#include "nemu.h"
#include "cpu/reg.h"
#include "cpu/alu.h"
#include "cpu/reg_fpu.h"

extern CPU_STATE cpu;

// initialize the cpu states
void init_cpu();

// execute n instructions starting from the current eip
// change eip according to the length of the instruction in each step
void exec(uint32_t n);

// execute an instruction pointed by the current eip
// return the length of the instruction
int exec_inst();

void set_CF_add(uint32_t result,uint32_t src,size_t data_size);
void set_CF_adc(uint32_t result,uint32_t src,size_t data_size);
void set_CF_sub(uint32_t result,uint32_t src,size_t data_size);
void set_CF_sbb(uint32_t result,uint32_t src,size_t data_size);

void set_ZF(uint32_t result,size_t data_size);

void set_SF(uint32_t result,size_t data_size);

void set_PF(uint32_t result);

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);
void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);

#endif
