#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef int size_t;

struct Time
{ 
      unsigned char sec;
      unsigned char min;
      unsigned char hour;
      unsigned char day;
      unsigned char month;
      unsigned int year;
 };

/*This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};


// main functions
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

// scrn functions
extern void cls();
extern void putch(unsigned char c);
extern void print(const char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void arrow_keys(char dir);
extern void init_video();

// print functions
extern void print(int num);
extern void print(unsigned int num);
extern void print(long num);
extern void print(float num);	
extern void print(double num);
		
// gdt functions
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

// idt functions
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

// isrs functions
extern void isrs_install();

// irq functions
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

// timer functions
extern void timer_handler(struct regs *r);
extern void timer_wait(int ticks);
extern void timer_install();

// kb functions
extern void keyboard_handler(struct regs *r);
extern void keyboard_install();

// kbdfn functions
extern void toggle_caps();
extern void toggle_l_shift();
extern void toggle_l_ctrl();
extern void toggle_l_alt();
extern void toggle_r_shift();
extern void toggle_r_ctrl();
extern void toggle_r_alt();
extern void s_putch(char c);

// rtc functions
extern Time read_rtc();
extern void print_Time(Time t);

#endif