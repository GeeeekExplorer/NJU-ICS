#include "nemu.h"
#include "cpu/cpu.h"
#include "cpu/operand.h"
#include <stdlib.h>
#include <time.h>

char * reg_names_l[] = {"%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi"};
char * reg_names_w[] = {"%ax", "%cx", "%dx", "%bx", "%sp", "%bp", "%si", "%di"};
char * reg_names_b[] = {"%al", "%cl", "%dl", "%bl", "%ah", "%ch", "%dh", "%bh"};
char * sreg_names[] = {"%es", "%cs", "%ss", "%ds", "%fs", "%gs"};

void print_reg() {
	printf("eax\t0x%08x\n", cpu.eax);
	printf("ecx\t0x%08x\n", cpu.ecx);
	printf("edx\t0x%08x\n", cpu.edx);
	printf("ebx\t0x%08x\n", cpu.ebx);
	printf("esp\t0x%08x\n", cpu.esp);
	printf("ebp\t0x%08x\n", cpu.ebp);
	printf("esi\t0x%08x\n", cpu.esi);
	printf("edi\t0x%08x\n", cpu.edi);
	printf("eip\t0x%08x\n", cpu.eip);
}

int get_reg_val(const char *reg, bool *success) {
	int i;
	*success = true;
	for(i = 0; i < 8; i ++) {
		if(strcmp(reg_names_l[i] + 1, reg) == 0) {
			return cpu.gpr[i]._32;
		}
	} 

	for(i = 0; i < 8; i ++) {
		if(strcmp(reg_names_w[i] + 1, reg) == 0) {
			return cpu.gpr[i]._16;
		}
	} 

	for(i = 0; i < 8; i ++) {
		if(strcmp(reg_names_b[i] + 1, reg) == 0) {
			return cpu.gpr[i % 4]._8[i / 4];
		}
	} 

	if(strcmp(reg, "eip") == 0) {
		return cpu.eip;
	}

	if(strcmp(reg, "eflags") == 0) {
		return cpu.eflags.val;
	}

	*success = false;
	return 0;
}

void reg_test() {
	srand(time(0));
	uint32_t sample[8];
	uint32_t eip_sample = rand();
	OPERAND r;
	cpu.eip = eip_sample;
	r.type = OPR_REG;


	int i;
	for(i = REG_EAX; i <= REG_EDI; i ++) {
		sample[i] = rand();
		r.data_size = 32;
		r.addr = i;
		r.val = sample[i];
		operand_write(&r);
		r.data_size = 16;
		operand_read(&r);
		assert(r.val == (sample[i] & 0xffff));
	}
	r.data_size = 8;
	r.addr = REG_AL;
	operand_read(&r);
	assert(r.val == (sample[REG_EAX] & 0xff));
	r.addr = REG_AH;
	operand_read(&r);
	assert(r.val == ((sample[REG_EAX] >> 8) & 0xff));
	r.addr = REG_BL;
	operand_read(&r);
	assert(r.val == (sample[REG_EBX] & 0xff));
	r.addr = REG_BH;
	operand_read(&r);
	assert(r.val == ((sample[REG_EBX] >> 8) & 0xff));
	r.addr = REG_CL;
	operand_read(&r);
	assert(r.val == (sample[REG_ECX] & 0xff));
	r.addr = REG_CH;
	operand_read(&r);
	assert(r.val == ((sample[REG_ECX] >> 8) & 0xff));
	r.addr = REG_DL;
	operand_read(&r);
	assert(r.val == (sample[REG_EDX] & 0xff));
	r.addr = REG_DH;
	operand_read(&r);
	assert(r.val == ((sample[REG_EDX] >> 8) & 0xff));

	assert(sample[REG_EAX] == cpu.eax);
	assert(sample[REG_ECX] == cpu.ecx);
	assert(sample[REG_EDX] == cpu.edx);
	assert(sample[REG_EBX] == cpu.ebx);
	assert(sample[REG_ESP] == cpu.esp);
	assert(sample[REG_EBP] == cpu.ebp);
	assert(sample[REG_ESI] == cpu.esi);
	assert(sample[REG_EDI] == cpu.edi);

	assert(eip_sample == cpu.eip);

	printf("reg_test()      \e[0;32mpass\e[0m\n");
}

