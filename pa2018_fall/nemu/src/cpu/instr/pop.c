#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.type=OPR_MEM;
	opr_dest.sreg=SREG_DS;
	opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);
	opr_src.val=opr_dest.val;
	operand_write(&opr_src);
	cpu.esp+=32/8;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, i, b)
make_instr_impl_1op(pop, i, v)

make_instr_func(popa) {
	print_asm_0("popa", "", 1);
	opr_src.data_size=32;
	opr_src.type=OPR_MEM;
	opr_src.sreg=SREG_DS;

	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.edi=opr_src.val;
	cpu.esp+=32/8;

	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.esi=opr_src.val;
	cpu.esp+=32/8;
	
	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.ebp=opr_src.val;
	cpu.esp+=32/8;
	
	cpu.esp+=32/8;
	
	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.ebx=opr_src.val;
	cpu.esp+=32/8;

	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.edx=opr_src.val;
	cpu.esp+=32/8;

	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.ecx=opr_src.val;
	cpu.esp+=32/8;

	opr_src.addr=cpu.esp;
	operand_read(&opr_src);
	cpu.eax=opr_src.val;
	cpu.esp+=32/8;

	return 1;
}
