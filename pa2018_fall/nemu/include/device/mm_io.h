#ifndef __MM_IO_H__
#define __MM_IO_H__

#include "nemu.h"

typedef void(*mmio_callback_t)(uint32_t hwaddr, size_t len, bool isWrite);

void* add_mmio_map(uint32_t hwaddr, size_t len, mmio_callback_t callback);
void clear_mmio_map();
int is_mmio(uint32_t hwaddr);

uint32_t mmio_read(uint32_t hwaddr, size_t len, int map_NO);
void mmio_write(uint32_t hwaddr, size_t len, uint32_t data, int map_NO);

#endif
