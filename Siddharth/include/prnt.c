#include "system.h"

void print(const char *text)
{
    size_t i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

void print(int n)
{
	if(n<0)
	{
		putch('-');
		n = -n;
	}

	if(n == 0)
	{
		putch('0');
	}

	else
	{
		if(n > 10)
			print(n / 10);
		putch(n % 10 + '0');
	}
}

void print(double n)
{
	print((int) n);
	n -= (int) n;
	putch('.');
	n *= 1000000;
	print((int) n);
}