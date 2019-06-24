#include "nemu.h"
#include "monitor/ui.h"
#include "monitor/breakpoint.h"
#include "cpu/cpu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
        static char *line_read = NULL;
        if (line_read) {
                free(line_read);
                line_read = NULL;
        }
	do {
        	line_read = readline("(nemu) ");
	} while (!(line_read && *line_read));
        add_history(line_read);
        return line_read;
}

#define cmd_handler(cmd) static int cmd(char * args)


cmd_handler(cmd_c) {
	// execute the program
	exec(-1);
	return 0;
}

cmd_handler(cmd_q) {
	// terminate
	return -1;
}

cmd_handler(cmd_si) {
	if(args == NULL) {
		exec(1);
		return 0;
	}
	char * steps = strtok(NULL, " ");
	if(steps == NULL) {
		exec(1);
	} else {
		int n = 1;
		if(sscanf(steps, "%d", &n) == 1 && n > 0) { exec(n); }
                else { printf("Bad number: \e[0;31m%s\e[0m\n", steps); }
	}
	return 0;
}

cmd_handler(cmd_info) {
	char * arg = strtok(NULL, " ");
	if(strcmp(arg, "r") == 0) {
		print_reg();
	} else if (strcmp(arg, "w") == 0) {
		 list_breakpoint();
	} else {
		printf("undefined info args\n");
	}
	return 0;
}

// static void cmd_p(char *e, char *cmd_end) {
cmd_handler(cmd_p) {
	if(args == NULL) { goto p_error; }
	//if(args + strspn(args, " ") >= cmd_end) { goto p_error; }

	bool success;
	uint32_t val = expr(args, &success);
	if(!success) {
		printf("invalid expression: '%s'\n", args);
	}
	else {
		printf("dec     %d\nhex     0x%x\n", val, val);
	}
	return 0;

p_error:
	puts("Command format: \"p EXPR\"");
	return 0;
}

uint32_t look_up_fun_symtab(char *, bool *);

//static void cmd_b(char *e, char *cmd_end) {
cmd_handler(cmd_b) {
	vaddr_t addr;
	char fun_name[81];
	bool success;
	if(args == NULL) { goto b_error; }

	args += strspn(args, " ");
	if(*args == '*') {
		args ++;
		addr = expr(args, &success);
		if(!success) {
			printf("invalid expression: '%s'\n", args);
			return 0;
		}
	}
	else if(sscanf(args, "%80[a-zA-Z0-9_]", fun_name) == 1) {
		//addr = look_up_fun_symtab(fun_name, &success) + 3;	// +3 to skip the machine code of "push %ebp; movl %esp, %ebp"
		addr = look_up_fun_symtab(fun_name, &success);
		if(!success) {
			printf("function '%s' not found\n", fun_name);
			return 0;
		}
	}
	else {
b_error:
		puts("Command format: \"b *ADDR\" or \"b FUN\"");
		return 0;
	}

	int NO = set_breakpoint(addr);
	printf("set breakpoint %d at address 0x%08x\n", NO, addr);
	return 0;
}

//static void cmd_w(char *e, char *cmd_end) {
cmd_handler(cmd_w) {
	if(args == NULL) {
		puts("Command format: \"w EXPR\"");
		return 0;
	}
	   
	args += strspn(args, " ");
	int NO = set_watchpoint(args);
	if(NO == -1) {
		printf("invalid expression: '%s'\n", args);
		return 0;
	}

	printf("set watchpoint %d\n", NO);
	return 0;
}

//static void cmd_d() {
cmd_handler(cmd_d) {
	char *p = strtok(NULL, " ");
	if(p == NULL) {
		char c;
		while(1) {
			printf("Deleta all breakpoints? (y or n)");
			scanf("%c", &c);
			switch(c) {
				case 'y': delete_all_breakpoint();
				case 'n': return 0;
				default: puts("Please answer y or n.");
			}
		}
	}
	
	int NO;
	for(; p != NULL; p = strtok(NULL, " ")) {
		if(sscanf(p, "%d", &NO) != 1) {
			printf("Bad breakpoint number: '%s'\n", p);
			return 0;
		}
		delete_breakpoint(NO);
	}
	return 0;
}

cmd_handler(cmd_help);

static struct {
        char *name;
        char *description;
        int (*handler) (char *);
} cmd_table [] = {
        { "help", "Display informations about all supported commands", cmd_help },
        { "c", "Continue the execution of the program", cmd_c },
        { "q", "Exit NEMU", cmd_q },
        { "p", "Evaluate an expression", cmd_p },
        { "b", "Set breakpoint", cmd_b },
        { "w", "Set watchpoint", cmd_w },
		{ "d", "Delete breakpoint(s).", cmd_d},
        { "exit", "Exit NEMU", cmd_q },

        /* TODO: Add more commands */
	{ "si", "Single Step Execution", cmd_si},
	{ "info", "Print register and watch point info", cmd_info},

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))


cmd_handler(cmd_help) {
	/* extract the first argument */
        char *arg = strtok(NULL, " ");
        int i;

        if(arg == NULL) {
                /* no argument given */
                for(i = 0; i < NR_CMD; i ++) {
                        printf("%s\t-\t%s\n", cmd_table[i].name, cmd_table[i].description);
                }
        }
        else {
                for(i = 0; i < NR_CMD; i ++) {
                        if(strcmp(arg, cmd_table[i].name) == 0) {
                                printf("%s\t-\t%s\n", cmd_table[i].name, cmd_table[i].description);
                                return 0;
                        }
                }
                printf("Unknown command \e[0;31m%s\e[0m\n", arg);
        }
        return 0;
}

// the main loop of accepting user commands
void ui_mainloop(bool autorun) {

	if(autorun) {
		cmd_c("");
		if(nemu_state == NEMU_STOP) {
			return;
		}
	}
	
	while(true) {
		// read user command
		char * user_cmd = rl_gets();
		char * user_cmd_end = user_cmd + strlen(user_cmd);
		// parse the command
		char * cmd = strtok(user_cmd, " ");
		if(cmd == NULL) {
			// empty command, should not happen
			continue;
		}

		// the remaining part of user_cmd is considered as arguments
		char * args = user_cmd + strlen(cmd) + 1;
		args += strspn(args, " ");
		if(args >= user_cmd_end) {
			// there is no argument
			args = NULL;
		}

		// execute the command by calling corresponding function
		int i;
		for(i = 0 ; i < NR_CMD ; i++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
                                if(cmd_table[i].handler(args) < 0) {
					// quit the ui mainloop
					return;
				}
				// stop searching for cmd and wait for the next user_cmd
                                break;
                        }
		}

		if(i == NR_CMD) {
			printf("Unknown user command \e[0;31m%s\e[0m\n", user_cmd);
		}

		if(nemu_state == NEMU_STOP) {
			break;
		}
	}
}
