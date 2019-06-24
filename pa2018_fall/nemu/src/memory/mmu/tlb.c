#include "cpu/cpu.h"
#include "memory/memory.h"
#include "memory/mmu/page.h"

#include <stdlib.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#ifdef TLB_ENABLED

typedef union {
	struct {
		uint32_t pf_off		:12;
		uint32_t pt_idx		:10;
		uint32_t pdir_idx	:10;
	};
	uint32_t addr;
} PageAddr;

paddr_t page_walk(laddr_t laddr) {
	PageAddr *addr = (void *)&laddr;
	paddr_t pdir_base = cpu.cr3.val & ~PAGE_MASK;

	PDE pde;
	pde.val	= paddr_read(pdir_base + addr->pdir_idx * 4, 4);
	/*if(!pde.present) {
		Log("eip = %x, lnaddr = %x, pdir_base = %x, pde = %x", cpu.eip, lnaddr, pdir_base, pde.val);
		assert(0);
	}*/
	assert(pde.present);

	paddr_t pt_base = pde.val & ~PAGE_MASK;
	PTE pte;
	pte.val = paddr_read(pt_base + addr->pt_idx * 4, 4);
	/*if(!pte.present) {
		Log("eip = %x, lnaddr = %x, pt_base = %x, pte = %x", cpu.eip, lnaddr, pt_base, pte.val);
		assert(0);
	}*/
	assert(pte.present);

	return pte.val;
}

typedef union {
	struct {
		uint32_t valid	:1;
		uint32_t pad0	:11;
		uint32_t vpn	:20;
	};
	uint32_t val;
} TLBKey;

/* TLB is fully associative */
typedef struct {
	int size;
	int size_width;
	TLBKey *key;
	uint32_t *pte;
} TLB;

static TLB tlb;

bool tlb_query(TLB *t, laddr_t lnaddr, int *idx) {
	uint32_t key = (lnaddr & ~PAGE_MASK) | 0x1;
	int i;

	asm ("cld; repne scasl" : "=c"(i) : "a"(key), "D"(t->key), "c"(t->size + 1));
	*idx = t->size - i;
	if(*idx < t->size) {
		return true;
	}

	/* TLB miss */
	*idx = rand() & mask_with_len(t->size_width);		// victim TLB entry
	return false;
}

static uint32_t tlb_fetch(TLB *t, laddr_t lnaddr) {
	int idx;
#ifdef TLB_ENABLED
   	bool b = tlb_query(t, lnaddr, &idx); 
	if(b) {
		/* TLB hit */
		return idx;
	}

	/* TLB miss */

#else
	idx = 0;
#endif
	/* TLB fill */
	t->key[idx].val = (lnaddr & ~PAGE_MASK) | 0x1; 
	t->pte[idx] = page_walk(lnaddr);
	return idx;
}

uint32_t tlb_read(laddr_t lnaddr) {
	uint32_t idx = tlb_fetch(&tlb, lnaddr);
	return tlb.pte[idx] & ~PAGE_MASK;
}

static void init_tlb(TLB *t) {
	int i;
	for(i = 0; i < t->size; i ++) {
		t->key[i].val = 0;
	}
}

static void make_tlb(TLB *t, int size_width) {
	t->size_width = size_width;
	t->size = exp2(size_width);
	t->key = malloc(sizeof(TLBKey) << size_width);
	t->pte = malloc(sizeof(uint32_t) << size_width);
}

void make_all_tlb() {
	make_tlb(&tlb, 6);
}

void init_all_tlb() {
	init_tlb(&tlb);
}
#endif
