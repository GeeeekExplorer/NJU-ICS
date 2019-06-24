#ifndef __ALU_REF_H__
#define __ALU_REF_H__

uint32_t __ref_alu_add(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_adc(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_sub(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_sbb(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_and(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_xor(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_or(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_shl(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_shr(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_sar(uint32_t src, uint32_t dest, size_t data_size);
uint32_t __ref_alu_sal(uint32_t src, uint32_t dest, size_t data_size);
uint64_t __ref_alu_mul(uint32_t src, uint32_t dest, size_t data_size);
int64_t  __ref_alu_imul(int32_t src, int32_t dest, size_t data_size);
uint32_t __ref_alu_div(uint64_t src, uint64_t dest, size_t data_size);
int32_t  __ref_alu_idiv(int64_t src, int64_t dest, size_t data_size);
uint32_t __ref_alu_mod(uint64_t src, uint64_t dest);
int32_t  __ref_alu_imod(int64_t src, int64_t dest);

#endif
