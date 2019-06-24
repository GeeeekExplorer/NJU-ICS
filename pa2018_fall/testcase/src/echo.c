#include "trap.h"
#include <stdint.h>
#include <sys/syscall.h>

// read a byte from the port
uint8_t in_byte(uint16_t port) {
	uint8_t data;
	asm volatile("in %1, %0": "=a"(data) : "d"(port));
	return data;
}

// register a handle of interrupt request in the Kernel
void add_irq_handler(int irq, void *handler) {
	// refer to kernel/src/syscall/do_syscall.c to understand what has happened
	asm volatile("int $0x80" : : "a"(0), "b"(irq), "c"(handler));
}


void writec(int fd, char c) {
	asm volatile("int $0x80" : : "a"(SYS_write), "b"(fd), "c"(&c), "d"(1));
}

void printc(char c) {
	writec(1, c);
}

char translate_key(int scan_code);

// the keyboard event handler, called when an keyboard interrupt is fired
void keyboard_event_handler() {

	uint8_t key_pressed = in_byte(0x60);

	// translate scan code to ASCII
	char c = translate_key(key_pressed);
	if(c > 0) {
		// can you now fully understand Fig. 8.3 on pg. 317 of the text book?
		printc(c);
	}
	
}

int main() {
	// register for keyboard events
	add_irq_handler(1, keyboard_event_handler);
	while(1) asm volatile("hlt");
	return 0;
}

// scan code for letter a-z
static int letter_code[] = {
	30, 48, 46, 32, 18, 33, 34, 35, 23, 36,
	37, 38, 50, 49, 24, 25, 16, 19, 31, 20,
	22, 47, 17, 45, 21, 44
};

char translate_key(int scan_code) {
	int i;
	for (i = 0; i < 26; i ++) {
		if (letter_code[i] == scan_code) {
			return i+0x41;
		}
	}
	return 0;
}
