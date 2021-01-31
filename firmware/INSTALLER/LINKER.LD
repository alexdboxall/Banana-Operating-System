/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)
OUTPUT_FORMAT("binary")

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 0x50000;
 
	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4) : ALIGN(4)
	{
		*(.text)
	}
 
	/* Read-only data. */
	.rodata BLOCK(4) : ALIGN(4)
	{
		*(.rodata)
	}
 
	/* Read-write data (initialized) */
	.data BLOCK(4) : ALIGN(4)
	{
		*(.data)
	}
 
	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4) : ALIGN(4)
	{
		*(COMMON)
		*(.bss)
	}
 
	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}