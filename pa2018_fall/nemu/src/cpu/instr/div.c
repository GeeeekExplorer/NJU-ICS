#include "cpu/instr.h"

make_instr_func(div_rm2a_b) {
	int len = 1;// in group
	OPERAND ax, rm;
	ax.type = OPR_REG;
	ax.data_size = 16;
	ax.addr = REG_AX;
	operand_read(&ax);

	rm.data_size = 8;
	len += modrm_rm(eip + 1, &rm);
	operand_read(&rm);
	uint32_t quotient  = alu_div(rm.val, ax.val, 8);
	uint32_t remainder = alu_mod(rm.val, ax.val);
	OPERAND ah, al;
	ah.type = al.type = OPR_REG;
	ah.data_size = al.data_size = 8;
	ah.addr = REG_AH;
	al.addr = REG_AL;
	al.val = quotient;
	ah.val = remainder;
	operand_write(&ah);
	operand_write(&al);


	print_asm_2("div", "b", len, &rm, &ax);
	return len;
}

make_instr_func(div_rm2a_v) {
        int len = 1;// in group
        OPERAND a, d, rm;
        d.type = a.type = OPR_REG;
        d.data_size = a.data_size = data_size;
        a.addr = REG_EAX;
	d.addr = REG_EDX;
        operand_read(&a);
	operand_read(&d);

        rm.data_size = data_size;
        len += modrm_rm(eip + 1, &rm);
        operand_read(&rm);
        uint32_t quotient  = 0;
	uint32_t remainder = 0;
	if(data_size == 16) {
		quotient = alu_div(rm.val, (d.val << 16) | a.val, data_size);
		remainder = alu_mod(rm.val, (d.val << 16) | a.val);
		print_asm_3("div", "w", len, &rm, &d, &a);
	}
	else { // data_size == 32
		uint64_t dividend = 0;
		dividend |= d.val;
		dividend = dividend << 32;
		dividend |= a.val;
		quotient = alu_div(rm.val, dividend, data_size);
		remainder = alu_mod(rm.val, dividend);
		print_asm_3("div", "l", len, &rm, &d, &a);
	}
	a.val = quotient;
	d.val = remainder;
        operand_write(&a);
        operand_write(&d);
        return len;
}
