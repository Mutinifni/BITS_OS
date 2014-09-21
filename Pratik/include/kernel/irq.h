#ifndef IRQ_C 
#define IRQ_C 
#include <string.h> 
#include <interrupt.h>
void irq_handler(regs*) ; 
void irq_install() ; 
void irq_remap() ; 
void irq_uninstall_handler(int) ;
void irq_install_handler(int irq, void (*handler)(struct regs *r)) ;   
#endif 
