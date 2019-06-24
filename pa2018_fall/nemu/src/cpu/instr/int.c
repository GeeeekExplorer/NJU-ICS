#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_) {
	OPERAND rel;
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;
    operand_read(&rel);
	print_asm_1("int", "", 2, &rel);
	raise_sw_intr(rel.val);
	return 0;
}
