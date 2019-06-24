#include "common.h"

/* This function is defined only to make the newlibc linkable.
 * Without it, errors will be reported during linking.
 * But the execution flow should not reach here.
 */
void* sbrk(int incr) {
	assert(0);
	return NULL;
}
