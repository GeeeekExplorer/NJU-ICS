#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	if(opr_src.data_size == 16) {
		opr_src.val = sign_ext(opr_src.val, 8);
	} else {
		opr_src.val = sign_ext(opr_src.val, 16);
	}
	operand_write(&opr_src);
}

make_instr_impl_1op(cbw, a, v);
