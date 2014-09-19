#ifndef SYSTEM_H
#define SYSTEM_H
#define size_t unsigned int 

/* This defines what the stack looks like after an ISR was running */
/*struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};*/


void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, char val, size_t count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
size_t strlen(const char *str);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

		
#endif
