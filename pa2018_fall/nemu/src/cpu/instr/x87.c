#include "cpu/instr.h"

// reference: http://www.felixcloutier.com/x86/

static uint32_t f2u(float val) {
	uint32_t *temp = (uint32_t *)&val;
	return *temp;
}

static float u2f(uint32_t val) {
	float *temp = (float *)&val;
	return *temp;
}

typedef union {
	double dval;
	uint32_t uval[2];
}DOUBLE;


make_instr_func(x87_fldl) {
	int len = 1;
	DOUBLE temp;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	temp.uval[0] = opr_src.val;
	opr_src.addr += 4;
	operand_read(&opr_src);
	temp.uval[1] = opr_src.val;
	print_asm_0("fldl", "", len);
	fpu_load(f2u((float)temp.dval));
	return len;
}

make_instr_func(x87_flds) {
	int len = 1;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	print_asm_0("flds", "", len);
	fpu_load(opr_src.val);
	return len;
}


make_instr_func(x87_fildl) {
	int len = 1;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	fpu_load(f2u((float)((int)opr_src.val)));
	print_asm_0("fildl", "", len);
	return len;
}

make_instr_func(x87_fldx) {
	int len = 2;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xE8:
		fpu_load(f2u(1.0)); break;
	case 0xE9:
		assert(0); break;
	case 0xEA:
		assert(0); break;
	case 0xEB:
		assert(0); break;
	case 0xEC:
		assert(0); break;
	case 0xED:
		assert(0); break;
	case 0xEE:
		fpu_load(f2u(0.0)); break;
	default: // fldcw
		len = 1;
		opr_dest.data_size = 16;
		len += modrm_rm(eip + 1, &opr_dest);
		operand_read(&opr_dest);
		fpu.control.val = opr_dest.val;
		print_asm_0("fldcw", "", len);
		break;
	}
	return len;
}

make_instr_func(x87_fadds) {
	int len = 1;
	uint32_t idx;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xC0:
	case 0xC1:
	case 0xC2:
	case 0xC3:
	case 0xC4:
	case 0xC5:
	case 0xC6:
	case 0xC7:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_add_idx(idx, 0);
		len ++;
		break;
	default: //fadds m32fp
		opr_src.data_size = 32;
		len += modrm_rm(eip + 1, &opr_src);
		operand_read(&opr_src);
		fpu_add(opr_src.val);
	}
	print_asm_0("fadds", "", len);
	return len;
}

make_instr_func(x87_faddx) {
	int len = 1;
	uint32_t idx;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xC0:
	case 0xC1:
	case 0xC2:
	case 0xC3:
	case 0xC4:
	case 0xC5:
	case 0xC6:
	case 0xC7:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_add_idx(idx, idx);
		fpu_store();
		len ++;
		break;
	default: //fiadd m16int
		opr_src.data_size = 16;
		len += modrm_rm(eip + 1, &opr_src);
		operand_read(&opr_src);
		fpu_add(f2u((float)((int) opr_src.val)));
	}
	print_asm_0("fadd", "", len);
	return len;
}

make_instr_func(x87_faddlx) {
	int len = 1;
	uint32_t idx;
	DOUBLE temp;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xC0:
	case 0xC1:
	case 0xC2:
	case 0xC3:
	case 0xC4:
	case 0xC5:
	case 0xC6:
	case 0xC7:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_add_idx(idx, idx);
		len ++;
		break;
	default: //faddl
		opr_src.data_size = 32;
		len += modrm_rm(eip + 1, &opr_src);
		operand_read(&opr_src);
		temp.uval[0] = opr_src.val;
		opr_src.addr += 4;
		operand_read(&opr_src);
		temp.uval[1] = opr_src.val;
		fpu_add(f2u((float)(temp.dval)));
	}
	print_asm_0("faddl", "", len);
	return len;
}

make_instr_func(x87_fsubs) {
	int len = 1;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	fpu_sub(opr_src.val);
	print_asm_0("fsubs", "", len);
	return len;
}

make_instr_func(x87_fmuls) {
	int len = 1;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	fpu_mul(opr_src.val);
	print_asm_0("fmuls", "", len);
	return len;
}

make_instr_func(x87_fmullx) {
	int len = 1;
	uint32_t idx;
	DOUBLE temp;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xC8:
	case 0xC9:
	case 0xCA:
	case 0xCB:
	case 0xCC:
	case 0xCD:
	case 0xCE:
	case 0xCF:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_mul_idx(idx, idx);
		len ++;
		break;
	default: //fmul m64fp
		opr_src.data_size = 32;
		len += modrm_rm(eip + 1, &opr_src);
		operand_read(&opr_src);
		temp.uval[0] = opr_src.val;
		opr_src.addr += 4;
		operand_read(&opr_src);
		temp.uval[1] = opr_src.val;
		fpu_mul(f2u((float)(temp.dval)));
	}
	print_asm_0("fmull", "", len);
	return len;
}

make_instr_func(x87_fdivs) {
	int len = 1;
	opr_src.data_size = 32;
	len += modrm_rm(eip + 1, &opr_src);
	operand_read(&opr_src);
	fpu_div(opr_src.val);
	print_asm_0("fdivs", "", len);
	return len;
}

make_instr_func(x87_fstps) {
	int len = 1;
	opr_dest.data_size = 32;
	len += modrm_rm(eip + 1, &opr_dest);
	opr_dest.val = fpu_store();
	operand_write(&opr_dest);
	print_asm_0("fstps", "", len);
	return len;
}

make_instr_func(x87_fxch) {
	uint32_t idx = instr_fetch(eip + 1, 1) & 0x7;
	fpu_xch(idx);
	print_asm_0("fxch", "", 2);
	return 2;
}

make_instr_func(x87_fucompp) {
	fpu_cmp(1);
	fpu_store();
	fpu_store();
	print_asm_0("fucompp", "", 2);
	return 2;
}

make_instr_func(x87_fnstsw) {
	cpu.gpr[0]._16 = fpu.status.val;
	print_asm_0("fnstsw", "", 2);
	return 2;
}

make_instr_func(x87_fstpx) {
	int len = 1;
	uint32_t idx;
	DOUBLE temp;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xD8: 
	case 0xD9:
	case 0xDA:
	case 0xDB:
	case 0xDC:
	case 0xDD:
	case 0xDE:
	case 0xDF:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_copy(idx);
		fpu_store();
		len ++;
		break;
	default: // fstpl
		opr_dest.data_size = 32; 
		len += modrm_rm(eip + 1, &opr_dest);
		temp.dval = (double)u2f(fpu_store());
		opr_dest.val = temp.uval[0];
		operand_write(&opr_dest);
		opr_dest.addr += 4;
		opr_dest.val = temp.uval[1];
		operand_write(&opr_dest);
	}
	print_asm_0("fstp", "", len);
	return len;
}

make_instr_func(x87_fstx) {
	int len = 1;
	uint32_t idx;
	DOUBLE temp;
	switch(instr_fetch(eip + 1, 1)) {
	case 0xD0:
	case 0xD1:
	case 0xD2:
	case 0xD3:
	case 0xD4:
	case 0xD5:
	case 0xD6:
	case 0xD7:
		idx = instr_fetch(eip + 1, 1) & 0x7;
		fpu_copy(idx);
		len ++;
		break;
	default: // fstl
		opr_dest.data_size = 32; 
		len += modrm_rm(eip + 1, &opr_dest);
		temp.dval = (double)u2f(fpu_peek());
		opr_dest.val = temp.uval[0];
		operand_write(&opr_dest);
		opr_dest.addr += 4;
		opr_dest.val = temp.uval[1];
		operand_write(&opr_dest);
	}
	print_asm_0("fst", "", len);
	return len;
}

make_instr_func(x87_fsts) {
	int len = 1;
	opr_dest.data_size = 32;
	len += modrm_rm(eip + 1, &opr_dest);
	opr_dest.val = fpu_peek();
	operand_write(&opr_dest);
	print_asm_0("fsts", "", len);
	return len;
}

make_instr_func(x87_fucom) {
	uint32_t idx = instr_fetch(eip + 1, 1) & 0x7;
	fpu_cmp(idx);
	print_asm_0("fucom", "", 2);
	return 2;
}

make_instr_func(x87_fucomi) {
	uint32_t idx = instr_fetch(eip + 1, 1) & 0x7;
	fpu_cmpi(idx);
	print_asm_0("fucomi", "", 2);
	return 2;
}

make_instr_func(x87_fucomip) {
	uint32_t idx = instr_fetch(eip + 1, 1) & 0x7;
	fpu_cmpi(idx);
	fpu_store();
	print_asm_0("fucomip", "", 2);
	return 2;
}

make_instr_func(x87_fucomp) {
	uint32_t idx = instr_fetch(eip + 1, 1) & 0x7;
	fpu_cmp(idx);
	fpu_store();
	print_asm_0("fucomp", "", 2);
	return 2;
}

make_instr_func(x87_fnstcw) {
	int len = 1;
	opr_dest.data_size = 16;
	len += modrm_rm(eip + 1, &opr_dest);
	opr_dest.val = fpu.control.val;
	operand_write(&opr_dest);
	print_asm_0("fnstcw", "", len);
	return len;
}

make_instr_func(x87_fistpl) {
	int len = 1;
	float f;
	uint32_t u;
	int i;
	opr_dest.data_size  = 32;
	len += modrm_rm(eip + 1, &opr_dest);
	u = fpu_store();
	f = u2f(u);
	i = (int) f;
	opr_dest.val = i;
	operand_write(&opr_dest);
	print_asm_0("fistpl", "", len);
	return len;
}
