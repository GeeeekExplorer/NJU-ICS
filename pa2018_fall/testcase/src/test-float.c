#include "trap.h"

int main() {

	float a = 1.2, b = 1;
	float c = a + b;
	if(c == 2.2)
		;
	else
		HIT_BAD_TRAP;
	c = a * b;
	if(c == 1.2)
		;
	else
		HIT_BAD_TRAP;

	c = a / b;
	if(c == 1.2)
		;
	else
		HIT_BAD_TRAP;

	c = a - b;
	if(c == 0.2) // this will fail, and also fails for native program, interesting, can be used as a quiz
		;
	else
		HIT_BAD_TRAP;

	
	HIT_GOOD_TRAP;
	return 0;
}
