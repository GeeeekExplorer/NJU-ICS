#include "cpu/instr.h"

make_instr_func(idiv_rm2a_b) {
	int len = 1;// in group
	OPERAND ax, rm;
	ax.type = OPR_REG;
	ax.data_size = 16;
	ax.addr = REG_AX;
	operand_read(&ax);

	rm.data_size = 8;
	len += modrm_rm(eip + 1, &rm);
	operand_read(&rm);
	int32_t quotient  = alu_idiv(sign_ext_64(rm.val, 8), sign_ext_64(ax.val, 16), 8);
	int32_t remainder = alu_imod(sign_ext_64(rm.val, 8), sign_ext_64(ax.val, 16));
	OPERAND ah, al;
	ah.type = al.type = OPR_REG;
	ah.data_size = al.data_size = 8;
	ah.addr = REG_AH;
	al.addr = REG_AL;
	al.val = quotient;
	ah.val = remainder;
	operand_write(&ah);
	operand_write(&al);
	print_asm_2("idiv", "b", len, &rm, &ax);
	return len;
}

make_instr_func(idiv_rm2a_v) {
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
        int32_t quotient  = 0;
	int32_t remainder = 0;
	if(data_size == 16) {
		quotient = alu_idiv(sign_ext_64(rm.val, 16), sign_ext_64((d.val << 16) | a.val, 32), data_size);
		remainder = alu_imod(sign_ext_64(rm.val, 16), sign_ext_64((d.val << 16) | a.val, 32));
		print_asm_3("idiv", "w", len, &rm, &d, &a);
	}
	else { // data_size == 32
		int64_t dividend = 0;
		dividend |= d.val;
		dividend = dividend << 32;
		dividend |= a.val;
		quotient = alu_idiv(sign_ext_64(rm.val, 32), dividend, data_size);
		remainder = alu_imod(sign_ext_64(rm.val, 32), dividend);
		print_asm_3("idiv", "l", len, &rm, &d, &a);
	}
	a.val = quotient;
	d.val = remainder;
        operand_write(&a);
        operand_write(&d);
        return len;
}
