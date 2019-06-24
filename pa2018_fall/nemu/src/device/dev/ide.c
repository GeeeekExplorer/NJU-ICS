#include "nemu.h"
#include "device/ide.h"
#include "device/i8259_pic.h"

// the simulated disk in memory
static uint32_t disk_idx;
static uint32_t sector;
static uint32_t byte_cnt;
static bool ide_write;
static FILE *disk_fp;

// init the hard disk by loading the file into it
void init_ide(const char * file_to_load) {
	disk_fp = fopen(file_to_load, "rb");
	assert(disk_fp != 0);
	disk_idx = 0;
	write_io_port(IDE_PORT_BASE + 7, 1, 0x40);
}

make_pio_handler(handler_ide) {
	uint32_t buf;
	assert(byte_cnt <= 512);
	if(is_write) {
		if(port - IDE_PORT_BASE == 0 && len == 4) {
			/* write 4 bytes data to disk */
			assert(ide_write);
			buf = read_io_port(IDE_PORT_BASE, 4);
			fwrite(&buf, 4, 1, disk_fp);

			byte_cnt += 4;
			if(byte_cnt == 512) {
				/* finish */
				write_io_port(IDE_PORT_BASE + 7, 1, 0x40);
			}
		}
		else if(port - IDE_PORT_BASE == 7) {
			if(read_io_port(IDE_PORT_BASE + 7, 1) == 0x20 || read_io_port(IDE_PORT_BASE + 7, 1) == 0x30) {
				/* command: read/write */
				sector = (read_io_port(IDE_PORT_BASE + 6, 1) & 0x1f) << 24 
					| read_io_port(IDE_PORT_BASE + 5, 1) << 16
					| read_io_port(IDE_PORT_BASE + 4, 1) << 8 
					| read_io_port(IDE_PORT_BASE + 3, 1);
				disk_idx = sector << 9;
				fseek(disk_fp, disk_idx, SEEK_SET);

				byte_cnt = 0;

				if(read_io_port(IDE_PORT_BASE + 7, 1) == 0x20) {
					/* command: read from disk */
					ide_write = false;
					write_io_port(IDE_PORT_BASE + 7, 1, 0x40);
					i8259_raise_intr(IDE_IRQ);
				}
				else {
					/* command: write to disk */
					ide_write = true;
				}
			}
			else if (read_io_port(IDE_PORT_BASE + 7, 1) == 0xc8) {
				/* command: DMA read */

				/* Nothing to do here. The actual read operation is
				 * issued by write commands to the bus master register. */
			}
			else {
				/* not implemented command */
				assert(0);
			}
		}
	}
	else {
		if(port - IDE_PORT_BASE == 0 && len == 4) {
			/* read 4 bytes data from disk */
			assert(!ide_write);
			fread(&buf, 4, 1, disk_fp);
			write_io_port(IDE_PORT_BASE, 4, buf);

			byte_cnt += 4;
			if(byte_cnt == 512) {
				/* finish */
				write_io_port(IDE_PORT_BASE + 7, 1, 0x40);
			}
		}
	}
}
