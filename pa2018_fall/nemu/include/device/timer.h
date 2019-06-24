#ifndef __TIMER_H__
#define __TIMER_H__

#include "nemu.h"
#include "device/port_io.h"

#define TIMER_PORT 0X40
#define TIMER_IRQ 0x0

void timer_intr();
make_pio_handler(handler_timer);
void timer_start(int hz);
void timer_stop();
#endif
