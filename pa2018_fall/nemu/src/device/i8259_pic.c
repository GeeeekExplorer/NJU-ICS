#include "nemu.h"
#include "cpu/cpu.h"
#include "device/i8259_pic.h"

#include <SDL/SDL.h>

static uint8_t i8259_intr_no = I8259_NO_INTR;

static SDL_mutex* i8259_mutex;

uint8_t i8259_query_intr_no() {
	return i8259_intr_no;
}

void i8259_raise_intr(uint8_t irq_no) { 
	// this is the only place i8259_intr_no and cpu.intr is set
	while(SDL_LockMutex(i8259_mutex) != 0) {
		if(nemu_state == NEMU_STOP) return;
		SDL_Delay(1);
	}
	// the i8259_mutex is to protect the i8259_intr_no and cpu.intr
	if(i8259_intr_no == I8259_NO_INTR ||
		       	(i8259_intr_no != I8259_NO_INTR && irq_no > i8259_intr_no - IRQ_BASE)) {
		// priority
		i8259_intr_no = irq_no + IRQ_BASE;
		//printf("i8259 raise %d, %d\n", irq_no, i8259_intr_no);
	}
#ifdef IA32_INTR
	cpu.intr = 1;
#endif
	SDL_UnlockMutex(i8259_mutex); // unlock
}

void i8259_ack_intr() {
	while(SDL_LockMutex(i8259_mutex) != 0) {
		if(nemu_state == NEMU_STOP) return;
		SDL_Delay(1);
	}
	i8259_intr_no = I8259_NO_INTR;
#ifdef IA32_INTR
	cpu.intr = 0;
#endif
	SDL_UnlockMutex(i8259_mutex); // unlock
}

void i8259_init() {
	i8259_mutex = SDL_CreateMutex();
	i8259_intr_no = I8259_NO_INTR;
	assert(i8259_mutex);
}

void i8259_destroy() {
	SDL_DestroyMutex(i8259_mutex);
}
