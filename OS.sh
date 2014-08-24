 gcc -o kernel_main.o kernel_main.c -std=c99 -m32 -c 
 nasm -f elf -o kernel.o kernel.asm
 ld -T linker_script.ld -o myos.bin -O2 -nostdlib kernel.o kernel_main.o  -m elf_i386
 cp myos.bin isodir/boot/
 cp grub.cfg isodir/boot/grub/
 grub-mkrescue -o myos.iso isodir
 qemu-system-i386 -cdrom myos.iso


