#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <stdint.h>  
/* This file will contain the parameters related to the processor.*/ 
/* These parameters will be set when the processor restarts. */ 
struct breg 
{
  int32_t eax ; 
  int32_t ecx ; 
  int32_t edx ; 
  int32_t ebx ; 
  int32_t ebp ; 
  int32_t esp ; 
  int32_t esi ; 
  int32_t edi ; 
} ; 
typedef struct breg breg ;
extern breg reg_val ; 
// always call this function before using the above variable.  
void get_breg(breg* ptr) ; 
#endif 
