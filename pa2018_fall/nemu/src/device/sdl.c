#include "nemu.h"
#include "device/vga.h"
#include "device/audio.h"
#include "device/timer.h"
#include "device/keyboard.h"
#include <SDL/SDL.h>


#if defined(HAS_DEVICE_TIMER) || defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD) || defined(HAS_DEVICE_AUDIO)

#ifdef HAS_DEVICE_VGA
extern uint8_t fontdata_8x16[128][16];
SDL_Surface *screen;
uint8_t (*pixel_buf) [SCREEN_COL];
#endif

SDL_Surface *real_screen;

#define SDL_HZ 100
static bool initialized = false;




#if defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD) 
static void init_sdl_window() {
	#ifdef HAS_DEVICE_AUDIO
	int ret = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER| SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
	#else
	int ret = SDL_Init(SDL_INIT_TIMER| SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
	#endif
	assert(ret == 0);
	real_screen = SDL_SetVideoMode(640, 400, 8, 
			SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_ASYNCBLIT);

	#ifdef HAS_DEVICE_VGA
	screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 400, 8,
			real_screen->format->Rmask, real_screen->format->Gmask,
			real_screen->format->Bmask, real_screen->format->Amask);
	pixel_buf = screen->pixels;

	SDL_SetPalette(real_screen, SDL_LOGPAL | SDL_PHYSPAL, (void *)&palette, 0, 256);
	SDL_SetPalette(screen, SDL_LOGPAL, (void *)&palette, 0, 256);
	#endif
	SDL_WM_SetCaption("NEMU v3.0", NULL);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

}
#endif

void close_sdl() {
	if(initialized) {
		initialized = false;
		#ifdef HAS_DEVICE_TIMER 
		timer_stop();
		#endif

		#ifdef HAS_DEVICE_KEYBOARD
		keyboard_stop();
		#endif

		#ifdef HAS_DEVICE_VGA
		vga_close();
		#endif

		#ifdef HAS_DEVICE_AUDIO
		audio_stop();
		#endif

		#if defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD)
		//Destroy the various items
		SDL_Quit();
		#endif
	}
}

void init_sdl() {
	if(!initialized) {
		#ifdef HAS_DEVICE_TIMER 
		timer_start(100); // start timer
		#endif

		#if defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD)
		init_sdl_window();

			#ifdef HAS_DEVICE_KEYBOARD
			keyboard_start(); // start keyboard
			#endif

			#ifdef HAS_DEVICE_VGA
			vga_init(); // init vga
			#endif

		#endif

		#ifdef HAS_DEVICE_AUDIO
		audio_start();
		#endif

		initialized = true;
	}

}
#endif
