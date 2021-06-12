ENTRY(start)
/*OUTPUT_FORMAT("binary")*/
OUTPUT_FORMAT("elf32-i386")
/*OUTPUT_ARCH(i386:x86-64)*/

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1M */
	. = 0xC0000000;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */

	.text BLOCK(1) : ALIGN(1)
	{
		*(.text)
		*(.gnu.linkonce.t*)
	}

	/* Read-only data. */
	.rodata BLOCK(1) : ALIGN(1)
	{
		start_ctors = .;
        *(SORT(.ctors*))  /* Note the "SORT" */
        end_ctors = .;

        start_dtors = .;
        *(SORT(.dtors*))
        end_dtors = .;

        *(.rodata*)
        *(.gnu.linkonce.r*)
	}

	/* Read-write data (initialized) */
	.data BLOCK(1) : ALIGN(1)
	{
		*(.data)
		*(.gnu.linkonce.d*)
	}
	
	.eh_frame BLOCK(1) : ALIGN(1)
	{
		*(.eh_frame)
	}
	
	.userkernel BLOCK(4096) : ALIGN(4096)
	{
		START_USER_KERNEL = .;
		*(.userkernel)
		END_USER_KERNEL = .;
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(1) : ALIGN(1)
	{
		sbss = .;
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
		*(.gnu.linkonce.b*)
		ebss = .;
	}
	
	
	/DISCARD/ :
    {
        *(.comment)
    }
	
	/* Try to include the BSS within the flat binary */
	. = . + SIZEOF(.bss);

	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}