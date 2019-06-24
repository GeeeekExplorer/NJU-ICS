#ifndef __INSTR_HELPER_REF_H__
#define __INSTR_HELPER_REF_H__ 

#include <cpu/instr_helper.h>

//reference
// macro for making an instruction entry
#define make_instr_func_ref(name) int concat(__ref_, name)(uint32_t eip, uint8_t opcode)

#endif
