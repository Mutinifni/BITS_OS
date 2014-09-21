#include <system.h>

UInt8 spkeys[10]={0};
/*
	0 - CAPS_LOCK
	1 - SHIFT_KEY
	2 - CTRL KEY
	3 - ALT KEY
*/

void toggle_caps()
{
	spkeys[0] = !spkeys[0];
}

void toggle_shift()
{
	spkeys[1] = !spkeys[1];
}

void toggle_ctrl()
{
	spkeys[2] = !spkeys[2];
}

void toggle_alt()
{
	spkeys[3] = !spkeys[3];
}

void s_putch(char c)
{
	if (spkeys[0] && c >= 'a' && c <='z')
	{
		c += 'A' - 'a';
	}

	else if (spkeys[1])
	{
		if(c >= 'a' && c <='z')
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