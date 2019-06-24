#include "nemu.h"
#include "cpu/fpu.h"
#include <stdlib.h>
#include <time.h>

static FLOAT p_zero, n_zero, p_inf, n_inf, p_nan, n_nan, denorm_1, denorm_2, denorm_3, big_1, big_2, small_1, small_2;

void fpu_test_add() {
	float input[] = {
		p_zero.fval, n_zero.fval, p_inf.fval, n_inf.fval, denorm_1.fval, denorm_2.fval, big_1.fval, big_2.fval,
		p_nan.fval, n_nan.fval, denorm_3.fval, small_1.fval, small_2.fval,
		10000000, 1.2, 1.1, 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8, -0.9, -1, -10000000};
	FLOAT a, b, res, res_fpu;
	int i, j;
	// int count = 0;
	for(i = 0 ; i < sizeof(input)/sizeof(float) ; i++) {
		for(j = 0 ; j < sizeof(input)/sizeof(float) ; j++) {
			// printf(" == %d ==\n", count++);
			a.fval = input[i];
			b.fval = input[j];
			res.fval = a.fval + b.fval;
			res_fpu.val = internal_float_add(b.val, a.val);
			//printf("float add a = %f, b = %f, ua = %x, ub = %x, res = %x, res_fpu = %x, res = %f, res_fpu = %f\n", a.fval, b.fval, a.val, b.val, res.val, res_fpu.val, res.fval, res_fpu.fval);
			assert(res_fpu.val == res.val);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a.val = rand();
		b.val = rand();
		if(a.exponent == 0xff || b.exponent == 0xff) continue;
		res.fval = a.fval + b.fval;
		res_fpu.val = internal_float_add(b.val, a.val);
		assert(res_fpu.val == res.val);
	}
	printf("fpu_test_add()  \e[0;32mpass\e[0m\n");
}

void fpu_test_sub() {
	float input[] = {
		p_zero.fval, n_zero.fval, p_inf.fval, n_inf.fval, denorm_1.fval, denorm_2.fval, big_1.fval, big_2.fval,
		p_nan.fval, n_nan.fval, denorm_3.fval, small_1.fval, small_2.fval,
		10000000, 1.2, 1.1, 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8, -0.9, -1, -10000000};
	FLOAT a, b, res, res_fpu;
	int i, j;
	// int count = 0;
	for(i = 0 ; i < sizeof(input)/sizeof(float) ; i++) {
		for(j = 0 ; j < sizeof(input)/sizeof(float) ; j++) {
			// printf(" == %d ==\n", count++);
			a.fval = input[i];
			b.fval = input[j];
			res.fval = a.fval - b.fval;
			res_fpu.val = internal_float_sub(b.val, a.val);
			//printf("float sub a = %f, b = %f, ua = %x, ub = %x, res = %x, res_fpu = %x, res = %f, res_fpu = %f\n", a.fval, b.fval, a.val, b.val, res.val, res_fpu.val, res.fval, res_fpu.fval);
			assert(res_fpu.val == res.val);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a.val = rand();
		b.val = rand();
		if(a.exponent == 0xff || b.exponent == 0xff) continue;
		res.fval = a.fval - b.fval;
		res_fpu.val = internal_float_sub(b.val, a.val);
		assert(res_fpu.val == res.val);
	}
	printf("fpu_test_sub()  \e[0;32mpass\e[0m\n");
}

void fpu_test_div() {
	float input[] = {
		p_zero.fval, n_zero.fval, p_inf.fval, n_inf.fval, denorm_1.fval, denorm_2.fval, big_1.fval, big_2.fval,
		p_nan.fval, n_nan.fval, denorm_3.fval, small_1.fval, small_2.fval,
		10000000, 1.2, 1.1, 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8, -0.9, -1, -10000000};

	
	FLOAT a, b, res, res_fpu;

	int i, j;
	//int count = 0;
	for(i = 0 ; i < sizeof(input)/sizeof(float) ; i++) {
		for(j = 0 ; j < sizeof(input)/sizeof(float) ; j++) {
			//printf(" == %d ==\n", count++);
			a.fval = input[i];
			b.fval = input[j];
			res.fval = a.fval / b.fval;
			res_fpu.val = internal_float_div(b.val, a.val);
			//printf("float div a = %f, b = %f, ua = %x, ub = %x, res = %x, res_fpu = %x, res = %f, res_fpu = %f\n", a.fval, b.fval, a.val, b.val, res.val, res_fpu.val, res.fval, res_fpu.fval);
			//printf("a       sign %x, exp %x, %d, sig %x\n", a.sign, a.exponent, a.exponent, a.significand);
			//printf("b       sign %x, exp %x, %d, sig %x\n", b.sign, b.exponent, b.exponent, b.significand);
			//printf("res     sign %x, exp %x, %d, sig %x\n", res.sign, res.exponent, res.exponent, res.significand);
			//printf("res_fpu sign %x, exp %x, %d, sig %x\n", res_fpu.sign, res_fpu.exponent, res_fpu.exponent, res_fpu.significand);
			assert(res_fpu.val == res.val || res.val - res_fpu.val == 1);
		}
	}


	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a.val = rand();
		b.val = rand();
		if(a.exponent == 0xff || b.exponent == 0xff) continue;
		if(b.fval == 0) continue;
		res.fval = a.fval / b.fval;
		res_fpu.val = internal_float_div(b.val, a.val);
		assert(res_fpu.val == res.val || res.val - res_fpu.val == 1);
	}
	printf("fpu_test_div()  \e[0;32mpass\e[0m\n");
}

void fpu_test_mul() {
	float input[] = {
		p_zero.fval, n_zero.fval, p_inf.fval, n_inf.fval, denorm_1.fval, denorm_2.fval, big_1.fval, big_2.fval,
		p_nan.fval, n_nan.fval, denorm_3.fval, small_1.fval, small_2.fval,
		10000000, 1.2, 1.1, 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8, -0.9, -1, -10000000};
	FLOAT a, b, res, res_fpu;
	int i, j;
	//int count = 0;
	for(i = 0 ; i < sizeof(input)/sizeof(float) ; i++) {
		for(j = 0 ; j < sizeof(input)/sizeof(float) ; j++) {
			//printf(" == %d ==\n", count++);
			a.fval = input[i];
			b.fval = input[j];
			res.fval = a.fval * b.fval;
			res_fpu.val = internal_float_mul(b.val, a.val);
			//printf("float mul a = %f, b = %f, ua = %x, ub = %x, res = %x, res_fpu = %x, res = %f, res_fpu = %f\n", a.fval, b.fval, a.val, b.val, res.val, res_fpu.val, res.fval, res_fpu.fval);
			//printf("a       sign %x, exp %x, %d, sig %x\n", a.sign, a.exponent, a.exponent, a.significand);
			//printf("b       sign %x, exp %x, %d, sig %x\n", b.sign, b.exponent, b.exponent, b.significand);
			//printf("res     sign %x, exp %x, %d, sig %x\n", res.sign, res.exponent, res.exponent, res.significand);
			//printf("res_fpu sign %x, exp %x, %d, sig %x\n", res_fpu.sign, res_fpu.exponent, res_fpu.exponent, res_fpu.significand);
			assert(res_fpu.val == res.val);
		}
	}

	srand(time(0));
	for(i = 0 ; i < 1000000 ; i++) {
		a.val = rand();
		b.val = rand();
		if(a.exponent == 0xff || b.exponent == 0xff) continue;
		res.fval = a.fval * b.fval;
		res_fpu.val = internal_float_mul(b.val, a.val);
		assert(res_fpu.val == res.val);
	}
	printf("fpu_test_mul()  \e[0;32mpass\e[0m\n");
}

void init_fpu_test() {
	p_zero.sign = 0; p_zero.exponent = 0; p_zero.fraction = 0;
	n_zero.sign = 1; n_zero.exponent = 0; n_zero.fraction = 0;
	p_inf.sign = 0; p_inf.exponent = 255; p_zero.fraction = 0;
	n_inf.sign = 1; n_inf.exponent = 255; n_zero.fraction = 0;
	p_nan.sign = 0; p_nan.exponent = 255; p_nan.fraction = 0x400000;
	n_nan.sign = 1; n_nan.exponent = 255; n_nan.fraction = 0x400000;
	denorm_1.sign = 0; denorm_1.exponent = 0; denorm_1.fraction = 1;
	denorm_2.sign = 0; denorm_2.exponent = 0; denorm_2.fraction = 2;
	denorm_3.sign = 1; denorm_3.exponent = 0; denorm_3.fraction = 0x400000;
	small_1.sign = 0; small_1.exponent = 1; small_1.fraction = 0;
	small_2.sign = 0; small_2.exponent = 1; small_2.fraction = 1;
	big_1.sign = 0; big_1.exponent = 254; big_1.fraction = 1;
	big_2.sign = 1; big_2.exponent = 254; big_2.fraction = 1;
}

/*
void fpu_test() {
	printf("\n======== fpu test ========\n");
	p_zero.sign = 0; p_zero.exponent = 0; p_zero.fraction = 0;
	n_zero.sign = 1; n_zero.exponent = 0; n_zero.fraction = 0;
	p_inf.sign = 0; p_inf.exponent = 255; p_zero.fraction = 0;
	n_inf.sign = 1; n_inf.exponent = 255; n_zero.fraction = 0;
	p_nan.sign = 0; p_nan.exponent = 255; p_nan.fraction = 0x400000;
	n_nan.sign = 1; n_nan.exponent = 255; n_nan.fraction = 0x400000;
	denorm_1.sign = 0; denorm_1.exponent = 0; denorm_1.fraction = 1;
	denorm_2.sign = 0; denorm_2.exponent = 0; denorm_2.fraction = 2;
	denorm_3.sign = 1; denorm_3.exponent = 0; denorm_3.fraction = 0x400000;
	small_1.sign = 0; small_1.exponent = 1; small_1.fraction = 0;
	small_2.sign = 0; small_2.exponent = 1; small_2.fraction = 1;
	big_1.sign = 0; big_1.exponent = 254; big_1.fraction = 1;
	big_2.sign = 1; big_2.exponent = 254; big_2.fraction = 1;
	fpu_test_add();
	fpu_test_sub();
	fpu_test_mul();
	fpu_test_div();
}
*/
