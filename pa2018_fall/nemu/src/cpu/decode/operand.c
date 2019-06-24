#include "cpu/operand.h"
#include <stdio.h>

// the source and destination operands
OPERAND opr_src, opr_dest;

void operand_read(OPERAND * opr) {
	switch(opr->type) {
		case OPR_MEM:
			//assert(opr->sreg == SREG_DS || opr->sreg == SREG_SS);
			opr->val = vaddr_read(opr->addr, opr->sreg, 4);
			break;
		case OPR_IMM: 
			opr->val = vaddr_read(opr->addr, SREG_CS, 4);
			break;
		case OPR_REG:
			if(opr->data_size == 8) {
				opr->val = cpu.gpr[opr->addr % 4]._8[opr->addr / 4];
			} else {
				opr->val = cpu.gpr[opr->addr]._32;
			}
			break;
		case OPR_CREG:
			switch(opr->addr) {
#ifdef IA32_SEG
				case 0: opr->val = cpu.cr0.val; break;
#endif
#ifdef IA32_PAGE
				case 3: opr->val = cpu.cr3.val; break;
#endif
				default:
					printf("Error: Cannot read from control register %d\n", opr->addr);
					assert(0);
					break;
			}
			break;
		case OPR_SREG:
#ifdef IA32_SEG
			opr->val = cpu.segReg[opr->addr].val;
#endif
			break;
	}
	
	// deal with data size
	switch(opr->data_size) {
		case 8: opr->val = opr->val & 0xff; break;
		case 16: opr->val = opr->val & 0xffff; break;
		case 32: break;
		default: 
			printf("Error: Operand data size = %u\n", (uint8_t)opr->data_size);
			assert(0);
			break;
	}
}

void operand_write(OPERAND * opr) {
	switch(opr->type) {
	case OPR_MEM:
		// data size here
		//assert(opr->sreg == SREG_DS || opr->sreg == SREG_SS);
		vaddr_write(opr->addr, opr->sreg, opr->data_size / 8, opr->val);
		break;
	case OPR_REG:
		// data size here
		// printf("reg data size = %d, val = %x, addr = %x\n", opr->data_size, opr->val, opr->addr);
		switch(opr->data_size) {
		case 8: cpu.gpr[opr->addr % 4]._8[opr->addr / 4] = opr->val; break;
		case 16: cpu.gpr[opr->addr]._16 = opr->val; break;
		case 32: cpu.gpr[opr->addr]._32 = opr->val;
			break;
		default:
			printf("Error: Data size = %u\n", (uint8_t)opr->data_size);
			assert(0);
			break;
		}
		break;
	case OPR_IMM:
		printf("Error: Cannot write to an immediate\n");
		assert(0);
		break;
	case OPR_CREG:
		switch(opr->addr) {
#ifdef IA32_SEG
			case 0: cpu.cr0.val = opr->val; break;
#endif
#ifdef IA32_PAGE
			case 3: cpu.cr3.val = opr->val; break;
#endif
			default:
				printf("Error: Cannot write to control regeister %d\n", opr->addr);
				assert(0);
				break;
		}
	case OPR_SREG:
#ifdef IA32_SEG
		cpu.segReg[opr->addr].val = opr->val;
#endif
		break;
	}
}

void parse_operand_address(OPERAND * opr, char * str) {
	char disp_temp[20] = "";
	char sib_temp[40] = "";
	switch(opr->type) {
		case OPR_REG: 
			switch(opr->data_size){
				case 8: strcpy(str, reg_names_b[opr->addr]); return;
				case 16: strcpy(str, reg_names_w[opr->addr]); return;
				case 32: strcpy(str, reg_names_l[opr->addr]); return;
				default: printf("illegal operand size %d\n", opr->data_size); assert(0); return;
			}
			break;
		case OPR_IMM:
			operand_read(opr);
			sprintf(str, "$0x%x", opr->val);
			break;
		case OPR_CREG:
			sprintf(str, "%%cr%x", opr->addr);
			break;
		case OPR_SREG:
			strcpy(str, sreg_names[opr->addr]);
			break;
		case OPR_MEM:
			if(opr->mem_addr.disp != MEM_ADDR_NA) {
				int displacement = opr->mem_addr.disp;
				sprintf(disp_temp, "%s0x%x", displacement < 0 ? "-" : "", displacement < 0 ? -displacement : displacement);
			}
			if(opr->mem_addr.base != MEM_ADDR_NA && opr->mem_addr.index == MEM_ADDR_NA) {
				sprintf(sib_temp, "(%s)", reg_names_l[opr->mem_addr.base]);
			} else if(opr->mem_addr.base == MEM_ADDR_NA && opr->mem_addr.index != MEM_ADDR_NA) {
				sprintf(sib_temp, "(,%s,%d)", reg_names_l[opr->mem_addr.index], opr->mem_addr.scale);
			} else if(opr->mem_addr.base != MEM_ADDR_NA && opr->mem_addr.index != MEM_ADDR_NA) {
				if(opr->mem_addr.scale != 0) {
					sprintf(sib_temp, "(%s,%s,%d)", reg_names_l[opr->mem_addr.base], reg_names_l[opr->mem_addr.index], opr->mem_addr.scale);
				} else {
					sprintf(sib_temp, "(%s)", reg_names_l[opr->mem_addr.base]);
				}
			}
			sprintf(str, "%s%s", disp_temp, sib_temp);
			break;
		default: printf("illegal operand type %d\n", opr->type);
	}
}

void clear_operand_mem_addr(OPERAND * opr) {
	opr->mem_addr.disp = MEM_ADDR_NA;
	opr->mem_addr.base = MEM_ADDR_NA;
	opr->mem_addr.index = MEM_ADDR_NA;
	opr->mem_addr.scale = MEM_ADDR_NA;
}
