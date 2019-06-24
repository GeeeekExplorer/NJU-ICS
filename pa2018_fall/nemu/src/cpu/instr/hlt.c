#include "cpu/instr.h"

#include <SDL/SDL.h>

static int HLT_Thread(void * ptr) {
#ifdef HAS_DEVICE_TIMER
	while(!cpu.intr && nemu_state != NEMU_STOP) {
		SDL_Delay(1);
	}
#endif
	return 0;
}

make_instr_func(hlt) {
	SDL_Thread *thread;
	print_asm_0("hlt", "", 1);
	thread = SDL_CreateThread(HLT_Thread, (void *)NULL);

	if (NULL == thread) {
		printf("\nSDL_CreateThread for HLT failed: %s\n", SDL_GetError());
	} else {
		SDL_WaitThread(thread, NULL);
	}
	return 1;
}
