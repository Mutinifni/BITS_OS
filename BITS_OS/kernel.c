#include <processor.h>
#include <io.h>  
extern "C" void kernel_main()
{
  init_video() ; 
  putch('H') ; 
  for(;;)  ;
} 
