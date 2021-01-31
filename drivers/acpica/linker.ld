ENTRY(_start)
SECTIONS
{
	. = 0xC2484000;     
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{		
		*(.data)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{		
		*(.rodata*)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.bss)
	}
}

/* 
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
This is padding in case we need to expand the linker script within the executable
*/
