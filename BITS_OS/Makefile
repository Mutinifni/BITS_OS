# This is the make file for the BITS_OS project.
curr_dir = $(shell pwd)
inc_dir = $(curr_dir)/include
lib_dir = $(curr_dir)/lib
script = linker_script.ld
target = proc_asm.o kernel_asm.o proc_c.o kernel.o io.o string.o
flags = -Wall -Werror -nostdinc -m32 -c -fno-builtin -I$(inc_dir)
comp = g++
sys_obj = proc_asm.o $(lib_dir)/proc_c.o kernel_asm.o kernel.o $(lib_dir)/io.o $(lib_dir)/string.o 
all: $(target) 
	ld -m elf_i386 -t $(script) -o kernel.bin $(sys_obj) -nostdlib
	qemu-system-i386 -kernel kernel.bin 

proc_asm.o: processor.asm 
	nasm -f elf processor.asm -o proc_asm.o 

kernel_asm.o: start.asm
	nasm -f elf start.asm -o kernel_asm.o 

proc_c.o: $(lib_dir)/processor.c
	$(comp) -o $(lib_dir)/proc_c.o $(lib_dir)/processor.c $(flags)

kernel.o: kernel.c
	$(comp) -o kernel.o kernel.c $(flags)

io.o: $(lib_dir)/io.c
	$(comp) -o $(lib_dir)/io.o $(lib_dir)/io.c $(flags) 
string.o: $(lib_dir)/string.c
	$(comp) -o $(lib_dir)/string.o $(lib_dir)/string.c $(flags)

clean:
	rm -v $(lib_dir)/*.o 
	rm -v *.o 
