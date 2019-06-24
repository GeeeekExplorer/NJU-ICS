#include "nemu.h"
#include <config.h>
#include "test/reg_alu_fpu_test.h"
#include <test/reg_alu_fpu_test_score.h>
#include <stdio.h>

char image_path[500];
char elf_path[500];
char image_path_score[500];
char elf_path_score[500];
bool flag_autorun = false;
bool flag_reg_alu_fpu = false;
bool flag_score = false;
bool flag_score_expr = false;
void (*builtin_test_func)(); // test function for reg, alu, fpu
void (*builtin_score_func)();

static bool flag_kernel = false;
static bool flag_game = false;
static bool flag_testcase = false;

static bool main_arg_expr_score() {
	flag_score_expr = true;
	return true;
}

static bool main_arg_testcase(char * testcase) {
	if(strcmp(testcase, "no_argument") == 0) { 
		printf("\n\nError: must specify a valid testcase after --testcase\n\n");
		return false;
	}
	if(!flag_kernel) { // skip if kernel img is already set
		strcpy(image_path, "./testcase/bin/");
		strcat(image_path, testcase);
		strcat(image_path, ".img");
	}
	strcpy(elf_path, "./testcase/bin/");
	strcat(elf_path, testcase);
	// config score path
	if(!flag_kernel) { // skip if kernel img is already set
		strcpy(image_path_score, "./scripts/score_testcases/");
		strcat(image_path_score, testcase);
		strcat(image_path_score, ".img");
	}
	strcpy(elf_path_score, "./scripts/score_testcases/");
	strcat(elf_path_score, testcase);
	flag_testcase = true;
	return true;
}

static bool main_arg_score(char * noUse) {
	flag_score = true;
	return true;
}

static bool main_arg_reg_test(char * noUse) {
	builtin_test_func = reg_test;
	builtin_score_func = __score_reg_test;
	flag_reg_alu_fpu = true;
	return true;
}

static struct alu_operation_map {
	char * operation;
	void (*alu_test_func)();
	void (*alu_score_func)();
} alu_operation_list[] = {
	{"add" , alu_test_add , __score_alu_test_add},
	{"adc" , alu_test_adc , __score_alu_test_adc},
	{"sub" , alu_test_sub , __score_alu_test_sub},
	{"sbb" , alu_test_sbb , __score_alu_test_sbb},
	{"and" , alu_test_and , __score_alu_test_and},
	{"or"  , alu_test_or  , __score_alu_test_or },
	{"xor" , alu_test_xor , __score_alu_test_xor},
	{"shl" , alu_test_shl , __score_alu_test_shl},
	{"shr" , alu_test_shr , __score_alu_test_shr},
	{"sal" , alu_test_sal , __score_alu_test_sal},
	{"sar" , alu_test_sar , __score_alu_test_sar},
	{"mul" , alu_test_mul , __score_alu_test_mul},
	{"div" , alu_test_div , __score_alu_test_div},
	{"imul", alu_test_imul, __score_alu_test_imul},
	{"idiv", alu_test_idiv, __score_alu_test_idiv}
};
#define NR_ALU_OPERATION_TEST (sizeof(alu_operation_list) / sizeof(alu_operation_list[0]))
static bool main_arg_alu_test(char * operation) {
	int i = 0;
	for(i = 0; i < NR_ALU_OPERATION_TEST; i++) {
		if(0 == strcmp(operation, alu_operation_list[i].operation)) {
			builtin_test_func = alu_operation_list[i].alu_test_func;
			builtin_score_func = alu_operation_list[i].alu_score_func;
			break;
		}
	}
	if(i >= NR_ALU_OPERATION_TEST) {
		printf("\n\nError: there is no ALU operation '%s'\n\n", operation);
		return false;
	}
	flag_reg_alu_fpu = true;
	return true;
}

static struct fpu_operation_map {
	char * operation;
	void (*fpu_test_func)();
	void (*fpu_score_func)();
} fpu_operation_list[] = {
	{"add" , fpu_test_add , __score_fpu_test_add},
	{"sub" , fpu_test_sub , __score_fpu_test_sub},
	{"mul" , fpu_test_mul , __score_fpu_test_mul},
	{"div" , fpu_test_div , __score_fpu_test_div},
};
#define NR_FPU_OPERATION_TEST (sizeof(fpu_operation_list) / sizeof(fpu_operation_list[0]))
static bool main_arg_fpu_test(char * operation) {
	init_fpu_test(); // init fpu test
	__score_init_fpu_test();
	int i = 0;
	for(i = 0; i < NR_FPU_OPERATION_TEST; i++) {
		if(0 == strcmp(operation, fpu_operation_list[i].operation)) {
			builtin_test_func = fpu_operation_list[i].fpu_test_func;
			builtin_score_func = fpu_operation_list[i].fpu_score_func;
			break;
		}
	}
	if(i >= NR_FPU_OPERATION_TEST) {
		printf("\n\nError: there is no FPU operation '%s'\n\n", operation);
		return false;
	}
	flag_reg_alu_fpu = true;
	return true;
}

static bool main_arg_game(char * noUse) {
	strcpy(elf_path, "./game/game");
	strcpy(elf_path_score, "./scripts/score_testcases/game");
	flag_game = true;
	return true;
}

static bool main_arg_kernel(char * noUse) {
	strcpy(image_path, "./kernel/kernel.img");
	strcpy(image_path_score, "./kernel/kernel.img");
	flag_kernel = true;
	return true;
}

static bool main_arg_autorun(char * noUse) {
	flag_autorun = true;
	return true;
}

static struct main_arguments {
	char * arg;
	bool (*handler)(char *);
	int numArgs;
} main_args_list[] = {
	{"--testcase", main_arg_testcase, 1},
	{"--score", main_arg_score, 0},
	{"--test-reg", main_arg_reg_test, 0},
	{"--test-alu", main_arg_alu_test, 1},
	{"--test-fpu", main_arg_fpu_test, 1},
	{"--test-game", main_arg_game, 0},
	{"--kernel", main_arg_kernel, 0},
	{"--autorun", main_arg_autorun, 0},
	{"--test-expr-score" ,main_arg_expr_score, 0},
};

#define NR_ARGS_HANDELS (sizeof(main_args_list)/sizeof(main_args_list[0]))

static bool check_for_arg_validity() {
	int numTargets = 0;
	if(true == flag_reg_alu_fpu) numTargets++;
	if(true == flag_testcase) numTargets++;
	if(true == flag_game) numTargets++;
	if(true == flag_score_expr) numTargets++;
	if(0 == numTargets) {
		printf("\n\nError: specify a target: [--test-reg, --test-alu, --test-fpu, --testcase, --test-game, --test-expr-score]\n\n");
		return false;
	}
	if(1 < numTargets) {
		printf("\n\nError: only one target is allowed: [--test-reg, --test-alu, --test-fpu, --testcase,  --test-game, --test-expr-score]\n\n");
		return false;
	}
	if(flag_game == true && flag_kernel == false) {
		printf("\n\nError: --test-game must be executed with --kernel\n\n");
		return false;
	}
	return true;
}

bool parse_args(int argc, char* argv[]) {
	int i = 0, j = 0;
	for(i = 1; i < argc; i++) {
		for(j = 0; j < NR_ARGS_HANDELS; j++) {
			if(strcmp(argv[i], main_args_list[j].arg) == 0) {
				if(i+1 < argc) {
					if(!main_args_list[j].handler(argv[i+1])) return false;
				} else {
					if(!main_args_list[j].handler("no_argument")) return false;
				}
				i += main_args_list[j].numArgs;
				break;
			}
		}
		if(j >= NR_ARGS_HANDELS) {
			printf("\n\nError: unknown argument '%s'\n\n", argv[i]);
			return false;
		}
	}
	return check_for_arg_validity();
}
