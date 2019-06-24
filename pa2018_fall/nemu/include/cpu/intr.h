#ifndef __INTR_H__
#define __INTR_H__

#include "nemu.h"
#include "device/i8259_pic.h"

typedef union GateDescriptor {
	struct {
		uint32_t offset_15_0      : 16;
		uint32_t selector         : 16;
		uint32_t pad0             : 8;
		uint32_t type             : 4;
		uint32_t system           : 1;
		uint32_t privilege_level  : 2;
		uint32_t present          : 1;
		uint32_t offset_31_16     : 16;
	};
	uint32_t val[2];
} GateDesc;

void raise_intr(uint8_t intr_no);
void raise_sw_intr(uint8_t intr_no);

#endif
