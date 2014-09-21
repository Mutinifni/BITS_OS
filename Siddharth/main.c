#include <system.h>

extern void read_rtc();

int main()
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    timer_install();
    keyboard_install();


    __asm__ __volatile__ ("sti");

    print("\t\t\t\t Operating System \n");
    read_rtc();
    for (;;);
    return 0;
}