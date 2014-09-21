#include <exception.h> 
#include <interrupt.h>
#include <scrn.h>  
void dump_registers(struct regs* content)
{
	print_text(&sc,"eax : "); 
	print_int(&sc, content->eax) ; 
	print_text(&sc, ",ebx: ") ; 
	print_int(&sc, content->ebx) ; 
	print_text(&sc, "\nebp: ") ; 
	print_int(&sc, content->ebp) ; 
	print_text(&sc, "\n") ; 
}