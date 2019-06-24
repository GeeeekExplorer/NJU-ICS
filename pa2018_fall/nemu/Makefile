.PHONY: clean

CC := gcc
LD := ld
CFLAGS := -ggdb3 -MMD -MP -Wall -Werror -O2 -I./include -I../include -I../libs -I../libs/nemu-ref/include
LDFLAGS := -lreadline -lSDL

CFILES := $(shell find src/ -name "*.c")
OBJS := $(CFILES:.c=.o)
IFILES := $(CFILES:.c=.i)

nemu: $(OBJS) ../include/config.h 
	$(CC) -o nemu $(OBJS) ../libs/nemu-ref/lib-nemu-ref.a $(LDFLAGS)

%.i: %.c
	$(CC) $(CFLAGS) -E -o $@ $<

clean:
	-rm -f nemu $(OBJS) $(IFILES) $(OBJS:.o=.d)
