#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	uint32_t addr=(uint32_t)hw_mem+page_translate(segment_translate(cpu.idtr.base+8*intr_no,SREG_DS));
	GateDesc* gatedesc=(void*)addr;
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.eflags.val);
	cpu.esp-=2;
	vaddr_write(cpu.esp,SREG_DS,2,cpu.cs.val);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.eip);
	if(gatedesc->type==0xe)
		cpu.eflags.IF=1;
	else if(gatedesc->type==0xf)
		cpu.eflags.IF=0;
	cpu.eip=(gatedesc->offset_31_16<<16)+gatedesc->offset_15_0;
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
