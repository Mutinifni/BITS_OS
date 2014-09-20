#include <system.h>

struct idt_entry
{
    UInt16 base_lo;
    UInt16 sel;        /* Our kernel segment goes here! */
    UInt8 always0;     /* This will ALWAYS be set to 0! */
    UInt8 flags;       /* Set using the above table! */
    UInt16 base_hi;
} __attribute__((packed));

struct idt_ptr
{
    UInt16 limit;
    UInt32 base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load() __asm__ ("idt_load");

void idt_set_gate(UInt8 num, UInt32 base, UInt16 sel, UInt8 flags)
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
    idtp.base = (UInt32) &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}