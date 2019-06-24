#include "cpu/instr.h"

make_instr_func(cmps_v) {
	OPERAND msi, mdi;
	msi.data_size = mdi.data_size = data_size;
	msi.type = mdi.type = OPR_MEM;
	msi.sreg = mdi.sreg = SREG_DS;
	msi.addr = cpu.gpr[REG_ESI]._32;
	mdi.addr = cpu.gpr[REG_EDI]._32;
	operand_read(&msi);
	operand_read(&mdi);
	alu_sub(mdi.val, msi.val, data_size);
	int incDec = 0;
	incDec = cpu.eflags.DF == 0 ? data_size / 8 : -data_size / 8;
	cpu.gpr[REG_ESI]._32 += incDec;
	cpu.gpr[REG_EDI]._32 += incDec;

	print_asm_0("cmps (%%edi), (%%esi)", "", 1);
	return 1;
}

make_instr_func(cmps_b) {
        OPERAND msi, mdi;
        msi.data_size = mdi.data_size = 8;
        msi.type = mdi.type = OPR_MEM;
	msi.sreg = mdi.sreg = SREG_DS;
        msi.addr = cpu.gpr[REG_ESI]._32;
        mdi.addr = cpu.gpr[REG_EDI]._32;
        operand_read(&msi);
        operand_read(&mdi);
	alu_sub(mdi.val, msi.val, data_size);
        int incDec = 0;
        incDec = cpu.eflags.DF == 0 ? 1 : -1;
        cpu.gpr[REG_ESI]._32 += incDec;
        cpu.gpr[REG_EDI]._32 += incDec;
	print_asm_0("cmps (%%edi), (%%esi)", "", 1);
	return 1;
}

