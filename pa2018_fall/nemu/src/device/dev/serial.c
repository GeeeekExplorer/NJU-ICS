#include "nemu.h"
#include "device/serial.h"


make_pio_handler(handler_serial) {
	if(is_write) {
		assert(len == 1);
#ifdef HAS_DEVICE_SERIAL
		if(port == SERIAL_PORT) { // offset == 0
			char c = (char)read_io_port(port, 1);
			putc(c, stdout);
			fflush(stdout);
		}
#endif
	}
}

void init_serial() {
	// serial port always free
	write_io_port(SERIAL_PORT + 5, 1, 0x20);
}
