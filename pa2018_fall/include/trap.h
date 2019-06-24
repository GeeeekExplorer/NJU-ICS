#ifndef __TRAP_H__
#define __TRAP_H__

#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)

#ifndef __ASSEMBLER__

#define HIT_GOOD_TRAP \
	asm volatile(".byte 0x82" : : "a" (0))

#define HIT_BAD_TRAP \
	asm volatile(".byte 0x82" : : "a" (1))

#define CHECK_POINT \
	asm volatile(".byte 0x82" : : "a" (110))

#define nemu_assert(cond) \
	do { \
		if( !(cond) ) HIT_BAD_TRAP; \
	} while(0);

#define BREAK_POINT \
	asm volatile(".byte 0xF1");

#else

#define HIT_GOOD_TRAP \
	movl $0, %eax; \
	.byte 0x82

#define HIT_BAD_TRAP \
	movl $1, %eax; \
	.byte 0x82

#define CHECK_POINT \
	movl $110, %eax; \
	.byte 0x82

#define nemu_assert(reg, val) \
	cmp $val, %reg; \
	je concat(label,__LINE__); HIT_BAD_TRAP; concat(label,__LINE__):

#define BREAK_POINT \
	.byte 0xF1

#endif

#endif
