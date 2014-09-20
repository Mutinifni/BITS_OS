/* This file defines the screen related functions in the operating system. */ 

#include <system.h>
#include <scrn.h> 
#include <string.h> 
/* These define our textpointer, our background and foreground
*  colors (attributes), and x and y cursor coordinates */
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
/* Scrolls the screen */
void scroll(screen* ptr)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (ptr->attrib << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(ptr->csr_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = ptr->csr_y - 25 + 1;
        memcpy (ptr->textmemptr, ptr->textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (ptr->textmemptr + (25 - temp) * 80, blank, 80);
        ptr->csr_y = 25 - 1;
    }
}

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(screen* ptr)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = (ptr->csr_y) * 80 + (ptr->csr_x);

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* Clears the screen */
void cls(screen* ptr)
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (ptr->attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw ((ptr->textmemptr) + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    (ptr->csr_x) = 0;
    (ptr->csr_y) = 0;
    move_csr(ptr);
}

/* Puts a single character on the screen */
void putch(screen* ptr,  char c)
{
    unsigned short *where;
    unsigned att = (ptr->attrib) << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if((ptr->csr_x) != 0) (ptr->csr_x)--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        (ptr->csr_x) = ((ptr->csr_x) + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        (ptr->csr_x) = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        (ptr->csr_x) = 0;
        (ptr->csr_y)++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = ptr->textmemptr + ((ptr->csr_y) * 80 + (ptr->csr_x));
        *where = c | att;	/* Character AND attributes: color */
        (ptr->csr_x)++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if((ptr->csr_x) >= 80)
    {
        (ptr->csr_x) = 0;
        (ptr->csr_y)++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll(ptr);
    move_csr(ptr);
}

/* Uses the above routine to output a string... */
void puts(screen* ptr, const char *text)
{
    for (unsigned int i = 0; i < strlen(text); i++)
    {
        putch(ptr, text[i]);
    }
}

/* Sets the forecolor and backcolor that we will use */
void settextcolor(screen* ptr, unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    (ptr->attrib) = (backcolor << 4) | (forecolor & 0x0F) ;
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(screen* ptr)
{
    initialize_screen(ptr) ; 
    (ptr->textmemptr) = (unsigned short *)0xB8000;
    cls(ptr);
}
void initialize_screen(screen* ptr)
{
    // We will now initialize the screen here.
    ptr->attrib = 0x0F;
    ptr->csr_x = 0 ; 
    ptr->csr_y = 0  ; 
}
void print_text(screen* ptr, const char *text)
{
    size_t i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(ptr, text[i]);
    }
}

void print_int(screen* ptr, int n)
{
    if(n < 0)
    {
        putch(ptr, '-');
        n = -n;
    }
    if(n/10)
    {
        print_int(ptr, n/10);
    }
    putch(ptr, n%10 + '0');
}

void print_long_int(screen* ptr, long int n)
{
    if(n < 0)
    {
        putch(ptr, '-');
        n = -n;
    }
    if(n/10)
    {
        print_long_int(ptr, n/10);
    }
    putch(ptr, n%10 + '0');
}

void print_double(screen* ptr, double n)
{
    print_int(ptr, (int) n);
    n -= (int) n;
    putch(ptr,'.');
    n *= 1000000;
    print_int(ptr, (int) n);
}

void print_float(screen* ptr, float n)
{
    print_int(ptr, (int) n);
    n -= (int) n;
    putch(ptr,'.');
    n *= 1000000;
    print_int(ptr, (int) n);
}