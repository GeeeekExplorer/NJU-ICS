#include "cpu/instr.h"

make_instr_func(mul_rm2a_b) {
        int len = 1; // in group
        OPERAND al, rm;
        al.data_size = 8;
        al.type = OPR_REG;
        al.addr = REG_AL;
        rm.data_size = 8;
        len += modrm_rm(eip + 1, &rm);
        operand_read(&al);
        operand_read(&rm);
	// zero extent
        uint32_t res = alu_mul(rm.val, al.val, 8);
        OPERAND ax;
        ax.data_size = 16;
        ax.type = OPR_REG;
        ax.addr = REG_AX;
        ax.val = res;
        operand_write(&ax);
	if(((res >> 8) & 0xff) == 0) {
		cpu.eflags.CF = cpu.eflags.OF = 0;
	} else {
		cpu.eflags.CF = cpu.eflags.OF = 1;
	}
	print_asm_2("mul", "b", len, &rm, &al);
        return len;

}

make_instr_func(mul_rm2a_v) {
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
                uint32_t res = alu_mul(rm.val, a.val, 16);
                dx.data_size = ax.data_size = 16;
                ax.val = res & 0xffff;
                dx.val = (res >> 16) & 0xffff;
		print_asm_3("mul", "w", len, &rm, &dx, &ax);
        } else { // data_size == 32
                uint64_t res = alu_mul(rm.val, a.val, 32);
                dx.data_size = ax.data_size = 32;
                ax.val = res & 0xffffffff;
                dx.val = (res >> 32) & 0xffffffff;
		print_asm_3("mul", "l", len, &rm, &dx, &ax);
        }
        operand_write(&ax);
        operand_write(&dx);
	if(dx.val == 0) {
		cpu.eflags.CF = cpu.eflags.OF = 0;
	} else {
		cpu.eflags.CF = cpu.eflags.OF = 1;
	}
        return len;

}
