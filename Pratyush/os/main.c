#include <system.h>

int main()
{
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    timer_install();
    keyboard_install();
    __asm__ __volatile__ ("sti"); // Re-enable interrupts command (opposite of cli)	
    init_video();

    read_rtc();
    //int f = 5;
    //int k = 0;
    //print(f/k);
    for (;;);
    return 0;
}