#ifndef __PORT_IO_H__
#define __PORT_IO_H__

#include "nemu.h"

// macro for making a port io handler
#define make_pio_handler(name) void name(uint16_t port, size_t len, bool is_write)

// port io handler
typedef void (*pio_handler)(uint16_t port, size_t len, bool is_write);

// called by the out instruction
void pio_write(uint16_t port, size_t len, uint32_t data);

// called by the in instruction
uint32_t pio_read(uint16_t port, size_t len);

// write value to an io port, internal use only
void write_io_port(uint16_t port, size_t len, uint32_t data);

// read value from an io port, internal use only
uint32_t read_io_port(uint16_t port, size_t len);

#endif
