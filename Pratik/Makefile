# check for tabs vs spaces issues with the command cat -e -t -v Makefile 
current_dir = $(shell pwd)
libdir = $(current_dir)/lib/kernel/
includedir = $(current_dir)/include/kernel/
top_level_obj = $(shell cat top.list) 
kernel_obj = $(shell cat kernel.list) 
all: kernel_main.o kernel.o gdt.o start.o initialize.o 
	ld -T  linker_script.ld -o myos.bin -O2 -nostdlib $(top_level_obj) $(kernel_obj)  -m elf_i386
	mkdir -p isodir/boot 
	mkdir -p isodir/boot/grub/ 
	cp  myos.bin isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso --no-reboot 
start.o: start.asm
	nasm -f elf -o start.o start.asm 
gdt.o: gdt.c 
	gcc -o gdt.o gdt.c  -std=c99 -m32 -c 
kernel_main.o: kernel_main.c 
	@echo $(current_dir) 
	@echo $(includedir) 
	gcc -o kernel_main.o kernel_main.c  -std=c99 -m32 -c -I$(includedir)  
initialize.o: $(libdir)initialize.c
	gcc -o $(libdir)initialize.o $(libdir)initialize.c -std=c99 -m32 -c -I$(includedir) 
kernel.o: kernel.asm
	nasm -f elf -o kernel.o kernel.asm
clean:
	rm -v *.o 
	rm -v *.iso 
	rm -v *.bin