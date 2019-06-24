#include "common.h"
#define NR_SEC_CACHE    128   /* sector cache is a direct address hash */

void disk_do_read(void *, uint32_t);
void disk_do_write(void *, uint32_t);

struct SectorCache {
	uint32_t sector;
	bool used, dirty;
	uint8_t content[512];
};
static struct SectorCache cache[NR_SEC_CACHE];

void
cache_init(void) {
	int i;
	for (i = 0; i < NR_SEC_CACHE; i ++) {
		cache[i].used = false;
	}
}

void
cache_writeback(void) {
	int i;
	for (i = 0; i < NR_SEC_CACHE; i ++) {
		if (cache[i].dirty == true) {
			disk_do_write(&cache[i].content, cache[i].sector);
			cache[i].dirty = false;
		}
	}
}

static struct SectorCache *
cache_fetch(uint32_t sector) {
	struct SectorCache *ptr = &cache[sector % NR_SEC_CACHE];
	
	if (ptr->used == true && ptr->sector == sector) {
		/* cache hit, do nothing */
	} else {
		if (ptr->used == true && ptr->dirty == true) {
			/* write back */
			disk_do_write(&ptr->content, ptr->sector);
		}
		/* issue a read command */
		disk_do_read(&ptr->content, sector);

		ptr->used = true;
		ptr->sector = sector;
		ptr->dirty = false;
	}
	return ptr;
}

uint8_t
read_byte(uint32_t offset) {
	uint32_t sector = offset >> 9; // div by 512
	struct SectorCache *ptr = cache_fetch(sector);
	return ptr->content[offset & 511];
}

void
write_byte(uint32_t offset, uint8_t data) {
	uint32_t sector = offset >> 9;
	struct SectorCache *ptr = cache_fetch(sector);
	ptr->content[offset & 511] = data;
	ptr->dirty = true;
}

