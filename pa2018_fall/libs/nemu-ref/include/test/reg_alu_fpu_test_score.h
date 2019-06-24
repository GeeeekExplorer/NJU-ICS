#ifndef __REG_ALU_FPU_TEST_SCORE_H__
#define __REG_ALU_FPU_TEST_SCORE_H__

// test for registers
void __score_reg_test();

// test for alu
void __score_alu_test_add();
void __score_alu_test_adc();
void __score_alu_test_sub();
void __score_alu_test_sbb();
void __score_alu_test_and();
void __score_alu_test_or();
void __score_alu_test_xor();
void __score_alu_test_shl();
void __score_alu_test_shr();
void __score_alu_test_sal();
void __score_alu_test_sar();
void __score_alu_test_mul();
void __score_alu_test_div();
void __score_alu_test_imul();
void __score_alu_test_idiv();

// test for fpu

void __score_init_fpu_test();
void __score_fpu_test_add();
void __score_fpu_test_sub();
void __score_fpu_test_mul();
void __score_fpu_test_div();

#endif
