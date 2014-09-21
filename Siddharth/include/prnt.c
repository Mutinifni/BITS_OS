#include <system.h>

//For Printing a String
void print(const char *text)
{
    UInt32 i;

    for (i = 0; text[i] != '\0'; i++)
    {
        putch(text[i]);
    }
}

// For Printing an integer
void print(short n)
{
	if(n < 0)
	{
		putch('-');
		n = -n;
	}

	if(n > 10)
		print(n / 10);
	putch(n % 10 + '0');
}

void print(int n)
{
	if(n < 0)
	{
		putch('-');
		n = -n;
	}

	if(n > 10)
		print(n / 10);
	putch(n % 10 + '0');
}

void print(long n)
{
	if(n < 0)
	{
		putch('-');
		n = -n;
	}

	if(n > 10)
		print(n / 10);
	putch(n % 10 + '0');
}

void print(UInt16 n)
{
	if(n > 10)
		print(n / 10);
	putch(n % 10 + '0');
}

void print(UInt32 n)
{
	if(n > 10)
		print(n / 10);
	putch(n % 10 + '0');
}

// For Printing a decimal
void print(float n)
{
	print((int) n);
	n -= (int) n;
	
	putch('.');
	
	n *= 1000000;
	print((int) n);
}

void print(double n)
{
	print((int) n);
	n -= (int) n;
	
	putch('.');
	
	n *= 1000000;
	print((int) n);
}