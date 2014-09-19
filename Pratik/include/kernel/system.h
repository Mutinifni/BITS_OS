#ifndef SYSTEM_H 
/* This header file will describe the prototypes we will use in setting up the header file. */ 
#define SYSTEM_H 
#define uint32_t unsigned int 
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) ; 
// This will setup the descriptor in the gdt.
void gdt_install() 
// This will create the new gdt.  
#endif 