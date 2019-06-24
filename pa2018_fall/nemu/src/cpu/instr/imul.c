#include "cpu/instr.h"

make_instr_func(imul_rm2r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = data_size;
	len += modrm_r_rm(eip + 1, &r, &rm);
	operand_read(&r);
	operand_read(&rm);
	r.val = alu_imul(sign_ext(rm.val, data_size), sign_ext(r.val, data_size), data_size);
	operand_write(&r);

	print_asm_2("imul", "b", len, &rm, &r);
	return len;
}

make_instr_func(imul_rm2a_b) {
        int len = 1; // in group
        OPERAND al, rm;
        al.data_size = 8;
	al.type = OPR_REG;
	al.addr = REG_AL;
        rm.data_size = 8;
        len += modrm_rm(eip + 1, &rm);
        operand_read(&al);
        operand_read(&rm);
        uint32_t res = alu_imul(sign_ext(rm.val, 8), sign_ext(al.val, 8), 8);
	OPERAND ax;
	ax.data_size = 16;
	ax.type = OPR_REG;
	ax.addr = REG_AX;
	ax.val = res;
        operand_write(&ax);
	print_asm_3("imul", "b", len, &rm, &al, &ax);
        return len;
}

make_instr_func(imul_rm2a_v) {
        int len = 1; // in group
        OPERAND a, rm;
        a.data_size = data_size;
        a.type = OPR_REG;
        a.addr = REG_EAX;
        rm.data_size = data_size;
        len += modrm_rm(eip + 1, &rm);
        operand_read(&a);
        operand_read(&rm);
       	OPERAND ax, dx;
       	dx.type = ax.type = OPR_REG;
	ax.addr = REG_AX;
	dx.addr = REG_DX;
	if(data_size == 16) {
	        int32_t res = alu_imul(sign_ext(rm.val, 16), sign_ext(a.val, 16), 16);
	        dx.data_size = ax.data_size = 16;
        	ax.val = res & 0xffff;
		dx.val = (res >> 16) & 0xffff; 
		print_asm_3("imul", "w", len, &rm, &dx, &ax);
	} else { // data_size == 32
		int64_t res = alu_imul(sign_ext(rm.val, 32), sign_ext(a.val, 32), 32);
		dx.data_size = ax.data_size = 32;
		ax.val = res & 0xffffffff;
		dx.val = (res >> 32) & 0xffffffff;
		print_asm_3("imul", "l", len, &rm, &dx, &ax);
	}
        operand_write(&ax);
	operand_write(&dx);
        return len;
}

make_instr_func(imul_irm2r_v) {
	int len = 1;
	OPERAND r, rm, imm;
	r.data_size = data_size;
	rm.data_size = data_size;
	len += modrm_r_rm(eip + 1, &r, &rm);
	imm.type = OPR_IMM;
	imm.data_size = data_size;
	imm.addr = eip + len;
	operand_read(&rm);
	operand_read(&imm);
	r.val = alu_imul(sign_ext(imm.val, data_size), sign_ext(rm.val, data_size), data_size);
	operand_write(&r);
	print_asm_3("imul", "l", len + data_size / 8, &imm, &rm, &r);
	return len + data_size / 8;
}

make_instr_func(imul_i8rm2r_v) {
        int len = 1;
        OPERAND r, rm, imm;
        r.data_size = data_size;
        rm.data_size = data_size;
        len += modrm_r_rm(eip + 1, &r, &rm);
        imm.type = OPR_IMM;
        imm.data_size = 8;
        imm.addr = eip + len;
        operand_read(&rm);
        operand_read(&imm);
        r.val = alu_imul(sign_ext(imm.val, 8), sign_ext(rm.val, data_size), data_size);
        operand_write(&r);
	print_asm_3("imul", data_size == 16 ? "w" : "l", len + 1, &imm, &rm, &r);
        return len + 1;
}

