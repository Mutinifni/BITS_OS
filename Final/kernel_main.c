// This file is the basic entry point for the kernel.  
// Compile with : - gcc -o kernel_main.o kernel_main.c -std=c99 -c -m32 
#define TRUE 1
#define FALSE 0 
//#include <stddef.h> will decide later that this is needed or not. 
#include <stdint.h>
#include <initialize.h> 
#include <system.h> 
#include <scrn.h>
#include <gdt.h> 
#define uint32_t unsigned int 

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif 
void kernel_main()
{
	gdt_install();
	int state = check_processor_state() ;
	screen sc  ; 
	init_video(&sc) ; 
	puts(&sc, "Hello world in new functions\n") ; 
	print_int(&sc, state) ; 
}