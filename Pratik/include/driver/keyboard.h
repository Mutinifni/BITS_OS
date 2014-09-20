#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <interrupt.h>
#include <system.h> 
#define UInt8 unsigned char 
extern UInt8 spkeys[10] ; 
extern unsigned char kbdus[128] ; 
void keyboard_install() ; 
void keyboard_handler(struct regs *r) ; 
void toggle_caps() ;
void toggle_shift(int) ; 
void s_putch(char) ;  
#endif 