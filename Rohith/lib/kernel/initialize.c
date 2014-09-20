#include <initialize.h> 
int check_processor_state()
{
	register int state __asm__("eax") ; // access the eax register. 
	return state ; 
}