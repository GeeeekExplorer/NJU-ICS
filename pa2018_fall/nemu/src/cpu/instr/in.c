#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
	print_asm_0("in", "b", 1);
	cpu.eax = pio_read(cpu.edx, 1);
	return 1;
}

make_instr_func(in_v) {
	print_asm_0("in", (data_size == 16)?"w":"l", 1);
	cpu.eax = pio_read(cpu.edx, data_size/8);
	return 1;
}
	
