#include "system.h"	 

char spkeys[10]={0};
/*
	0 - CAPS_LOCK
	1 - LEFT SHIFT_KEY
	2 - RIGHT SHIFT KEY
	3 - LEFT ALT KEY
	4 - RIGHT ALT KEY
	5 - LEFT CTRL KEY
	6 - RIGHT CTRL KEY
*/

int match(char*, int);
void toggle_caps()
{
	spkeys[0] = !spkeys[0];
}

void toggle_l_shift()
{
	spkeys[1] = !spkeys[1];
}

void toggle_l_ctrl()
{
	spkeys[5] = !spkeys[5];
}

void toggle_l_alt()
{
	spkeys[3] = !spkeys[3];
}

void toggle_r_shift()
{
	spkeys[2] = !spkeys[2];
}

void toggle_r_ctrl()
{
	spkeys[6] = !spkeys[6];
}

void toggle_r_alt()
{
	spkeys[4] = !spkeys[4];
}

void s_putch(char c)
{
	if ((spkeys[0] ^ (spkeys[1] || spkeys[2])) && c >= 'a' && c <='z')
	{
		c += 'A' - 'a';
	}
	else if (spkeys[1] || spkeys[2])
	{
		if(c >= 'a' && c <='z' && !spkeys[0])
		{
			c += 'A' - 'a';
		}

		switch(c)
		{
			case '1': c = '!'; break;
			case '2': c = '@'; break;
			case '3': c = '#'; break;
			case '4': c = '$'; break;
			case '5': c = '%'; break;
			case '6': c = '^'; break;
			case '7': c = '&'; break;
			case '8': c = '*'; break;
			case '9': c = '('; break;
			case '0': c = ')'; break;
			case '-': c = '_'; break;
			case '=': c = '+'; break;
			case '[': c = '{'; break;
			case ']': c = '}'; break;
			case '\\': c = '|'; break;
			case ';': c = ':'; break;
			case '\'': c = '"'; break;
			case ',': c = '<'; break;
			case '.': c = '>'; break;
			case '/': c = '?'; break;
			default: break;
		}
	}

	putch(c);

	return ;
}