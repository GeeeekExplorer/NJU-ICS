#include "cpu/instr.h"

make_instr_func(rep_repe) {
	int len = 1;
	uint8_t op = instr_fetch(eip + 1, 1);
	print_asm_0("rep", "", len + 1);
	if(op == 0xc3) {
		// reference http://repzret.org/p/repzret/
		opcode_entry[op](eip + 1, op);
		return 0;
	}
	while(cpu.gpr[REG_ECX]._32 != 0) {
		opcode_entry[op](eip + 1, op);
		cpu.gpr[REG_ECX]._32 --;
		/**/
		if((op == 0xA6 || op == 0xA7 || op == 0xAE || op == 0xAF) && cpu.eflags.ZF == 1) {
			break;
		}
	}
	return len + 1;
}
