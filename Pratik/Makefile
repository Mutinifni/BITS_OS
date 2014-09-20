# check for tabs vs spaces issues with the command cat -e -t -v Makefile 
current_dir = $(shell pwd)
libdir = $(current_dir)/lib/kernel/
includedir = $(current_dir)/include/kernel/ 
include_cdir = $(current_dir)/include/clib/ 
lib_cdir = $(current_dir)/lib/clib/
top_level_obj = kernel.o kernel_main.o 
kernel_obj =  lib/kernel/initialize.o lib/kernel/scrn.o lib/kernel/system.o lib/kernel/gdt.o lib/kernel/interrupt.o lib/kernel/irq.o 
clib_obj = lib/clib/string.o 
all: kernel_main.o kernel.o gdt.o initialize.o scrn.o system.o string.o interrupt.o  irq.o 
	ld -m elf_i386 -T  linker_script.ld -o myos.bin -nostdlib $(top_level_obj) $(kernel_obj) $(clib_obj) 
	qemu-system-i386 -kernel myos.bin
irq.o: $(libdir)irq.c 
	gcc -o $(libdir)irq.o -Werror $(libdir)irq.c -Wall -std=c99 -nostdinc -m32 -c -I$(includedir) -I$(include_cdir) -fno-builtin 
gdt.o: $(libdir)gdt.c 
	gcc -o $(libdir)gdt.o -Werror $(libdir)gdt.c -Wall -std=c99  -nostdinc -m32 -c -I$(includedir) -fno-builtin
system.o: $(libdir)system.c
	gcc -o $(libdir)system.o -Werror $(libdir)system.c -Wall -std=c99  -nostdinc -m32 -c -I$(includedir) -I$(include_cdir) -fno-builtin
kernel_main.o: kernel_main.c 
	gcc -o kernel_main.o kernel_main.c  -Wall -nostdinc  -std=c99 -m32 -c -I$(includedir) -I$(include_cdir)  -fno-builtin
initialize.o: $(libdir)initialize.c
	gcc -o $(libdir)initialize.o -Werror $(libdir)initialize.c  -std=c99 -nostdinc -m32 -c -I$(includedir) -Wall -fno-builtin 
scrn.o: $(libdir)scrn.c 
	gcc -o $(libdir)scrn.o $(libdir)scrn.c  -m32 -c -nostdinc  -std=c99 -Werror -I$(includedir) -I$(include_cdir) -Wall -fno-builtin 
kernel.o: kernel.asm
interrupt.o: $(libdir)interrupt.c 
	gcc -o $(libdir)interrupt.o $(libdir)interrupt.c -m32 -c -nostdinc -std=c99 -Werror -I$(includedir) -I$(include_cdir) -Wall -fno-builtin 
	nasm -f elf -o kernel.o kernel.asm
string.o: $(lib_cdir)string.c
	gcc -o $(lib_cdir)string.o $(lib_cdir)string.c -m32 -c -nostdinc -std=c99 -Werror -I$(includedir) -I$(include_cdir) -Wall -fno-builtin  
clean:
	rm -v *.o 
	rm -v *.bin
	rm -v $(libdir)*.o
	rm -v $(lib_cdir)*.o 
 
