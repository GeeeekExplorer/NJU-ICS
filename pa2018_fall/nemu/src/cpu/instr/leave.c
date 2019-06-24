#include "cpu/instr.h"

make_instr_func(leave) {
	cpu.esp=cpu.ebp;
	OPERAND mem;
	mem.data_size=data_size;
	mem.type=OPR_MEM;
	mem.sreg=SREG_DS;
	mem.addr=cpu.esp;
	operand_read(&mem);
	cpu.ebp=mem.val;
	cpu.esp+=data_size/8;
	return 1;
}
