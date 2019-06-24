#include "cpu/instr.h"

extern uint8_t data_size;

make_instr_func(data_size_16) {
	uint8_t op_code = 0;
	int len = 0;
	data_size = 16;
	op_code = instr_fetch(eip + 1, 1);
#ifdef NEMU_REF_INSTR
	len = __ref_opcode_entry[op_code](eip + 1, op_code);
#else
	len = opcode_entry[op_code](eip + 1, op_code);
#endif
	data_size = 32;
	return 1 + len;
}
