#ifndef STRING_H 
#define STRING_H 
#define size_t unsigned int 
/* This file will contain the functions related to the manipulation of the strings in C. */ 
void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, char val, size_t count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
size_t strlen(const char *str);
#endif 