#include "system.h"

extern int timer_ticks;

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,                  /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock 58*/
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    static unsigned char scancode = 0;
    static unsigned char flag = 0;  // Flag determines left or right in case of alt or ctrl key.

    if(scancode == 224)
    {
        flag = !flag;
    }

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);
    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
        switch(scancode & ~0x80)
        {
            case 29 :
                if(flag)
                    toggle_r_ctrl();
                else
                    toggle_l_ctrl();
                break;
            case 42 : 
                toggle_l_shift(); 
                break;
            case 54 : 
                toggle_r_shift(); 
                break;
            case 56 :
                if(flag)
                    toggle_l_alt();
                else
                    toggle_r_alt(); 
                break;
            default : 
                break;
        }

    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        switch(scancode)
        {
            case 29 :
                if(flag)
                    toggle_r_ctrl();
                else
                    toggle_l_ctrl();
                break;
            case 42 : 
                toggle_l_shift(); 
                break;
            case 54 : 
                toggle_r_shift(); 
                break;
            case 56 : 
                if(flag)
                    toggle_l_alt();
                else
                    toggle_r_alt(); 
                break;
            case 58 : 
                toggle_caps(); 
                break;
            case 72 : 
                arrow_keys('u'); 
                break;
            case 75 : 
                arrow_keys('l'); 
                break;
            case 77 : 
                arrow_keys('r'); 
                break;
            case 80 : 
                arrow_keys('d'); 
                break;
            default : 
                s_putch(kbdus[scancode]); 
                break;
        }
    }
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}