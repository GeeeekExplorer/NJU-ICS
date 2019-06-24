#include "nemu.h"
#include "device/timer.h"
#include "device/i8259_pic.h"

#include <SDL/SDL.h>

static bool timer_active = false;

void timer_intr() {
	if(nemu_state == NEMU_RUN) {
		i8259_raise_intr(TIMER_IRQ); // multi-thread safe
	}
}

static int TIMER_Thread(void* hz) {
	int delay = 1000 / *(int*)hz;
	while(timer_active) {
		timer_intr();
		SDL_Delay(delay);
	}
	return 0;
}

// start a timer with hz Hz
void timer_start(int hz) {
	timer_active = true;
	SDL_CreateThread(TIMER_Thread, (void*) &hz);
}

void timer_stop() {
	timer_active = false;
}

make_pio_handler(handler_timer) {}
