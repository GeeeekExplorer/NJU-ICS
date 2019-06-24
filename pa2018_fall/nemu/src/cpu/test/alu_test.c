#include "nemu.h"
#include "cpu/reg.h"
#include "cpu/cpu.h"
#include "cpu/intr.h"
#include "cpu/instr.h"
#include "cpu/instr_helper.h"
#include "memory/memory.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <scoring.h>

typedef union {
	struct {
		uint32_t CF :1;
		uint32_t dummy0 :1;
		uint32_t PF :1;
		uint32_t dummy1 :1;
		uint32_t AF :1;
		uint32_t dummy2: 1;
		uint32_t ZF :1;
		uint32_t SF :1;
		uint32_t TF :1;
		uint32_t IF :1;
		uint32_t DF :1;
		uint32_t OF :1;
		uint32_t OLIP :2;
		uint32_t NT :1;
		uint32_t dummy3 :1;
		uint32_t RF :1;
		uint32_t VM :1;
		uint32_t dummy4 :14;
	};
	uint32_t val;	
} TEST_EFLAGS;

#define assert_res_CPSZO(dataSize) \
		"pushf;" \
		"popl %%edx;" \
		: "=a" (res_asm), "=d" (res_eflags) \
		: "a" (a), "c" (b)); \
	test_eflags.val = res_eflags; \
	res_asm = res_asm & (0xFFFFFFFF >> (32 - dataSize)); \
	assert(res == res_asm); \
	assert(cpu.eflags.CF == test_eflags.CF); \
	assert(cpu.eflags.PF == test_eflags.PF); \
	assert(cpu.eflags.SF == test_eflags.SF); \
	assert(cpu.eflags.ZF == test_eflags.ZF); \
	assert(cpu.eflags.OF == test_eflags.OF); \

#define assert_res_CPSZ(dataSize) \
		"pushf;" \
		"popl %%edx;" \
		: "=a" (res_asm), "=d" (res_eflags) \
		: "a" (a), "c" (b)); \
	test_eflags.val = res_eflags; \
	res_asm = res_asm & (0xFFFFFFFF >> (32 - dataSize)); \
	assert(res == res_asm); \
	assert(cpu.eflags.CF == test_eflags.CF); \
	assert(cpu.eflags.PF == test_eflags.PF); \
	assert(cpu.eflags.SF == test_eflags.SF); \
	assert(cpu.eflags.ZF == test_eflags.ZF); \

#define internel_alu_test_CPSZO(alu_func, dataSize, asm_instr) \
	uint32_t res, res_asm, res_eflags;\
	TEST_EFLAGS test_eflags;\
	res = alu_func(b, a, dataSize);\
	asm (	asm_instr \
	assert_res_CPSZO(dataSize)

#define internel_alu_test_CPSZO_clc(alu_func, dataSize, asm_instr) \
	uint32_t res, res_asm, res_eflags;\
	TEST_EFLAGS test_eflags;\
	cpu.eflags.CF = 0; \
	res = alu_func(b, a, dataSize);\
	asm (	"clc;" \
		asm_instr \
	assert_res_CPSZO(dataSize)

#define internel_alu_test_CPSZO_stc(alu_func, dataSize, asm_instr) \
	uint32_t res, res_asm, res_eflags;\
	TEST_EFLAGS test_eflags;\
	cpu.eflags.CF = 1; \
	res = alu_func(b, a, dataSize);\
	asm (	"stc;" \
		asm_instr \
	assert_res_CPSZO(dataSize)

#define internel_alu_test_CPSZ(alu_func, dataSize, asm_instr) \
	uint32_t res, res_asm, res_eflags;\
	TEST_EFLAGS test_eflags;\
	res = alu_func(b, a, dataSize);\
	asm (	asm_instr \
	assert_res_CPSZ(dataSize)

void alu_test_add() {
	uint32_t a, b;
	int input[] = {0x10000000, -3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO(alu_add, 32, "addl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO(alu_add, 16, "addw %%cx, %%ax;")}
			{internel_alu_test_CPSZO(alu_add, 8 , "addb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO(alu_add, 32, "addl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO(alu_add, 16, "addw %%cx, %%ax;")}
		{internel_alu_test_CPSZO(alu_add, 8 , "addb %%cl, %%al;")}
	}
	printf("alu_test_add()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_adc() {
	uint32_t a, b;
	int input[] = {0x10000000,-3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO_clc(alu_adc, 32, "adcl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO_clc(alu_adc, 16, "adcw %%cx, %%ax;")}
			{internel_alu_test_CPSZO_clc(alu_adc, 8 , "adcb %%cl, %%al;")}
		}
	}

	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO_stc(alu_adc, 32, "adcl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO_stc(alu_adc, 16, "adcw %%cx, %%ax;")}
			{internel_alu_test_CPSZO_stc(alu_adc, 8 , "adcb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO_clc(alu_adc, 32, "adcl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO_clc(alu_adc, 16, "adcw %%cx, %%ax;")}
		{internel_alu_test_CPSZO_clc(alu_adc, 8 , "adcb %%cl, %%al;")}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO_stc(alu_adc, 32, "adcl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO_stc(alu_adc, 16, "adcw %%cx, %%ax;")}
		{internel_alu_test_CPSZO_stc(alu_adc, 8 , "adcb %%cl, %%al;")}
	}

	printf("alu_test_adc()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_sub() {
	uint32_t a, b;
	int input[] = {0x10000000,-3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO(alu_sub, 32, "subl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO(alu_sub, 16, "subw %%cx, %%ax;")}
			{internel_alu_test_CPSZO(alu_sub, 8 , "subb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO(alu_sub, 32, "subl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO(alu_sub, 16, "subw %%cx, %%ax;")}
		{internel_alu_test_CPSZO(alu_sub, 8 , "subb %%cl, %%al;")}
	}

	printf("alu_test_sub()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_sbb() {
	uint32_t a, b;
	uint32_t input[] = {0x10000000,-3, -2, -1, 0, 1, 2, 0x80000000};
	int n = sizeof(input) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO_clc(alu_sbb, 32, "sbbl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO_clc(alu_sbb, 16, "sbbw %%cx, %%ax;")}
			{internel_alu_test_CPSZO_clc(alu_sbb, 8 , "sbbb %%cl, %%al;")}
		}
	}

	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO_stc(alu_sbb, 32, "sbbl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO_stc(alu_sbb, 16, "sbbw %%cx, %%ax;")}
			{internel_alu_test_CPSZO_stc(alu_sbb, 8 , "sbbb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO_clc(alu_sbb, 32, "sbbl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO_clc(alu_sbb, 16, "sbbw %%cx, %%ax;")}
		{internel_alu_test_CPSZO_clc(alu_sbb, 8 , "sbbb %%cl, %%al;")}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO_stc(alu_sbb, 32, "sbbl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO_stc(alu_sbb, 16, "sbbw %%cx, %%ax;")}
		{internel_alu_test_CPSZO_stc(alu_sbb, 8 , "sbbb %%cl, %%al;")}
	}

	printf("alu_test_sbb()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}



void alu_test_and() {
	uint32_t a, b;
	int input[] = {0x10000000,-3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO(alu_and, 32, "andl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO(alu_and, 16, "andw %%cx, %%ax;")}
			{internel_alu_test_CPSZO(alu_and, 8 , "andb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO(alu_and, 32, "andl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO(alu_and, 16, "andw %%cx, %%ax;")}
		{internel_alu_test_CPSZO(alu_and, 8 , "andb %%cl, %%al;")}
	}

	printf("alu_test_and()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_or() {

	uint32_t a, b;
	int input[] = {0x10000000,-3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO(alu_or, 32, "orl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO(alu_or, 16, "orw %%cx, %%ax;")}
			{internel_alu_test_CPSZO(alu_or, 8 , "orb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO(alu_or, 32, "orl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO(alu_or, 16, "orw %%cx, %%ax;")}
		{internel_alu_test_CPSZO(alu_or, 8 , "orb %%cl, %%al;")}
	}
	
	printf("alu_test_or()   \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_xor() {
	uint32_t a, b;
	int input[] = {0x10000000,-3, -2, -1, 0, 1, 2};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			{internel_alu_test_CPSZO(alu_xor, 32, "xorl %%ecx, %%eax;")}
			{internel_alu_test_CPSZO(alu_xor, 16, "xorw %%cx, %%ax;")}
			{internel_alu_test_CPSZO(alu_xor, 8 , "xorb %%cl, %%al;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		{internel_alu_test_CPSZO(alu_xor, 32, "xorl %%ecx, %%eax;")}
		{internel_alu_test_CPSZO(alu_xor, 16, "xorw %%cx, %%ax;")}
		{internel_alu_test_CPSZO(alu_xor, 8 , "xorb %%cl, %%al;")}
	}

	printf("alu_test_xor()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_shl() {
	uint32_t a, b;
	uint32_t inputb[] = {1, 2, 3, 4};
	uint32_t inputa[] = {0xffffffff, 0x0, 0x10101010};
	int na = sizeof(inputa) / sizeof(uint32_t);
	int nb = sizeof(inputb) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < na ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = inputa[i];
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_shl,  8, "shlb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_shl, 16, "shlw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_shl, 32, "shll %%cl, %%eax;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = rand();
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_shl,  8, "shlb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_shl, 16, "shlw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_shl, 32, "shll %%cl, %%eax;")}
		}
	}

	printf("alu_test_shl()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_shr() {
	uint32_t a, b;
	uint32_t inputb[] = {1, 2, 3, 4};
	uint32_t inputa[] = {0xffffffff, 0x0, 0x10101010};
	int na = sizeof(inputa) / sizeof(uint32_t);
	int nb = sizeof(inputb) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < na ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = inputa[i];
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_shr,  8, "shrb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_shr, 16, "shrw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_shr, 32, "shrl %%cl, %%eax;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = rand();
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_shr,  8, "shrb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_shr, 16, "shrw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_shr, 32, "shrl %%cl, %%eax;")}
		}
	}
	printf("alu_test_shr()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_sal() {
	uint32_t a, b;
	uint32_t inputb[] = {1, 2, 3, 4};
	uint32_t inputa[] = {0xffffffff, 0x0, 0x10101010};
	int na = sizeof(inputa) / sizeof(uint32_t);
	int nb = sizeof(inputb) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < na ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = inputa[i];
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_sal,  8, "salb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_sal, 16, "salw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_sal, 32, "sall %%cl, %%eax;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = rand();
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_sal,  8, "salb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_sal, 16, "salw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_sal, 32, "sall %%cl, %%eax;")}
		}
	}

	printf("alu_test_sal()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_sar() {
	uint32_t a, b;
	uint32_t inputb[] = {1, 2, 3, 4};
	uint32_t inputa[] = {0xffffffff, 0x0, 0x10101010};
	int na = sizeof(inputa) / sizeof(uint32_t);
	int nb = sizeof(inputb) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < na ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = inputa[i];
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_sar,  8, "sarb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_sar, 16, "sarw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_sar, 32, "sarl %%cl, %%eax;")}
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		for(j = 0 ; j < nb ; j++) {
			a = rand();
			b = inputb[j];
			{internel_alu_test_CPSZ(alu_sar,  8, "sarb %%cl, %%al;")}
			{internel_alu_test_CPSZ(alu_sar, 16, "sarw %%cl, %%ax;")}
			{internel_alu_test_CPSZ(alu_sar, 32, "sarl %%cl, %%eax;")}
		}
	}
	printf("alu_test_sar()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_imul() {
	uint64_t res, temp_a, temp_d;
	uint32_t a, b, res_asm_a, res_asm_d, res_eflags;
	//TEST_EFLAGS test_eflags;
	int input[] = {-4,-3, -2, -1, 0, 1, 2, 3, 4, 0x0fffffff, 0xefffffff};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_imul(sign_ext(b, 8), sign_ext(a, 8), 8);

			asm (	"imulb %%cl;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=c" (res_eflags)
				: "a" (a & 0xff), "c" (b & 0xff));

			assert((int32_t) res == (int32_t) sign_ext(res_asm_a, 16));
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_imul(sign_ext(b, 8), sign_ext(a, 8), 8);

		asm (	"imulb %%cl;"
			"pushf;"
			"popl %%ecx;"
			: "=a" (res_asm_a), "=c" (res_eflags)
			: "a" (a & 0xff), "c" (b & 0xff));

			assert((int32_t) res == (int32_t) sign_ext(res_asm_a, 16));
	}

	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_imul(sign_ext(b, 16), sign_ext(a, 16), 16);

			asm (	"imulw %%cx;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a & 0xffff), "c" (b & 0xffff));

			assert((int32_t) res == (int32_t) ((res_asm_a & 0xffff) | ((res_asm_d & 0xffff) << 16)));
		}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_imul(sign_ext(b, 16), sign_ext(a, 16), 16);

		asm (	"imulw %%cx;"
			"pushf;"
			"popl %%ecx;"
			: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
			: "a" (a & 0xffff), "c" (b & 0xffff));
	
		assert((int32_t) res == (int32_t) ((res_asm_a & 0xffff) | ((res_asm_d & 0xffff) << 16)));
	}


	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_imul(b, a, 32);
			asm (	"imull %%ecx;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a), "c" (b));
	
			temp_a = res_asm_a;
			temp_d = res_asm_d;
			assert((int32_t) res == (int32_t) ((temp_a & 0xffffffff) | ((temp_d & 0xffffffff) << 32)));
		}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_imul(b, a, 32);
		asm (	"imull %%ecx;"
			"pushf;"
			"popl %%ecx;"
			: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
			: "a" (a), "c" (b));
	
		temp_a = res_asm_a;
		temp_d = res_asm_d;
		assert((int32_t) res == (int32_t) ((temp_a & 0xffffffff) | ((temp_d & 0xffffffff) << 32)));
	}

	printf("alu_test_imul() \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_mul() {
	uint64_t res, temp_a, temp_d;
	uint32_t a, b, res_asm_a, res_asm_d, res_eflags;
	TEST_EFLAGS test_eflags;
	int input[] = {0x1,-3, -2, -1, 0, 1, 2, 4, 5, 0xefffffff};
	int n = sizeof(input) / sizeof(int);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_mul(b, a, 32);
			asm (	"mull %%ecx;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a), "c" (b));
				test_eflags.val = res_eflags;
	
			temp_a = res_asm_a;
			temp_d = res_asm_d;
			assert(res == (temp_a | (temp_d << 32)));
			assert(cpu.eflags.CF == test_eflags.CF);
			assert(cpu.eflags.OF == test_eflags.OF);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_mul(b, a, 32);

		asm (	"mull %%ecx;"
			"pushf;"
			"popl %%ecx;"
			: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
			: "a" (a), "c" (b));
			test_eflags.val = res_eflags;
	
		temp_a = res_asm_a;
		temp_d = res_asm_d;
		assert(res == (temp_a | (temp_d << 32)));
		assert(cpu.eflags.CF == test_eflags.CF);
		assert(cpu.eflags.OF == test_eflags.OF);
	}


	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_mul(b & 0xffff, a & 0xffff, 16);

			asm (	"mulw %%cx;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a & 0xffff), "c" (b & 0xffff));
				test_eflags.val = res_eflags;
	
			assert(res == (res_asm_a | (res_asm_d << 16)));
			assert(cpu.eflags.CF == test_eflags.CF);
			assert(cpu.eflags.OF == test_eflags.OF);
		}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_mul(b & 0xffff, a & 0xffff, 16);

			asm (	"mulw %%cx;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a & 0xffff), "c" (b & 0xffff));
				test_eflags.val = res_eflags;
	
			assert(res == (res_asm_a | (res_asm_d << 16)));
			assert(cpu.eflags.CF == test_eflags.CF);
			assert(cpu.eflags.OF == test_eflags.OF);
	}

	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			res = alu_mul(b & 0xff, a & 0xff, 8);

			asm (	"mulb %%cl;"
				"pushf;"
				"popl %%ecx;"
				: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
				: "a" (a & 0xff), "c" (b & 0xff));
				test_eflags.val = res_eflags;
	
			assert(res == (res_asm_a | (res_asm_d << 8)));
			assert(cpu.eflags.CF == test_eflags.CF);
			assert(cpu.eflags.OF == test_eflags.OF);
		}
	}

	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		res = alu_mul(b & 0xff, a & 0xff, 8);

		asm (	"mulb %%cl;"
			"pushf;"
			"popl %%ecx;"
			: "=a" (res_asm_a), "=d" (res_asm_d), "=c" (res_eflags)
			: "a" (a & 0xff), "c" (b & 0xff));
			test_eflags.val = res_eflags;
	
		assert(res == (res_asm_a | (res_asm_d << 8)));
		assert(cpu.eflags.CF == test_eflags.CF);
		assert(cpu.eflags.OF == test_eflags.OF);
	}

	printf("alu_test_mul()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_idiv() {
	UINT64_T aa;
	uint64_t a, b;
	uint32_t quo, quo_asm, rem, rem_asm;
	uint32_t input[] = {-3, -2, -1, 1, 2, 3, 4};
	int n = sizeof(input) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = sign_ext_64(input[i], 32);
			b = sign_ext_64(input[j], 32);
			aa.val = a;
			quo = alu_idiv(b, a, 32);
			rem = alu_imod(b, a);
			asm ("idivl %%ecx" : "=a" (quo_asm), "=d" (rem_asm) : "a" (aa.low), "d" (aa.high), "c" ((uint32_t)b));
			assert(quo == quo_asm);
			assert(rem == rem_asm);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = sign_ext_64(rand(), 32);
		b = sign_ext_64(rand(), 32);
		if(b == 0) continue;
		aa.val = a;
		quo = alu_idiv(b, a, 32);
		rem = alu_imod(b, a);
		asm ("idivl %%ecx" : "=a" (quo_asm), "=d" (rem_asm) : "a" (aa.low), "d" (aa.high), "c" ((uint32_t)b));
		assert(quo == quo_asm);
		assert(rem == rem_asm);
	}

	printf("alu_test_idiv() \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}

void alu_test_div() {
	UINT64_T aa;
	uint64_t a;
	uint32_t b;
	uint32_t quo, quo_asm, rem, rem_asm;
	uint32_t input[] = {-3, -2, -1, 1, 2, 3, 4};
	int n = sizeof(input) / sizeof(uint32_t);
	int i, j;
	for(i = 0 ; i < n ; i++) {
		for(j = 0 ; j < n ; j++) {
			a = input[i];
			b = input[j];
			aa.val = a;
			quo = alu_div(b, a, 32);
			rem = alu_mod(b, a);
			asm ("divl %%ecx" : "=a" (quo_asm), "=d" (rem_asm) : "a" (aa.low), "d" (aa.high), "c" ((uint32_t)b));
			assert(quo == quo_asm);
			assert(rem == rem_asm);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a = rand();
		b = rand();
		if(b == 0) continue;
		aa.val = a;
		quo = alu_div(b, a, 32);
		rem = alu_mod(b, a);
		asm ("divl %%ecx" : "=a" (quo_asm), "=d" (rem_asm) : "a" (aa.low), "d" (aa.high), "c" ((uint32_t)b));
		assert(quo == quo_asm);
		assert(rem == rem_asm);
	}

	printf("alu_test_div()  \e[0;32mpass\e[0m\n");
	if( get_ref() ) printf("\e[0;31mYou have used reference implementations, DO NOT submit this version!\e[0m\n");
}
