#include "common.h"
#include "x86.h"

#define SERIAL_PORT  0x3F8

void
init_serial(void) {}

static inline int
serial_idle(void) {
	return (in_byte(SERIAL_PORT + 5) & 0x20) != 0;
}

void
serial_printc(char ch) {
	while (!serial_idle()); // wait untile serial is idle
	// print 'ch' via out instruction here
	// HIT_BAD_TRAP;
	out_byte(SERIAL_PORT, ch);
}
