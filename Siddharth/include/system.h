#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef unsigned char UInt8;
typedef unsigned short int  UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;

struct regs
{
    UInt32 gs, fs, es, ds;      /* pushed the segs last */
    UInt32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    UInt32 int_no, err_code;    /* our 'push byte #' and ecodes do this */
    UInt32 eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

/* MEMFN.C */
extern void *memcpy(void *dest, const void *src, UInt32 count);
extern void *memset(void *dest, char val, UInt32 count);
extern UInt16 *memsetw(UInt16 *dest, UInt16 val, UInt32 count);
extern UInt32 strlen(const char *str);
extern UInt8 inportb (UInt16 _port);
extern void outportb (UInt16 _port, UInt8 _data);

/* SCR.C */
extern void scroll(void);
extern void move_csr(void);
extern void cls();
extern void putch(const char c);
extern void settextcolor(UInt8 forecolor, UInt8 backcolor);
extern void init_video(void);
extern void arrow_keys(char dir);

/* PRNT.C */
extern void print(const char *text);
extern void print(short n);
extern void print(int n);
extern void print(long n);
extern void print(UInt16 n);
extern void print(UInt32 n);
extern void print(UInt64 n);

/* GDT.C */
extern void gdt_set_gate(int num, UInt32 base, UInt32 limit, UInt8 access, UInt8 gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(UInt8 num, UInt32 base, UInt16 sel, UInt8 flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();

/* KEYBOARD.C */
extern void keyboard_install();

/* KBDFN.C */
extern void toggle_caps();
extern void toggle_shift();
extern void toggle_ctrl();
extern void toggle_alt();
extern void s_putch(const char c);

#endif