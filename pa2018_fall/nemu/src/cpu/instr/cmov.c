#include "cpu/instr.h"

static void instr_execute_2op_cc_pass() {
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

static void instr_execute_2op_cc_fail() { /*Do nothing*/ }
	
make_instr_impl_2op_cc(cmov, rm, r, v, a)
make_instr_impl_2op_cc(cmov, rm, r, v, ae)
make_instr_impl_2op_cc(cmov, rm, r, v, b)
make_instr_impl_2op_cc(cmov, rm, r, v, be)
make_instr_impl_2op_cc(cmov, rm, r, v, g)
make_instr_impl_2op_cc(cmov, rm, r, v, ge)
make_instr_impl_2op_cc(cmov, rm, r, v, l)
make_instr_impl_2op_cc(cmov, rm, r, v, le)
make_instr_impl_2op_cc(cmov, rm, r, v, ne)
make_instr_impl_2op_cc(cmov, rm, r, v, no)
make_instr_impl_2op_cc(cmov, rm, r, v, np)
make_instr_impl_2op_cc(cmov, rm, r, v, ns)
make_instr_impl_2op_cc(cmov, rm, r, v, o)
make_instr_impl_2op_cc(cmov, rm, r, v, p)
make_instr_impl_2op_cc(cmov, rm, r, v, s)
make_instr_impl_2op_cc(cmov, rm, r, v, e)
