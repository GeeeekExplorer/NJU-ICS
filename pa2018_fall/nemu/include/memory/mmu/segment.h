#ifndef __SEGMENT_H__
#define __SEGMENT_H__

typedef union SegmentDescriptor {
	struct {
	        uint32_t limit_15_0          : 16;
	        uint32_t base_15_0           : 16;
	        uint32_t base_23_16          : 8;
	        uint32_t type                : 4;
	        uint32_t segment_type        : 1;
	        uint32_t privilege_level     : 2;
	        uint32_t present             : 1;
	        uint32_t limit_19_16         : 4;
	        uint32_t soft_use            : 1;
	        uint32_t operation_size      : 1;
	        uint32_t pad0                : 1;
        	uint32_t granularity         : 1;
	        uint32_t base_31_24          : 8;
	};
	uint32_t val[2];
} SegDesc;

uint32_t segment_translate(uint32_t vaddr, uint8_t sreg);
void load_sreg(uint8_t sreg);

#endif
