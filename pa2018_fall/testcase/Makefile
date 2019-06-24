.PHONY: testcase clean

CC := gcc
LD := ld
CFLAGS := -ggdb3 -MMD -MP -Wall -m32 -march=i386 -fno-builtin -fno-stack-protector -I../include -I../libs/newlib/include

#LDFLAGS := -m elf_i386 -e start -Ttext=0x30000
#LDFLAGS := -m elf_i386 -e start -Ttext=0x60000
LDFLAGS := -m elf_i386 -e start

SFILES := $(shell find src/ -name "*.S")
CFILES := $(shell find src/ -name "*.c")

SOBJS := $(SFILES:.S=.o)
COBJS := $(CFILES:.c=.o)

SBINS := $(SFILES:.S=)
CBINS := $(CFILES:.c=)

testcase: start.o $(SOBJS) $(COBJS) $(SBINS) $(CBINS) Makefile

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

%: %.o
	$(LD) $(LDFLAGS) -o $@ src/start.o $< ../libs/newlib/libc.a
	cp $@ $(addprefix bin/,$(notdir $@))
	objcopy -S -O binary -B i386 $(addprefix bin/,$(notdir $@)) $(addprefix bin/,$(notdir $@)).img

start.o: start.S
	$(CC) $(CFLAGS) -c -o src/start.o start.S	


clean:
	-rm -f $(SOBJS) $(SOBJS:.o=.d) src/start.o src/start.d
	-rm -f $(COBJS) $(COBJS:.o=.d)
	-rm -f $(SBINS) 
	-rm -f $(CBINS)
	-rm -f -r bin/
	mkdir bin/
