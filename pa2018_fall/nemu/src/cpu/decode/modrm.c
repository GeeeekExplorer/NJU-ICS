#include "nemu.h"
#include "cpu/modrm.h"
#include "cpu/sib.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include <stdio.h>

// eip point to ModR/M byte
int case_mod_00(uint32_t eip, MODRM modrm, OPERAND * opr) {
	int len = 0;
	switch(modrm.rm) {
	case 4: // SIB + disp32
		opr->type = OPR_MEM;
		//len += parse_sib(eip + 1, modrm.mod, &opr->addr, &opr->sreg);
		len += parse_sib(eip + 1, modrm.mod, opr);
		break;
	case 5: // disp32
		opr->type = OPR_MEM;
		opr->sreg = SREG_DS;
		opr->addr = instr_fetch(eip + 1, 4);
		opr->mem_addr.disp = opr->addr;
		len += 4; // disp32
		break;
	default: // [EXX]
		opr->type = OPR_MEM;
		opr->sreg = SREG_DS;
		opr->addr = cpu.gpr[modrm.rm]._32;
		opr->mem_addr.base = modrm.rm;
		break;
	}
	// operand_read(opr);
	return len;
}

int case_mod_01(uint32_t eip, MODRM modrm, OPERAND * opr) {
	int len = 0;
	int8_t disp8 = 0;
	switch(modrm.rm) {
	case 4: //disp8 SIB
		opr->type = OPR_MEM;
		//len += parse_sib(eip + 1, modrm.mod, &opr->addr, &opr->sreg);
		len += parse_sib(eip + 1, modrm.mod, opr);
		disp8 = (int8_t) instr_fetch(eip + 2, 1);
		len += 1; // disp8
		break;
	default: //disp8[EXX]
		opr->type = OPR_MEM;
		opr->addr = cpu.gpr[modrm.rm]._32;
		opr->mem_addr.base = modrm.rm;
		disp8 = (int8_t) instr_fetch(eip + 1, 1);
		len += 1; // disp8
		if(modrm.rm == 5) { // EBP
			opr->sreg = SREG_SS;
		} else {
			opr->sreg = SREG_DS;
		}
		break;
	}
	opr->addr = disp8 + (int32_t)opr->addr;
	opr->mem_addr.disp = disp8;
	return len;
}

int case_mod_10(uint32_t eip, MODRM modrm, OPERAND * opr) {
	int len = 0;
	int32_t disp32 = 0;
	switch(modrm.rm) {
	case 4: //disp32 SIB
		opr->type = OPR_MEM;
		//len += parse_sib(eip + 1, modrm.mod, &opr->addr, &opr->sreg);
		len += parse_sib(eip + 1, modrm.mod, opr);
		disp32 = (int32_t) instr_fetch(eip + 2, 4);
		len += 4; // disp32
		break;
	default: // disp32[EXX]
		opr->type = OPR_MEM;
		opr->addr = cpu.gpr[modrm.rm]._32;
		opr->mem_addr.base = modrm.rm;
		disp32 = (int32_t) instr_fetch(eip + 1, 4);
		len += 4; // disp32
		if(modrm.rm == 5) { // EBP
			opr->sreg = SREG_SS;
		} else {
			opr->sreg = SREG_DS;
		}
		break;
	} 
	opr->addr = disp32 + (int32_t)opr->addr;
	opr->mem_addr.disp = disp32;
	return len;
}

int case_mod_11(uint32_t eip, MODRM modrm, OPERAND * opr) {
	opr -> type = OPR_REG;
	opr -> addr = modrm.rm;
	return 0;
}

int parse_rm_32(uint32_t eip, MODRM modrm, OPERAND * opr) {
	int len = 1; // modr/m
	if(verbose) clear_operand_mem_addr(opr);
	switch(modrm.mod) {
	case 0: len += case_mod_00(eip, modrm, opr); break;
	case 1: len += case_mod_01(eip, modrm, opr); break;
	case 2: len += case_mod_10(eip, modrm, opr); break;
	case 3: len += case_mod_11(eip, modrm, opr); break;
	}
	return len;
}


int modrm_r_rm(uint32_t eip, OPERAND * r, OPERAND * rm) {
	MODRM modrm;
	modrm.val = instr_fetch(eip, 1);
	r -> type = OPR_REG;
	r -> addr = modrm.reg_opcode;
	int len = parse_rm_32(eip, modrm, rm);
	return len;
}

int modrm_opcode_rm(uint32_t eip, uint8_t * opcode, OPERAND * rm) {
        MODRM modrm;
        modrm.val = instr_fetch(eip, 1);
        *opcode = modrm.reg_opcode;
        int len = parse_rm_32(eip, modrm, rm);
        return len;
}

int modrm_opcode(uint32_t eip, uint8_t * opcode) {
        MODRM modrm;
        modrm.val = instr_fetch(eip, 1);
        *opcode = modrm.reg_opcode;
        return 1;
}

int modrm_rm(uint32_t eip, OPERAND * rm) {
	MODRM modrm;
	modrm.val = instr_fetch(eip, 1);
	int len = parse_rm_32(eip, modrm, rm);
	return len;
}
