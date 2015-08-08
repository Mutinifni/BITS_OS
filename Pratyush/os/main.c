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
    print("\t\t\t\tBITS - OS\t\t") ;
    print_Time(read_rtc());     
    print("\t\t\tWelcome to our BITS Operating System\t\t\n") ; 
    print("\tWe have added support for US style keyboard,so you can type !\t\n");
    print("root@cyborg:# ");    
    //int f = 5;
    //int k = 0;
    //print(f/k);
    for (;;);
    return 0;
}