#include "common.h"
#include "memory.h"
#include "x86.h"

#define BMR_PORT 0xc040

struct {
	uint32_t addr;
	uint16_t byte_cnt;
	uint16_t pad0	:15;
	uint16_t eot	:1;
} PRD;

void
dma_prepare(void *buf) {
	uint32_t addr = (uint32_t)va_to_pa(buf);

	PRD.addr = addr;
	PRD.byte_cnt = 512;
	PRD.eot = 1;
	PRD.pad0 = 0;

	uint32_t PRD_addr = (uint32_t)va_to_pa(&PRD);
	out_long(BMR_PORT + 4, PRD_addr);
}

void
dma_issue_read(void) {
	out_byte(BMR_PORT, in_byte(BMR_PORT) | 0x1 | 0x8);
}
