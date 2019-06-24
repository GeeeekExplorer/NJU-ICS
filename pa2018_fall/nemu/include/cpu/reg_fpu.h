#ifndef __REG_FPU_H__
#define __REG_FPU_H__

#include "nemu.h"

typedef union {
	struct {
		uint32_t ie	:1;
		uint32_t de	:1;
		uint32_t ze	:1;
		uint32_t oe	:1;
		uint32_t ue	:1;
		uint32_t pe	:1;
		uint32_t sf	:1;
		uint32_t es	:1;
		uint32_t c0	:1;
		uint32_t c1	:1;
		uint32_t c2	:1;
		uint32_t top	:3;
		uint32_t c3	:1;
		uint32_t b	:1;
		
	};
	uint16_t val;
}FPU_STATUS_WORD;

typedef union {
	struct {
		uint32_t im	:1;
		uint32_t dm	:1;
		uint32_t zm	:1;
		uint32_t om	:1;
		uint32_t um	:1;
		uint32_t pm	:1;
		uint32_t resv_0	:2;
		uint32_t pc	:2;
		uint32_t rc	:2;
		uint32_t x	:1;
		uint32_t resv_1	:3;
	};
	uint16_t val;
}FPU_CTRL_WORD;

typedef union {
	struct {
		uint32_t fraction	:23;
		uint32_t exponent	:8;
		uint32_t sign		:1;
	};
	float fval;
	uint32_t val;
}FLOAT;

typedef struct {
	FLOAT regStack[8];
	FPU_STATUS_WORD status;
	FPU_CTRL_WORD control;
}FPU;

#endif
