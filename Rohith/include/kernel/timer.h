#ifndef TIMER_H
#define TIMER_H
#include <interrupt.h> 
extern int timer_ticks ; 
void timer_handler(struct regs *r) ; 
void timer_wait(int ticks) ; 
void timer_install() ; 
#endif 
