#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "device/port_io.h"

#define SERIAL_PORT 0x3F8

make_pio_handler(handler_serial);

void init_serial();

#endif
