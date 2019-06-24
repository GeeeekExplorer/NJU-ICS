#include "cpu/instr.h"

#define make_group_impl(name) \
	make_instr_func(name) { \
		uint8_t op_code; \
		modrm_opcode(eip + 1, &op_code); \
		return concat(name, _entry)[op_code](eip, op_code); \
	}
#define make_group_impl_ref(name) \
	make_instr_func(name) { \
		uint8_t op_code; \
		modrm_opcode(eip + 1, &op_code); \
		return concat3(__ref_, name, _entry)[op_code](eip, op_code); \
	}

#ifdef NEMU_REF_INSTR
#define make_group_impl_cond make_group_impl_ref
#else
#define make_group_impl_cond make_group_impl
#endif

make_group_impl_cond(group_1_b);
make_group_impl_cond(group_1_v);
make_group_impl_cond(group_1_bv);
make_group_impl_cond(group_2_b);
make_group_impl_cond(group_2_v);
make_group_impl_cond(group_2_1b);
make_group_impl_cond(group_2_1v);
make_group_impl_cond(group_2_cb);
make_group_impl_cond(group_2_cv);
make_group_impl_cond(group_3_b);
make_group_impl_cond(group_3_v);
make_group_impl_cond(group_5_indirect);
make_group_impl_cond(group_7);
make_group_impl_cond(group_x87_d8);
make_group_impl_cond(group_x87_d9);
make_group_impl_cond(group_x87_da);
make_group_impl_cond(group_x87_db);
make_group_impl_cond(group_x87_dc);
make_group_impl_cond(group_x87_dd);
make_group_impl_cond(group_x87_de);
make_group_impl_cond(group_x87_df);
