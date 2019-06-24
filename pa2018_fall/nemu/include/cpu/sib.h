#ifndef __SIB_H__
#define __SIB_H__

#include "nemu.h"
#include "cpu/operand.h"

typedef union {
	struct {
		uint32_t base :3;
		uint32_t index :3;
		uint32_t ss :2;
	};
	uint8_t val;
}SIB;


// given the sib byte, parse it and obtain the address
//uint32_t parse_sib(SIB s);
//int parse_sib(uint32_t eip, uint32_t mod, uint32_t * sibaddr, uint8_t * sibsreg);
int parse_sib(uint32_t eip, uint32_t mod, OPERAND * opr);

#endif
