nasm -f elf -o start.o start.asm
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
cd interrupts
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o gdt.o gdt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o idt.o idt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o isrs.o isrs.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o irq.o irq.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o timer.o timer.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o kb.o kb.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include -c -o rtc.o rtc.c
cd ../include
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I. -c -o scrn.o scrn.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I. -c -o prnt.o prnt.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I. -c -o memfn.o memfn.c
g++ -march=i386 -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I. -c -o kbdfn.o kbdfn.c
cd ..
ld -m elf_i386 -T link.ld -o kernel *.o */*.o
sudo ./update_image.sh
sudo ./run_bochs.sh
rm ./kernel
rm *.o */*.o