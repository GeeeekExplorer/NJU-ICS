#include "cpu/instr.h"

char addr_str_1[50];
char addr_str_2[50];
char addr_str_3[50];
#define MAX_INSTR_BYTES 13

void print_asm_0(char * instr, char * suffix, uint8_t len) {
	if(verbose) {
		if( len > MAX_INSTR_BYTES ) len = MAX_INSTR_BYTES;
		printf("%08x:   ", cpu.eip);
		int i;
		for(i = 0 ; i < len ; i++) {
			printf("%02x ", instr_fetch(cpu.eip + i, 1));
		}
		for(i = 0 ; i <= MAX_INSTR_BYTES - len ; i++) printf("   ");
		printf("%s%s\n", instr, suffix); 
	}
}
void print_asm_1(char * instr, char * suffix, uint8_t len, OPERAND * opr_1) {
	if(verbose) {
		if( len > MAX_INSTR_BYTES ) len = MAX_INSTR_BYTES;
		parse_operand_address(opr_1, addr_str_1);
		printf("%08x:   ", cpu.eip);
		int i;
		for(i = 0 ; i < len ; i++) {
			printf("%02x ", instr_fetch(cpu.eip + i, 1));
		}
		for(i = 0 ; i <= MAX_INSTR_BYTES - len ; i++) printf("   ");
		printf("%s%s %s\n", instr, suffix, addr_str_1); 
	}
}
void print_asm_2(char * instr, char * suffix, uint8_t len, OPERAND * opr_1, OPERAND * opr_2) {
	if(verbose) {
		if( len > MAX_INSTR_BYTES ) len = MAX_INSTR_BYTES;
		parse_operand_address(opr_1, addr_str_1);
		parse_operand_address(opr_2, addr_str_2);
		printf("%08x:   ", cpu.eip);
		int i;
		for(i = 0 ; i < len ; i++) {
			printf("%02x ", instr_fetch(cpu.eip + i, 1));
		}
		for(i = 0 ; i <= MAX_INSTR_BYTES - len ; i++) printf("   ");
		printf("%s%s %s, %s\n", instr, suffix,addr_str_1, addr_str_2); 
	}
}
void print_asm_3(char * instr, char * suffix, uint8_t len, OPERAND * opr_1, OPERAND * opr_2, OPERAND * opr_3) {
	if(verbose) {
		if( len > MAX_INSTR_BYTES ) len = MAX_INSTR_BYTES;
		parse_operand_address(opr_1, addr_str_1);
		parse_operand_address(opr_2, addr_str_2);
		parse_operand_address(opr_3, addr_str_3);
		printf("%08x:   ", cpu.eip);
		int i;
		for(i = 0 ; i < len ; i++) {
			printf("%02x ", instr_fetch(cpu.eip + i, 1));
		}
		for(i = 0 ; i <= MAX_INSTR_BYTES - len ; i++) printf("   ");
		printf("%s%s %s, %s, %s\n", instr, suffix,addr_str_1, addr_str_2, addr_str_3); 
	}
}
