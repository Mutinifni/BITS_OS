# check for tabs vs spaces issues with the command cat -e -t -v Makefile 
#current_dir = present working directory. 
#lib_kdir = library directory of the kernel files. 
#include_kdir = library directory of the kernel header files. 
#include_clib = library directory of the clib header files. 
#lib_clib = library directory of the clib implementation files. 
#c_obj = list of clib object files. 
#obj_list = list of the total object files produced after compilation with only the names of the files. 
current_dir = $(shell pwd)
lib_kdir = $(current_dir)/lib/kernel/
lib_clib = $(current_dir)/lib/clib/
include_kdir = $(current_dir)/include/kernel/
include_clib = $(current_dir)/include/clib/
top_level_obj = $(shell cat top.list) 
kernel_obj = $(shell cat kernel.list) 
c_obj = $(shell cat clib.list)
obj_list = $(shell cat object.list) 
all: $(obj_list) 
	@echo lib_clib 
	@echo lib_kdir 
	ld -T  linker_script.ld -o myos.bin -O2 -nostdlib $(top_level_obj) $(kernel_obj) $(c_obj)  -m elf_i386
	qemu-system-i386 -kernel myos.bin --no-reboot 
start.o: start.asm
	nasm -f elf -o start.o start.asm 
gdt.o: gdt.c 
	gcc -o gdt.o gdt.c -Wall -Werror -nostdinc -std=c99 -m32  -c
system.o: $(lib_kdir)system.c
	gcc -o $(lib_kdir)system.o -Werror $(lib_kdir)system.c -Wall -std=c99  -nostdinc -m32 -c -I$(include_kdir) -I$(include_clib) -fno-builtin
kernel_main.o: kernel_main.c 
	gcc -o kernel_main.o kernel_main.c  -Werror -Wall -nostdinc  -std=c99 -m32 -c -I$(include_kdir) -I$(include_clib)  -fno-builtin
initialize.o: $(lib_kdir)initialize.c
	gcc -o $(lib_kdir)initialize.o -Werror $(lib_kdir)initialize.c  -std=c99 -nostdinc -m32 -c -I$(include_kdir) -I$(include_clib) -Wall -fno-builtin 
scrn.o: $(lib_kdir)scrn.c 
	gcc -o $(lib_kdir)scrn.o $(lib_kdir)scrn.c  -m32 -c -nostdinc  -std=c99 -Werror -I$(include_kdir) -Wall -I$(include_clib) -fno-builtin 
kernel.o: kernel.asm
	nasm -f elf -o kernel.o kernel.asm
string.o: 
	gcc -o $(lib_clib)string.o $(lib_clib)string.c -m32 -c -nostdinc -std=c99 -Werror -I$(include_clib) -Wall -fno-builtin 
clean:
	rm -v *.o 
	rm -v *.bin
	rm -v $(libdir)*.o 
