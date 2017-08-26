CFLAGS=-mfloat-abi=soft -mlittle-endian -O0 -g3
CFLAGS+=-fno-builtin -nostartfiles -std=c11
LDFLAGS=-static -nostdlib

all: myprog.bin

GCC	=arm-unknown-eabi-gcc
LD	=arm-unknown-eabi-ld
OBJCPY	=arm-unknown-eabi-objcopy

main.o: main.c
	$(GCC) $(CFLAGS) -c $^ -o $@

start.o: start.S
	$(GCC) $(CFLAGS) -c $^ -o $@

myprog.elf: ldscript.lds start.o main.o
	$(LD) $(LDFLAGS) -T $^ `$(GCC) -print-libgcc-file-name` -o $@

myprog.bin: myprog.elf
	$(OBJCPY) -O binary $^ $@

target: ldscript.lds source.o
	$(LD) -T $^ -o $@

clean: main.o start.o
	rm $^
