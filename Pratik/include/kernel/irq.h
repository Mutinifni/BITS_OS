#ifndef IRQ_C 
#define IRQ_C 
#include <string.h> 
#include <interrupt.h>
extern void irq0() __asm__ ("irq0");
extern void irq1() __asm__ ("irq1");
extern void irq2() __asm__ ("irq2");
extern void irq3() __asm__ ("irq3");
extern void irq4() __asm__ ("irq4");
extern void irq5() __asm__ ("irq5");
extern void irq6() __asm__ ("irq6");
extern void irq7() __asm__ ("irq7");
extern void irq8() __asm__ ("irq8");
extern void irq9() __asm__ ("irq9");
extern void irq10() __asm__ ("irq10");
extern void irq11() __asm__ ("irq11");
extern void irq12() __asm__ ("irq12");
extern void irq13() __asm__ ("irq13");
extern void irq14() __asm__ ("irq14");
extern void irq15() __asm__ ("irq15");

void irq_handler(regs*) ; 
void irq_install() ; 
void irq_remap() ; 
void irq_uninstall_handler(int) ;
void irq_install_handler(int irq, void (*handler)(struct regs *r)) ;   
#endif 
