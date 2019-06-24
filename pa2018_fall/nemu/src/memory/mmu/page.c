#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	uint32_t dir = (laddr >> 22) & 0x3ff;
	uint32_t page = (laddr >> 12) & 0x3ff;
	uint32_t offset = laddr & 0xfff;
	PDE *pdir = (PDE *)(hw_mem + (cpu.cr3.pdtr << 12) + (dir << 2));
	PTE *ptable = (PTE *)(hw_mem + (pdir->page_frame << 12) + (page << 2));
	assert(pdir->present==1);
	assert(ptable->present==1);
	return (ptable->page_frame << 12) + offset;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
