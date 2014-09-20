#include <system.h>

int main()
{
    gdt_install();
    idt_install();
    isrs_install();
    init_video();
    for (;;);
    return 0;
}