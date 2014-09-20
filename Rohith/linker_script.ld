/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
OUTPUT_FORMAT("binary")
ENTRY(start)

phys = 0x00100000;

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
  .text phys : AT(phys) {
    code = .;
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }

  	/* Read-only data. */
  .data : AT(phys + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4096);
  }

	/* Read-write data (uninitialized) and stack */
  .bss : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4096);
  }
  end = .;
}