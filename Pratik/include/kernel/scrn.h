#ifndef SCRN_H 
#define SCRN_H 
#include <stdint.h>
/* This is the header file in which we will we be writing the functions in the scrn.c object file. */ 
struct screen
{
    uint16_t* textmemptr ;
    int32_t attrib ; 
    int32_t csr_x ; 
    int32_t csr_y ; 
} ; 
typedef struct screen screen ; 
void print_int(screen*, int) ; 
void print_long_int(screen*, long int) ;
void print_double(screen*, double) ;
void print_float(screen*, float) ; 
void print_text(screen*, const char*) ; 
void initialize_screen(screen*) ; 
void scroll(screen*) ; 
void move_csr(screen*) ; 
void cls(screen*) ; 
void putch(screen*, char) ; 
void puts(screen*, const char*) ; 
void settextcolor(screen*, uint8_t, uint8_t) ; 
void init_video(screen*) ; 
#endif 

