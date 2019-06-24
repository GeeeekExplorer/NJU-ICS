#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	uint32_t base=cpu.cache[sreg].base;
	return base+offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	uint32_t addr=(uint32_t)hw_mem+cpu.gdtr.base+8*cpu.segReg[sreg].index;
	SegDesc* segdesc=(void*)addr;
	uint32_t base=(segdesc->base_31_24<<24)+(segdesc->base_23_16<<16)+segdesc->base_15_0;
	uint32_t limit=(segdesc->limit_19_16<<16)+segdesc->limit_15_0;
	uint32_t privilege_level=segdesc->privilege_level;
	assert(base==0);
	assert(limit==0xFFFFF);
	assert(segdesc->granularity==1);	
	cpu.cache[sreg].base=base;
	cpu.cache[sreg].limit=limit;
	cpu.cache[sreg].privilege_level=privilege_level;
}
