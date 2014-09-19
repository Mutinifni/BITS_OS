echo Assembling:
nasm -f elf -o start.o start.asm

echo Compiling main.c:
gcc -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c

echo Compiling scrn.c:
gcc -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o scrn.o scrn.c

echo Running linker script:
ld -m elf_i386 -T link.ld -o kernel.bin start.o main.o scrn.o

echo Done!