#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	opr_dest.val = alu_sbb(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sbb, r, rm, b)
make_instr_impl_2op(sbb, r, rm, v)
make_instr_impl_2op(sbb, rm, r, b)
make_instr_impl_2op(sbb, rm, r, v)
make_instr_impl_2op(sbb, i, a, b)
make_instr_impl_2op(sbb, i, a, v)
make_instr_impl_2op(sbb, i, rm, b)
make_instr_impl_2op(sbb, i, rm, v)
make_instr_impl_2op(sbb, i, rm, bv)
