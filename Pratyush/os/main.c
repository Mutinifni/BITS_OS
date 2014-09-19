#include <system.h>

int main()
{
	gdt_install();
    init_video();
    double f = 2323.45;
    print(f);
    for (;;);
    return 0;
}