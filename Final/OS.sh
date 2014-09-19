# Following are the steps and the command to compile this project.  
# Assuming that you are running this file in a bash shell. 
# Before building the operating system, you must set the environment variable as shown below in the line. 
 export OS_DEV_INCLUDE_PATH=$(pwd)/include/kernel/ 
 gcc -o kernel_main.o kernel_main.c -std=c99 -m32 -c -nostdinc -I/OS_DEV_INCLUDE_PATH 
 nasm -f elf -o kernel.o kernel.asm
 ld -T linker_script.ld -o myos.bin -O2 -nostdlib kernel.o kernel_main.o  -m elf_i386
 mkdir -p isodir/boot 
 mkdir -p isodir/boot/grub/ 
 cp  myos.bin isodir/boot/
 cp grub.cfg isodir/boot/grub/
 grub-mkrescue -o myos.iso isodir
 qemu-system-i386 -cdrom myos.iso


