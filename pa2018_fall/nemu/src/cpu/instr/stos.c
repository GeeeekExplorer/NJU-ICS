#include "cpu/instr.h"

make_instr_func(stos_b) {
	OPERAND al, mdi;
	al.type = OPR_REG;
	al.data_size = 8;
	al.addr = REG_AL;

	mdi.type = OPR_MEM;
	mdi.sreg = SREG_ES;
	mdi.data_size = 8;
	mdi.addr = cpu.gpr[REG_EDI]._32;

	operand_read(&al);
	mdi.val = al.val;
	int incDec = 0;
        incDec = cpu.eflags.DF == 0 ? 1 : -1;
        cpu.gpr[REG_EDI]._32 += incDec;
	operand_write(&mdi);
	print_asm_0("stos", "", 1);
	return 1;
}

make_instr_func(stos_v) {
        OPERAND al, mdi;
        al.type = OPR_REG;
        al.data_size = data_size;
        al.addr = REG_AX;

        mdi.type = OPR_MEM;
	mdi.sreg = SREG_ES;
        mdi.data_size = data_size;
        mdi.addr = cpu.gpr[REG_EDI]._32;

        operand_read(&al);
        mdi.val = al.val;
        int incDec = 0;
        incDec = cpu.eflags.DF == 0 ? data_size / 8 : -data_size / 8;
        cpu.gpr[REG_EDI]._32 += incDec;
        operand_write(&mdi);
	print_asm_0("stos", "", 1);
	return 1;
}

