#ifndef __BREAKPOINT_H__
#define __BREAKPOINT_H__

#include "nemu.h"

#define INT3_CODE 0xf1

enum {IDLE, HIT, RE_EXEC};

enum {BREAKPOINT, WATCHPOINT};

typedef struct breakpoint {
	uint8_t ori_byte	: 8;
	bool enable			: 1;
	bool in_use			: 1;
	int NO				: 22;

	union {
		vaddr_t addr;
		struct {
			char *expr;
			uint32_t old_val;
			uint32_t new_val;
		};
	};
	int type;
	struct breakpoint *next;

	/* TODO: Add more member if necessary */


} BP;

int set_breakpoint(vaddr_t);
bool delete_breakpoint(int);
void delete_all_breakpoint();
void list_breakpoint();

BP* find_breakpoint(vaddr_t);
void resume_breakpoints();
void mask_breakpoints();


int set_watchpoint(char *e);
BP* scan_watchpoint();

void load_elf_tables(const char *);
void init_regex();
void init_bp_list();

uint32_t expr(char *, bool *);

#endif
