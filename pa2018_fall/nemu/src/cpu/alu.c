#include "cpu/cpu.h"

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
    uint32_t res=0;
    res=dest+src;
    
    set_CF_add(res,src,data_size);
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    set_OF_add(res,src,dest,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
    res=dest+src+cpu.eflags.CF;
    
    set_CF_adc(res,src,data_size);
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    set_OF_add(res,src,dest,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}


uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
    uint32_t res=0;
    res=dest-src;
    
    set_CF_sub(dest,src,data_size);
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    set_OF_sub(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
    res=dest-src-cpu.eflags.CF;
    
    set_CF_sbb(dest,src,data_size);
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    set_OF_sub(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	uint64_t res=0;
	if(data_size==32)
		res=(uint64_t)src*(uint64_t)dest;
	else
		res=src*dest;
    if(data_size==8)
		cpu.eflags.OF=cpu.eflags.CF=((res&0xFF00)!=0);
	else if(data_size==16)
		cpu.eflags.OF=cpu.eflags.CF=((res&0xFFFF0000)!=0);
	else
		cpu.eflags.OF=cpu.eflags.CF=((res&0xFFFFFFFF00000000)!=0);
	return res;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	uint64_t res=0;
	if(data_size==32)
		res=(uint64_t)src*(uint64_t)dest;
	else
		res=src*dest;
	return res;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	uint32_t res=0;
	if(src==0)
		return 0;
	res=dest/src;
	return res;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	uint32_t res=0;
	if(src==0)
		return 0;
	res=dest/src;
	return res;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	uint32_t res=0;
	if(src==0)
		return 0;
	res=dest%src;
	return res;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	uint32_t res=0;
	if(src==0)
		return 0;
	res=dest%src;
	return res;
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest&src;

	cpu.eflags.CF=0;
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    cpu.eflags.OF=0;
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest^src;

	cpu.eflags.CF=0;
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    cpu.eflags.OF=0;
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest|src;

	cpu.eflags.CF=0;
    set_PF(res);
    //set_AF();
    set_ZF(res,data_size);
	set_SF(res,data_size);
    cpu.eflags.OF=0;
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	cpu.eflags.CF=0;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	while(src){
		if(data_size==8)
			cpu.eflags.CF=((dest&0x80)==0x80);
		else if(data_size==16)
			cpu.eflags.CF=((dest&0x8000)==0x8000);
 		else
			cpu.eflags.CF=((dest&0x80000000)==0x80000000);
		dest=dest<<1;
		src--;
	}
	set_PF(dest);
    //set_AF();
    set_ZF(dest,data_size);
	set_SF(dest,data_size);
	return dest&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	cpu.eflags.CF=0;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	while(src){
		cpu.eflags.CF=((dest&0x1)==0x1);
		dest=dest>>1;
		src--;
	}
	set_PF(dest);
    //set_AF();
    set_ZF(dest,data_size);
	set_SF(dest,data_size);
	return dest&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	if(data_size==8&&(dest&0x00000080)==0x00000080)
		while(src){
			cpu.eflags.CF=((dest&0x1)==0x1);
			dest=dest>>1;
			dest=dest^0x00000080;
			src--;
		}
	else if(data_size==16&&(dest&0x00008000)==0x00008000)
		while(src){
			cpu.eflags.CF=((dest&0x1)==0x1);
			dest=dest>>1;
			dest=dest^0x00008000;
			src--;
		}
	else if(data_size==32&&(dest&0x80000000)==0x80000000)
		while(src){
			cpu.eflags.CF=((dest&0x1)==0x1);
			dest=dest>>1;
			dest=dest^0x80000000;
			src--;
		}
	else
		return alu_shr(src,dest,data_size);
	set_PF(dest);
	//set_AF();
	set_ZF(dest,data_size);
	set_SF(dest,data_size);
	return dest&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	return alu_shl(src,dest,data_size);
}
