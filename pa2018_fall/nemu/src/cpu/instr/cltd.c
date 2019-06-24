#include "cpu/instr.h"

make_instr_func(cltd) {
	OPERAND ax, dx;
	ax.type = OPR_REG;
	dx.type = OPR_REG;

	ax.data_size = data_size;
	dx.data_size = data_size;
	
	ax.addr = REG_AX;
	dx.addr = REG_DX;

	operand_read(&ax);
	int temp = (int) ax.val;
	
	uint32_t dxval = 0;
	if(temp < 0) {
		dxval = ~dxval;
	}
	dx.val = dxval;
	operand_write(&dx);

	print_asm_0("cltd", "", 1);
	return 1;
}
