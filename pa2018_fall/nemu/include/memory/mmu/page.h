#ifndef __PAGE_H__
#define __PAGE_H__

#include "nemu.h"

/* 32bit x86 uses 4KB page size */
#define PAGE_SIZE					4096
#define NR_PDE						1024
#define NR_PTE						1024
#define PD_SIZE						((NR_PTE) * (PAGE_SIZE))

#define PAGE_MASK					(PAGE_SIZE - 1)

/* force the data to be aligned with page boundary.
   statically defined page tables uses this feature. */
#define align_to_page              __attribute((aligned(PAGE_SIZE)))

/* the 32bit Page Directory(first level page table) data structure */
typedef union PageDirectoryEntry {
	struct {
		uint32_t present             : 1;
		uint32_t read_write          : 1; 
		uint32_t user_supervisor     : 1;
		uint32_t page_write_through  : 1;
		uint32_t page_cache_disable  : 1;
		uint32_t accessed            : 1;
		uint32_t pad0                : 6;
		uint32_t page_frame          : 20;
	};
	uint32_t val;
} PDE;

/* the 32bit Page Table Entry(second level page table) data structure */
typedef union PageTableEntry {
	struct {
		uint32_t present             : 1;
		uint32_t read_write          : 1;
		uint32_t user_supervisor     : 1;
		uint32_t page_write_through  : 1;
		uint32_t page_cache_disable  : 1;
		uint32_t accessed            : 1;
		uint32_t dirty               : 1;
		uint32_t pad0                : 1;
		uint32_t global              : 1;
		uint32_t pad1                : 3;
		uint32_t page_frame          : 20;
	};
	uint32_t val;
} PTE;

paddr_t page_translate(laddr_t laddr);
paddr_t page_walk(laddr_t laddr);

#endif
