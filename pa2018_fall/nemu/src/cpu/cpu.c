#include "nemu.h"
#include "cpu/cpu.h"
#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"
#include "monitor/breakpoint.h"
#include <stdio.h>
#include <assert.h>

CPU_STATE cpu;
FPU fpu;
int nemu_state;
uint8_t data_size = 32;

#define sign(x) ((uint32_t)(x) >> 31)

void init_cpu(const uint32_t init_eip) {
	cpu.eflags.val = 0x0;
	fpu.status.val = 0x0;
	int i=0;
	for(i = 0; i < 8; i++) {
		cpu.gpr[i].val = 0x0;
		fpu.regStack[i].val = 0x0;
	}
	cpu.eip = init_eip;
	cpu.esp = (128 << 20) - 16;
#ifdef IA32_SEG
	cpu.cr0.val = 0x0;
	cpu.gdtr.base = cpu.gdtr.limit = 0x0;
	for(i = 0; i < 6; i++) {
		cpu.segReg[i].val = 0x0;
		cpu.cache[i].base = cpu.cache[i].limit = cpu.cache[i].privilege_level = 0;
	}
	
#endif
#ifdef IA32_INTR
	cpu.idtr.base = cpu.idtr.limit = 0x0;
	cpu.intr = 0x0;
	i8259_init();
#endif
}

bool verbose = false;

void exec(uint32_t n) {
	static BP *bp = NULL;
	verbose = (n <= 100000);
	int instr_len = 0;
	bool hit_break_rerun = false;

	if(nemu_state == NEMU_BREAK) {
		hit_break_rerun = true;
	}

	nemu_state = NEMU_RUN;
	while( n > 0 && nemu_state == NEMU_RUN) {
		instr_len = exec_inst();
		cpu.eip += instr_len;
		n--;

		if(hit_break_rerun) {
			resume_breakpoints();
			hit_break_rerun = false;
		}

		// check for breakpoints
		if(nemu_state == NEMU_BREAK) {
			// find break in the list
			bp = find_breakpoint(cpu.eip - 1);
			if(bp) {
				// found, then restore the original opcode
				vaddr_write(bp->addr, SREG_CS, 1, bp->ori_byte);
				cpu.eip--;
			}
			// not found, it is triggered by BREAK_POINT in the code, do nothing
		}

		// check for watchpoints

		BP *wp = scan_watchpoint();
		if(wp != NULL) {
			// print_bin_instr(eip_temp, instr_len);
			// puts(assembly);
			printf("\n\nHit watchpoint %d at address 0x%08x, expr = %s\n", wp->NO, cpu.eip - instr_len, wp->expr);
			printf("old value = %#08x\nnew value = %#08x\n", wp->old_val, wp->new_val);
			wp->old_val = wp->new_val;
			nemu_state = NEMU_READY;
			break;
		}

#ifdef IA32_INTR
		// check for interrupt
		if(cpu.intr && cpu.eflags.IF) {
			// get interrupt number
			uint8_t intr_no = i8259_query_intr_no(); // get interrupt number
			assert(intr_no != I8259_NO_INTR);
			i8259_ack_intr(); // tell the PIC interrupt info received
			raise_intr(intr_no); // raise intrrupt to turn into kernel handler
		}
#endif
	}
	if(nemu_state == NEMU_STOP) {
		printf("NEMU2 terminated\n");
#ifdef IA32_INTR
		i8259_destroy();
#endif
	} else if(n == 0) {
		nemu_state = NEMU_READY;
	}
}

int exec_inst() {
	uint8_t opcode = 0;
	// get the opcode
	opcode = instr_fetch(cpu.eip, 1);
	//printf("opcode = %x, eip = %x\n", opcode, cpu.eip);
	// instruction decode and execution
#ifdef NEMU_REF_INSTR
	int len = __ref_opcode_entry[opcode](cpu.eip, opcode);
#else
	int len = opcode_entry[opcode](cpu.eip, opcode);
#endif
	return len;
}

void set_CF_add(uint32_t result,uint32_t src,size_t data_size){
    result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
    src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
    cpu.eflags.CF=(result<src);
}

void set_CF_adc(uint32_t result,uint32_t src,size_t data_size){
    result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
    src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==1)    
		cpu.eflags.CF=(result<=src);
	else
		cpu.eflags.CF=(result<src);
}


void set_CF_sub(uint32_t dest,uint32_t src,size_t data_size){
    dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
    src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
    cpu.eflags.CF=(dest<src);
}

void set_CF_sbb(uint32_t dest,uint32_t src,size_t data_size){
    dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
    src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==1)    
		cpu.eflags.CF=(dest<=src);
	else
		cpu.eflags.CF=(dest<src);
}

void set_ZF(uint32_t result,size_t data_size){
    result=result&(0xFFFFFFFF>>(32-data_size));
    cpu.eflags.ZF=(result==0);
}

void set_SF(uint32_t result,size_t data_size){
    result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
    cpu.eflags.SF=sign(result);
}

void set_PF(uint32_t result){
	int i=0;
    if((result&0x00000001)==0x00000001)i++;
	if((result&0x00000002)==0x00000002)i++;
	if((result&0x00000004)==0x00000004)i++;
	if((result&0x00000008)==0x00000008)i++;
	if((result&0x00000010)==0x00000010)i++;
	if((result&0x00000020)==0x00000020)i++;
	if((result&0x00000040)==0x00000040)i++;
	if((result&0x00000080)==0x00000080)i++;
	
	if(i%2)
		cpu.eflags.PF=0;
	else
		cpu.eflags.PF=1;
}

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(sign(src)==sign(dest)){
		if(sign(src)!=sign(result))
				cpu.eflags.OF=1;
		else
				cpu.eflags.OF=0;
	}else{
			cpu.eflags.OF=0;
	}
}

void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(sign(src)!=sign(dest)){
		if(sign(dest)!=sign(result))
				cpu.eflags.OF=1;
		else
				cpu.eflags.OF=0;
	}else{
			cpu.eflags.OF=0;
	}
}
