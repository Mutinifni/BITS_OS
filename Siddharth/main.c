#include <system.h>

int main()
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();

    __asm__ __volatile__ ("sti");

    print("\t\t\t\t Hello, World\n");
    for (;;);
    return 0;
}