#include <processor.h> 
#include <stdint.h>
breg reg_val ;   
void get_breg(breg* ptr)
{
  reg_val.eax = ptr->eax ; 
  reg_val.ecx = ptr->ecx ; 
  reg_val.edx = ptr->edx ; 
  reg_val.ebx = ptr->ebx ; 
  reg_val.ebp = ptr->ebp ; 
  reg_val.esp = ptr->esp ; 
  reg_val.esi = ptr->esi ; 
  reg_val.edi = ptr->edi ;
}
  
