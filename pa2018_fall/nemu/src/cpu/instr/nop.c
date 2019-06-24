#include "cpu/instr.h"

make_instr_func(nop) {
	print_asm_0("nop", "", 1);
	return 1;
}
