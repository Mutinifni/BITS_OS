#include "system.h"

struct idt_entry
{
    unsigned short base_lo;		// The lower 16 bits of the address to jump to when this interrupt fires.
    unsigned short sel; 		/* Our kernel segment goes here! */
    unsigned char always0;     	/* This will ALWAYS be set to 0! */
    unsigned char flags;       	
    unsigned short base_hi;		// The upper 16 bits of the address to jump to.
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;			// The address of the first element in our idt_entry_t array.
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load() __asm__ ("idt_load");

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}