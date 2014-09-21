#ifndef INTERRUPT_H 
#define INTERRUPT_H 
#include <string.h>
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

typedef struct regs regs ; 
typedef struct idt_entry idt_entry ;
typedef struct idt_ptr idt_ptr ; 

void fault_handler(regs*) ; 
void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags) ; 
void isrs_install() ; 
void idt_install() ; 
/* We have declared an IDT of 256 entries, if we hit on a interrupt and it goes unhandled, it will generate a
interrupt unhandled exception. */ 

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load() __asm__("idt_load");

#endif 		
