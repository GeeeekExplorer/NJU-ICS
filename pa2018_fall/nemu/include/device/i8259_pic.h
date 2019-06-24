#ifndef __I8259_PIC_H__
#define __I8259_PIC_H__


#include "nemu.h"

#define IRQ_BASE 32
#define I8259_NO_INTR 255 

// get interrupt number
uint8_t i8259_query_intr_no();

// called by device (keyboard) to raise an interrupt with irq number
void i8259_raise_intr(uint8_t irq_no);

// called by cpu after the cpu has received the interrupt
void i8259_ack_intr();

void i8259_init();

void i8259_destroy();
#endif
