#include "cpu/instr.h"

make_instr_func(jmp_near) {
    OPERAND rel;
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;
    operand_read(&rel);
	print_asm_1("jmp", "", 2, &rel);
	cpu.eip += sign_ext(rel.val, data_size);
    return 1 + data_size / 8;
}

make_instr_func(jmp_near_indirect) {
	int len = 1;
	OPERAND rel;
	rel.data_size = data_size;
	len += modrm_rm(eip + 1, &rel);
	operand_read(&rel);
	print_asm_1("jmp", "", len, &rel);
	if(data_size == 16)
		cpu.eip = rel.val & 0xFFFF;
	else
		cpu.eip = rel.val;
	return 0;
}

make_instr_func(jmp_short) {
	OPERAND rel;
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;
    operand_read(&rel);
	print_asm_1("jmp", "", 2, &rel);
	cpu.eip += sign_ext(rel.val, rel.data_size);
    return 2;
}

make_instr_func(jmp_far_imm) {
	OPERAND rel;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = 32;
    rel.addr = eip + 1;
	operand_read(&rel);
	print_asm_1("jmp", "", 7, &rel);
	if(data_size == 16)
		cpu.eip = rel.val & 0xFFFF;
	else
		cpu.eip = rel.val;
	cpu.cs.val = instr_fetch(eip + 5, 2);
	load_sreg(1);
    return 0;
}
