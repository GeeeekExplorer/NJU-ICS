#include "cpu/instr.h"

make_instr_func(lidt) {
	int len=1;
	OPERAND rel;
	len+=modrm_rm(eip+1,&rel);
	rel.data_size=16;
	operand_read(&rel);
	cpu.idtr.limit=rel.val;
	rel.addr+=2;
	rel.data_size=32;
	operand_read(&rel);
	cpu.idtr.base=rel.val;
	print_asm_1("lidt", "", len, &rel);
 	return len;
}
