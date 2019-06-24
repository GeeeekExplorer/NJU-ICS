#ifndef __INSTR_X87_H__
#define __INSTR_X87_H__

make_instr_func(x87_fldx);
make_instr_func(x87_flds);
make_instr_func(x87_fldl);
make_instr_func(x87_fstps);
make_instr_func(x87_fsts);
make_instr_func(x87_fstx);
make_instr_func(x87_fstpx);
make_instr_func(x87_fadds);
make_instr_func(x87_faddx);
make_instr_func(x87_faddlx);
make_instr_func(x87_fsubs);
make_instr_func(x87_fmuls);
make_instr_func(x87_fmullx);
make_instr_func(x87_fdivs);
make_instr_func(x87_fxch);
make_instr_func(x87_fucom);
make_instr_func(x87_fucomp);
make_instr_func(x87_fucompp);
make_instr_func(x87_fucomi);
make_instr_func(x87_fucomip);
make_instr_func(x87_fnstsw);
make_instr_func(x87_fnstcw);
make_instr_func(x87_fistpl);
make_instr_func(x87_fildl);

#endif
