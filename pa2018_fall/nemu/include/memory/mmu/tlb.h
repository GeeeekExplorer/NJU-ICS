#ifndef __TLB_H__
#define __TLB_H__

uint32_t tlb_read(laddr_t);
void init_all_tlb();
void make_all_tlb();

#endif
