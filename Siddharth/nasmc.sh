nasm -f elf -o start.o start.asm
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o gdt.o gdt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o idt.o idt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isrs.o isrs.c
cd include
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o scrn.o scrn.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o prnt.o prnt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o memfn.o memfn.c
cd ..
ld -m elf_i386 -T link.ld -o kernel.bin *.o ./include/*.o
