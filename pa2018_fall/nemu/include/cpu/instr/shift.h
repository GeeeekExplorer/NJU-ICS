#ifndef __INSTR_SHIFT_H__
#define __INSTR_SHIFT_H__

make_instr_func(shl_i2rm_bv);
make_instr_func(shl_i2rm_b);
make_instr_func(shl_rm_v);
make_instr_func(shl_rm_b);
make_instr_func(shl_c2rm_bv);
make_instr_func(shl_c2rm_b);

make_instr_func(shr_i2rm_bv);
make_instr_func(shr_i2rm_b);
make_instr_func(shr_rm_v);
make_instr_func(shr_rm_b);
make_instr_func(shr_c2rm_bv);
make_instr_func(shr_c2rm_b);

make_instr_func(sar_i2rm_bv);
make_instr_func(sar_i2rm_b);
make_instr_func(sar_rm_v);
make_instr_func(sar_rm_b);
make_instr_func(sar_c2rm_bv);
make_instr_func(sar_c2rm_b);

#endif
