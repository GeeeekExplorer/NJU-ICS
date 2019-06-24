#ifndef __REG_ALU_FPU_TEST_H__
#define __REG_ALU_FPU_TEST_H__

// test for registers
void reg_test();

// test for alu
void alu_test_add();
void alu_test_adc();
void alu_test_sub();
void alu_test_sbb();
void alu_test_and();
void alu_test_or();
void alu_test_xor();
void alu_test_shl();
void alu_test_shr();
void alu_test_sal();
void alu_test_sar();
void alu_test_mul();
void alu_test_div();
void alu_test_imul();
void alu_test_idiv();

// test for fpu

void init_fpu_test();
void fpu_test_add();
void fpu_test_sub();
void fpu_test_mul();
void fpu_test_div();

#endif
