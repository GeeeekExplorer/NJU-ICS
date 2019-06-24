#include "cpu/sib.h"
#include "cpu/cpu.h"
#include "cpu/operand.h"
#include "memory/memory.h"
#include <stdio.h>

// uint32_t parse_sib(sib s) {
/*
int parse_sib(uint32_t eip, uint32_t mod, uint32_t *sibaddr, uint8_t *sibsreg) {
	SIB sib;
	sib.val = instr_fetch(eip, 1);
	uint32_t idx = 0;
	*sibsreg = SREG_DS;
	
	if(sib.base == 5 || sib.base == 4) {
		*sibsreg = SREG_SS;
	}
	
	if(sib.index != 4) {
		idx = cpu.gpr[sib.index]._32;
		switch(sib.ss) {
			case 0x0: break;
			case 0x1: idx *= 2; break;
			case 0x2: idx *= 4; break;
			case 0x3: idx *= 8; break;
		}
	}
	switch(mod){
	case 0: // only now has additional disp32?
		if(sib.base == 5) {
			int32_t disp32 = instr_fetch(eip + 1, 4);
			*sibaddr = idx + disp32;
			//printf("\nsib disp32 %x\n", disp32);
			return 5;
		}
	case 1:
	case 2: *sibaddr = cpu.gpr[sib.base]._32 + idx;
		return 1;
	default: 
		printf("illegal mod=11 in SIB\n");
		assert(0);
		break;
		return 0;
	}
}
*/

int parse_sib(uint32_t eip, uint32_t mod, OPERAND * opr) {
	SIB sib;
	sib.val = instr_fetch(eip, 1);
	uint32_t idx = 0;
	opr->sreg = SREG_DS;
	
	if(sib.base == 5 || sib.base == 4) {
		opr->sreg = SREG_SS;
	}
	
	if(sib.index != 4) {
		idx = cpu.gpr[sib.index]._32;
		opr->mem_addr.index = sib.index;
		switch(sib.ss) {
			case 0x0: opr->mem_addr.scale = 1;
				  break;
			case 0x1: idx *= 2;
				  opr->mem_addr.scale = 2;
				  break;
			case 0x2: idx *= 4;
				  opr->mem_addr.scale = 4;
				  break;
			case 0x3: idx *= 8; 
				  opr->mem_addr.scale = 8;
				  break;
		}
	}
	switch(mod){
	case 0: // only now has additional disp32?
		if(sib.base == 5) {
			int32_t disp32 = instr_fetch(eip + 1, 4);
			opr->addr = idx + disp32;
			opr->mem_addr.disp = disp32;
			//printf("\nsib disp32 %x\n", disp32);
			return 5;
		}
	case 1:
	case 2: opr->addr = cpu.gpr[sib.base]._32 + idx;
		opr->mem_addr.base = sib.base;
		return 1;
	default: 
		printf("illegal mod=11 in SIB\n");
		assert(0);
		break;
		return 0;
	}
}
