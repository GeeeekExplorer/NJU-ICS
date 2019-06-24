#include "cpu/instr.h"

make_instr_func(lgdt) {
	int len=1;
	OPERAND rel;
	len+=modrm_rm(eip+1,&rel);
	//printf("addr:%x",rel.addr);
	rel.data_size=16;
	operand_read(&rel);
	cpu.gdtr.limit=rel.val;
	//printf("limit:%x\n",rel.val);
	rel.addr+=2;
	rel.data_size=32;
	operand_read(&rel);
	//printf("base:%x\n",rel.val);
	cpu.gdtr.base=rel.val;
	//printf("len:%x\n",len);
	print_asm_1("lgdt", "", len, &rel);
 	return len;
}
