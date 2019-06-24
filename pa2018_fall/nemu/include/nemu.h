#ifndef __NEMU2_H__
#define __NEMU2_H__

#include "macro.h"
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <config.h>

enum {NEMU_STOP, NEMU_RUN, NEMU_READY, NEMU_BREAK};

extern int nemu_state;

typedef uint8_t bool;
typedef uint32_t paddr_t;
typedef uint32_t laddr_t;
typedef uint32_t vaddr_t;

typedef uint16_t ioaddr_t;

extern bool verbose;

typedef union {
	struct {
		uint32_t low;
		uint32_t high;
	};
	uint64_t val;
} UINT64_T;

#define true 1
#define false 0

inline static void memcpy_with_mask(void *dest, const void *src, size_t len, uint8_t *mask) {
	int i;
	for(i = 0; i < len; i ++) {
		if(mask[i]) {
			((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
		}
	}
}

#endif
