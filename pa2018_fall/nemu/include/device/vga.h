#ifndef __VGA_H__
#define __VGA_H__

#include "nemu.h"
#include "device/port_io.h"
#include <SDL/SDL.h>

#define SCREEN_ROW 400
#define SCREEN_COL 640
#define VGA_HZ 25

#define VGA_DAC_READ_INDEX 0x3C7
#define VGA_DAC_WRITE_INDEX 0x3C8
#define VGA_DAC_DATA 0x3C9

#define VGA_CRTC_INDEX		0x3D4
#define VGA_CRTC_DATA		0x3D5

extern SDL_Surface *real_screen;
extern SDL_Surface *screen;

extern uint8_t (*pixel_buf) [SCREEN_COL];

static inline void draw_pixel(int x, int y, uint8_t color_idx) {
	assert(x >= 0 && x < SCREEN_COL && y >= 0 && y < SCREEN_ROW);
	pixel_buf[y][x] = color_idx;
}

typedef union {
	uint32_t val;
	struct { 
		uint8_t r, g, b, a;
	};
} Color;

extern Color palette[];

void update_screen();
void vga_init();
void vga_close();



make_pio_handler(vga_dac_io_handler);
make_pio_handler(vga_crtc_io_handler);

#endif
