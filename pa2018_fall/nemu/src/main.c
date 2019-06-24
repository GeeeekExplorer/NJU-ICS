#include "nemu.h"
#include "monitor/ui.h"
#include "memory/memory.h"
#include "cpu/cpu.h"
#include "cpu/fpu.h"
#include "device/sdl.h"
#include "device/serial.h"
#include "device/ide.h"
#include "monitor/breakpoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <scoring.h>

#define INIT_EIP 0x30000
#define LOAD_OFF 0x30000

extern char image_path[100];
extern char elf_path[100];
extern char image_path_score[100];
extern char elf_path_score[100];
extern bool flag_autorun;
extern bool flag_score;
extern bool flag_score_expr;
extern bool flag_reg_alu_fpu;
extern void (*builtin_test_func)();
extern void (*builtin_score_func)();

// load executable files
static void load_exec(const char * image_file, const uint32_t load_off) {
	int ret;
	FILE *fp = fopen(image_file, "rb");
	assert(fp != 0);

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	ret = fread(get_mem_addr() + load_off, file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}

static void restart(const uint32_t init_eip) {
	clear_ref();
	/* Initialize CPU and memory*/
	init_cpu(init_eip);
	init_mem();
	init_bp_list();
	init_regex();
#if defined(HAS_DEVICE_TIMER) || defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD)
	/* Initialize SDL for timer displayer audio and keyboard*/
	init_sdl();
#endif
#ifdef HAS_DEVICE_SERIAL
	init_serial();
#endif

}

static void single_run(const char * img_file_path, const char * elf_file_path) {
	restart(INIT_EIP); // restart the machine, do some initializations
	printf("NEMU load and execute img: \033[1m\033[32m%s\033[0m  elf: \033[1m\033[36m%s\033[0m\n", img_file_path, elf_file_path);
	load_exec(img_file_path, LOAD_OFF); // Load the memory image of executable
#ifdef HAS_DEVICE_IDE
	init_ide(elf_file_path); // Initialize hard drive
#else
	load_exec(elf_file_path, 0);
#endif
	load_elf_tables(elf_file_path);
	nemu_state = NEMU_READY; // Set the state of the machine to NEMU_READY
	ui_mainloop(flag_autorun); // Enter UI mainloop to accept user commands
}

void log_nemu_config() {
#ifdef CACHE_ENABLED
	score_set_cache_enabled();
#endif
#ifdef IA32_SEG
	score_set_ia32_seg();
#endif
#ifdef IA32_PAGE
	score_set_ia32_page();
#endif
#ifdef TLB_ENABLED
	score_set_tlb_enabled();
#endif
#ifdef IA32_INTR
	score_set_ia32_intr();
#endif
#ifdef HAS_DEVICE_TIMER
	score_set_has_device_timer();
#endif
#ifdef HAS_DEVICE_SERIAL
	score_set_has_device_serial();
#endif
#ifdef HAS_DEVICE_IDE
	score_set_has_device_ide();
#endif
#ifdef HAS_DEVICE_KEYBOARD
	score_set_has_device_keyboard();
#endif
#ifdef HAS_DEVICE_VGA
	score_set_has_device_vga();
#endif
#ifdef HAS_DEVICE_AUDIO
	score_set_has_device_audio();
#endif
	score_fix_config(); // prevent further changes to config log
}

bool parse_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {

	if(!parse_args(argc, argv)) { // parse the arguments
		printf("NEMU exit with argment parse error\n");
		return -1;
	}

	log_nemu_config();

	if(flag_score_expr) {
		init_regex();
		score_expr();
		return 0;
	}

	if(flag_reg_alu_fpu) {
		// use the built-in testcases
		printf("NEMU execute built-in tests\n");
		if(flag_score) {
			builtin_score_func();
		} else {
			builtin_test_func();
		}
	} else {
		// either testcase or game, the img and elf paths should be properly set
		if(flag_score) {
			single_run(image_path_score, elf_path_score);
		} else {
			single_run(image_path, elf_path);
		}
#if defined(HAS_DEVICE_TIMER) || defined(HAS_DEVICE_VGA) || defined(HAS_DEVICE_KEYBOARD)
		close_sdl();
#endif
	}

	return 0;
}
