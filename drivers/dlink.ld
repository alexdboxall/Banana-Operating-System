ENTRY(_start)
SECTIONS
{
        . = 256M;
        .text BLOCK(8) : ALIGN(8)
        {
                *(.text)
                *(.text.*)
                *(.rodata*)
        }
        .data BLOCK(8) : ALIGN(8)
        {
                *(.data)
        }
        .bss BLOCK(8) : ALIGN(8)
        {
                *(COMMON)
                *(.bss)
        }
        .eh_frame_hdr BLOCK(8) : ALIGN(8)
        {
                *(.eh_frame_hdr)
        }
        .gcc_except_table BLOCK(8) : ALIGN(8)
        {
                *(.eh_frame)
				*(.gcc_except_table)
        }
}
