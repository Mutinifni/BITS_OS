#include <system.h>

UInt8 spkeys[10]={0};
/*
	0 - CAPS_LOCK
	1 - LEFT SHIFT KEY
	2 - RIGHT SHIFT KEY
	3 - LEFT CTRL KEY
	4 - RIGHT CTRL KEY
	5 - LEFT ALT KEY
	6 - RIGHT ALT KEY
*/

void toggle_caps()
{
	spkeys[0] = !spkeys[0];
}

void toggle_lshift()
{
	spkeys[1] = !spkeys[1];
}

void toggle_rshift()
{
	spkeys[2] = !spkeys[2];
}

void toggle_lctrl()
{
	spkeys[3] = !spkeys[3];
}

void toggle_rctrl()
{
	spkeys[4] = !spkeys[4];
}

void toggle_lalt()
{
	spkeys[5] = !spkeys[5];
}

void toggle_ralt()
{
	spkeys[6] = !spkeys[6];
}

void s_putch(char c)
{
	if ( spkeys[0]^(spkeys[1] || spkeys[2]) && c >= 'a' && c <='z')
	{
		c += 'A' - 'a';
	}

	else if (spkeys[1] || spkeys[2])
	{
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