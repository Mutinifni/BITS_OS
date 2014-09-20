#include <system.h>

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
    for (;;);
    return 0;
}