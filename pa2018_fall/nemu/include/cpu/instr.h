#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "nemu.h"
#include "cpu/cpu.h"
#include "cpu/fpu.h"
#include "cpu/modrm.h"
#include "cpu/operand.h"
#include "cpu/instr_helper.h"
#include "memory/memory.h"
#include <cpu-ref/instr_ref.h>

#include <stdio.h>
 
extern uint8_t data_size;

#include "cpu/instr/mov.h"
#include "cpu/instr/jmp.h"
#include "cpu/instr/shift.h"
#include "cpu/instr/flags.h"
#include "cpu/instr/group.h"
#include "cpu/instr/special.h"
#include "cpu/instr/x87.h"
#include "cpu/instr/adc.h"
#include "cpu/instr/add.h"
#include "cpu/instr/and.h"
#include "cpu/instr/or.h"
#include "cpu/instr/sbb.h"
#include "cpu/instr/sub.h"
#include "cpu/instr/xor.h"
#include "cpu/instr/cmp.h"
#include "cpu/instr/inc.h"
#include "cpu/instr/dec.h"
#include "cpu/instr/push.h"
#include "cpu/instr/pop.h"
#include "cpu/instr/call.h"
#include "cpu/instr/ret.h"
#include "cpu/instr/test.h"
#include "cpu/instr/lea.h"
#include "cpu/instr/leave.h"
#include "cpu/instr/set.h"
#include "cpu/instr/mul.h"
#include "cpu/instr/imul.h"
#include "cpu/instr/div.h"
#include "cpu/instr/idiv.h"
#include "cpu/instr/not.h"
#include "cpu/instr/neg.h"
#include "cpu/instr/stoc.h"
#include "cpu/instr/lgdt.h"
#include "cpu/instr/lidt.h"
#include "cpu/instr/cli.h"
#include "cpu/instr/sti.h"
#include "cpu/instr/int.h"
#include "cpu/instr/iret.h"
#include "cpu/instr/in.h"
#include "cpu/instr/out.h"

/* TODO: add more instructions here */

#endif
