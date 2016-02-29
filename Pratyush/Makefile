PWD := $(shell pwd)
INCLUDE := $(PWD)/include

CC := g++
CC_FLAGS := -c -g -m32 -march=i386 -ffreestanding -fno-stack-protector -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I$(INCLUDE)

all: kernel.bin

qemu:
	qemu-system-i386 -kernel kernel.bin

start.o: start.asm
	nasm -f elf -o start.o start.asm

gdt.o: $(INCLUDE)/gdt.c idt.o irq.o isrs.o kb.o kbdfn.o memfn.o print.o rtc.o scrn.o timer.o
	$(CC) $(CC_FLAGS) $(INCLUDE)/gdt.c

idt.o: $(INCLUDE)/idt.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/idt.c

irq.o: $(INCLUDE)/irq.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/irq.c
	
isrs.o: $(INCLUDE)/isrs.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/isrs.c

kb.o: $(INCLUDE)/kb.c 
	$(CC) $(CC_FLAGS) $(INCLUDE)/kb.c
	
kbdfn.o: $(INCLUDE)/kbdfn.c	
	$(CC) $(CC_FLAGS) $(INCLUDE)/kbdfn.c
	
memfn.o: $(INCLUDE)/memfn.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/memfn.c
	
print.o: $(INCLUDE)/print.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/print.c

rtc.o: $(INCLUDE)/rtc.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/rtc.c
	
scrn.o: $(INCLUDE)/scrn.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/scrn.c
	
timer.o: $(INCLUDE)/timer.c
	$(CC) $(CC_FLAGS) $(INCLUDE)/timer.c

main.o: main.c
	$(CC) $(CC_FLAGS) main.c

kernel.bin: link.ld main.o start.o gdt.o idt.o irq.o isrs.o kb.o kbdfn.o memfn.o print.o rtc.o scrn.o timer.o
	ld -m elf_i386 -T link.ld -o kernel.bin -nostdlib $(PWD)/*.o -Map os.map
	rm $(PWD)/*.o

clean:
	rm os.map kernel.bin
