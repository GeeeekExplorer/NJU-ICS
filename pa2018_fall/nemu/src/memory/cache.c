#include "nemu.h"
#include "memory/memory.h"
#include "memory/cache.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CacheLine Cache[1024];

void init_cache() {
	int i;
	for(i=0;i<1024;i++)
		Cache[i].valid=0;
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	uint32_t ret;
	uint32_t sign =(paddr>>13)&0x7ffff;
	uint32_t group_num =(paddr>>6)&0x7f;
	uint32_t offset=paddr&0x3f;
	int i;
	for(i=0;i<8;i++)
	{
		if(cache[group_num*8+i].sign==sign&&cache[group_num*8+i].valid==1)
		{	
			if(offset+len<=64)
				memcpy(&ret,cache[group_num*8+i].block+offset,len);
			else
			{
				uint32_t temp1=0,temp2=0;
				memcpy(&temp1,cache[group_num*8+i].block+offset,64-offset);
				temp2=cache_read(paddr+64-offset,offset+len-64,Cache)<<(8*(64-offset));
				ret=temp2|temp1;
			}
			break;
		}
	}
	if(i==8)
	{
		memcpy(&ret,hw_mem+paddr,len);
		for(i=0;i<8;i++)
		{
			if(cache[group_num*8+i].valid==0)
			{
				cache[group_num*8+i].valid=1;
				cache[group_num*8+i].sign=sign;
				memcpy(cache[group_num*8+i].block,hw_mem+paddr-offset,64);
				break;
			}
		}
		if(i==8)
		{
			srand((unsigned)time(0));
			i=rand()%8;
			cache[group_num*8+i].valid=1;
			cache[group_num*8+i].sign=sign;
			memcpy(cache[group_num*8+i].block,hw_mem+paddr-offset,64);
		}
	}
	return ret;
}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache)
{
	memcpy(hw_mem+paddr,&data,len);
	uint32_t sign =(paddr>>13)&0x7ffff;
	uint32_t group_num =(paddr>>6)&0x7f;
	uint32_t offset=paddr&0x3f;
	int i;
	for(i=0;i<8;i++)
	{
		if(cache[group_num*8+i].sign==sign&&cache[group_num*8+i].valid==1)
		{
			if(offset+len<=64)
				memcpy(cache[group_num*8+i].block+offset,&data,len);
			else
			{
				cache_write(paddr,64-offset,data,Cache);
				cache_write(paddr+64-offset,len+offset-64,data>>(8*(64-offset)),Cache);
			}
			break;
		}
	}
}
