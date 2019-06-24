#include "cpu/instr.h"
#include <stdio.h>
#include <scoring.h>

make_instr_func(nemu_trap) {
	int i = 0;
	switch(cpu.eax) {
	case 4: 
		printf("\e[0;31mnemu trap output: \e[0m");
		for(i = 0; i < cpu.edx ; i++) {
			putchar((char) vaddr_read(cpu.ecx + i, SREG_DS, 1));
		}
		break;
	case 110:
		score_trap();
		break;
	default:
		printf("nemu: HIT %s TRAP at eip = 0x%08x\n", (cpu.eax == 0 ? "\e[0;32mGOOD\e[0m" : "\e[0;31mBAD\e[0m"), eip);
		if(get_ref()) {
			printf("\e[0;31mYou have used reference implementation, DO NOT submit this version.\e[0m\n");
		}
		nemu_state = NEMU_STOP;
		score_trap();
		break;
        }
        return 1;
}

make_instr_func(break_point) {
	printf("hit breakpoint at eip = 0x%08x\n", cpu.eip);
	nemu_state = NEMU_BREAK;
	return 1;
}
