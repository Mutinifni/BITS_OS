# check for tabs vs spaces issues with the command cat -e -t -v Makefile 
current_dir = $(shell pwd)
libdir = $(current_dir)/lib/kernel/
includedir = $(current_dir)/include/kernel/
top_level_obj = $(shell cat top.list) 
kernel_obj = $(shell cat kernel.list) 
all: kernel_main.o kernel.o gdt.o start.o initialize.o scrn.o system.o 
	ld -T  linker_script.ld -o myos.bin -O2 -nostdlib $(top_level_obj) $(kernel_obj)  -m elf_i386
	qemu-system-i386  -kernel myos.bin
start.o: start.asm
	nasm -f elf -o start.o start.asm 
gdt.o: gdt.c 
	gcc -o gdt.o gdt.c -Wall -Werror -nostdinc -std=c99 -m32  -c
system.o: $(libdir)system.c
	gcc -o $(libdir)system.o -Werror $(libdir)system.c -Wall -std=c99  -nostdinc -m32 -c -I$(includedir) -fno-builtin
kernel_main.o: kernel_main.c 
	gcc -o kernel_main.o kernel_main.c  -Werror -Wall -nostdinc  -std=c99 -m32 -c -I$(includedir)  -fno-builtin
initialize.o: $(libdir)initialize.c
	gcc -o $(libdir)initialize.o -Werror $(libdir)initialize.c  -std=c99 -nostdinc -m32 -c -I$(includedir) -Wall -fno-builtin 
scrn.o: $(libdir)scrn.c 
	gcc -o $(libdir)scrn.o $(libdir)scrn.c  -m32 -c -nostdinc  -std=c99 -Werror -I$(includedir) -Wall -fno-builtin 
kernel.o: kernel.asm
	nasm -f elf -o kernel.o kernel.asm
clean:
	rm -v *.o 
	rm -v *.iso 
	rm -v *.bin
	rm -v $(libdir)*.o 
