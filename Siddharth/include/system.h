#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef unsigned int size_t;

/* MEMFN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* SCR.C */
extern void scroll(void);
extern void move_csr(void);
extern void cls();
extern void putch(const char c);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video(void);

/* PRNT.C */
extern void print(const char *text);
extern void print(int n);
extern void print(double n);

#endif