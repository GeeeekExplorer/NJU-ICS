#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	cpu.eflags.CF = (opr_dest.val >> opr_src.val) & 0x1;
}

make_instr_impl_2op(bt, r, rm, v);
