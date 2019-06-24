#include "nemu.h"
#include "device/port_io.h"
#include "device/ide.h"
#include "device/keyboard.h"
#include "device/serial.h"
#include "device/timer.h"
#include "device/vga.h"
#include "device/audio.h"
// references
// http://wiki.osdev.org/I/O_Ports
// http://bochs.sourceforge.net/techspec/PORTS.LST

#define IO_PORT_SPACE 65536
static uint8_t io_port[IO_PORT_SPACE];

static struct pio_handler_map {
	uint16_t port;
	pio_handler handler;
} pio_handler_table [] = { 

#ifdef HAS_DEVICE_IDE
	//{BMR_PORT_BASE + 0, handler_bmr},
	//{BMR_PORT_BASE + 1, handler_bmr},
	//{BMR_PORT_BASE + 2, handler_bmr},
	//{BMR_PORT_BASE + 3, handler_bmr},
	//{BMR_PORT_BASE + 4, handler_bmr},
	//{BMR_PORT_BASE + 5, handler_bmr},
	//{BMR_PORT_BASE + 6, handler_bmr},
	//{BMR_PORT_BASE + 7, handler_bmr},

	{IDE_PORT_BASE + 0, handler_ide},
	{IDE_PORT_BASE + 1, handler_ide},
	{IDE_PORT_BASE + 2, handler_ide},
	{IDE_PORT_BASE + 3, handler_ide},
	{IDE_PORT_BASE + 4, handler_ide},
	{IDE_PORT_BASE + 5, handler_ide},
	{IDE_PORT_BASE + 6, handler_ide},
	{IDE_PORT_BASE + 7, handler_ide},
#endif

#ifdef HAS_DEVICE_KEYBOARD
	{KEYBOARD_DATA_PORT, handler_keyboard_data},
#endif

#ifdef HAS_DEVICE_SERIAL
	{SERIAL_PORT + 0, handler_serial},
	{SERIAL_PORT + 1, handler_serial},
	{SERIAL_PORT + 2, handler_serial},
	{SERIAL_PORT + 3, handler_serial},
	{SERIAL_PORT + 4, handler_serial},
	{SERIAL_PORT + 5, handler_serial},
	{SERIAL_PORT + 6, handler_serial},
	{SERIAL_PORT + 7, handler_serial},
#endif

#ifdef HAS_DEVICE_TIMER
	{TIMER_PORT + 0, handler_timer},
	{TIMER_PORT + 1, handler_timer},
	{TIMER_PORT + 2, handler_timer},
	{TIMER_PORT + 3, handler_timer},
#endif

#ifdef HAS_DEVICE_VGA
	{VGA_DAC_READ_INDEX, vga_dac_io_handler},
	{VGA_DAC_WRITE_INDEX, vga_dac_io_handler},
	{VGA_DAC_DATA, vga_dac_io_handler},
	{VGA_CRTC_INDEX, vga_crtc_io_handler},
	{VGA_CRTC_DATA, vga_crtc_io_handler},
#endif

#ifdef HAS_DEVICE_AUDIO
	{AUDIO_DATA, audio_io_handler},
	{AUDIO_CTL, audio_io_handler}
#endif
};

#define NR_PIO_ENTRY (sizeof(pio_handler_table) / sizeof(pio_handler_table[0]))

// called by the out instruction
void pio_write(uint16_t port, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	write_io_port(port, len, data);
	int i = 0;
	for(; i < NR_PIO_ENTRY ; i++) {
		if(pio_handler_table[i].port == port) {
			pio_handler_table[i].handler(port, len, true);
			break;
		}
	}
	if(i >= NR_PIO_ENTRY) {
		printf("PIO Write invalid port No. %d(0x%x)\n", port, port);
		assert(0);
	}
}

// called by the in instruction
uint32_t pio_read(uint16_t port, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	// call device read to put data into the port
	int i = 0;
	for(; i < NR_PIO_ENTRY ; i++) {
		if(pio_handler_table[i].port == port) {
			pio_handler_table[i].handler(port, len, false);
			break;
		}
	}
	if(i >= NR_PIO_ENTRY) {
		printf("PIO read invalid port No. %d(0x%x)\n", port, port);
		assert(0);
	}
	return read_io_port(port, len);
}

void write_io_port(uint16_t port, size_t len, uint32_t data) {
	memcpy(&(io_port[port]), &data, len);
}

uint32_t read_io_port(uint16_t port, size_t len) {
	uint32_t data = 0;
	memcpy(&data, &(io_port[port]), len);
	return data;
}
