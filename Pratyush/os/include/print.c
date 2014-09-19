#include "system.h"

/* Takes an integer and prints it on the console. */
void print(int num)
{
    if(num < 0)
    {
        putch('-');
        num = -num;
    }
    if(num/10)
    {
        print(num/10);
    }
    putch(num%10 + '0');
}

/* Takes a long and prints it on the console. */
void print(long num)
{
    if(num < 0)
    {
        putch('-');
        num = -num;
    }
    if(num/10)
    {
        print(num/10);
    }
    putch(num%10 + '0');
}

/* Takes a float and prints it on the console. Prints 6 digits after decimal point.*/
void print(float num)
{
    int i = (int) num;
    print(i);
    putch('.');
    num -= i;
    num *= 1000000;
    print((int) num);
}

/* Takes a double and prints it on the console. Prints 6 digits after decimal point. */
void print(double num)
{
    int ipart = (int) num;
    print(ipart);
    putch('.');
    num -= ipart;
    for(int i = 0; i < 6; i++)
    {
        num *= 10;
        ipart = (int)num; 
        putch(ipart + '0');
        num -= ipart;
    }
}

/* Outputs the parameter string. */
void print(const char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}