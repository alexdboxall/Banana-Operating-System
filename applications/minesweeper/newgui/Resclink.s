.section .rodata

#include misc. data into output
    .global _bna_misc
    .type   _bna_misc, @object
    .align  4
_bna_misc:
    .incbin "miscdata.txt"
_bna_misc_end:
    .global _bna_misc_size
    .type   _bna_misc_size, @object
    .align  4
_bna_misc_size:
    .int    _bna_misc_end - _bna_misc

#include 8x8 icon into output
    .global _bna_icon8x8
    .type   _bna_icon8x8, @object
    .align  4
_bna_icon8x8:
    .incbin "icon8x8.bmp"
_bna_icon8x8_end:
    .global _bna_icon8x8_size
    .type   _bna_icon8x8_size, @object
    .align  4
_bna_icon8x8_size:
    .int    _bna_icon8x8_end - _bna_icon8x8

#include 16x16 icon into output
    .global _bna_icon16x16
    .global _bna_icon16x16_size
    .type   _bna_icon16x16_size, @object
    .align  4
_bna_icon16x16:
    .incbin "icon16x16.bmp"
_bna_icon16x16_end:
    .global _bna_icon16x16_size
    .type   _bna_icon16x16_size, @object
    .align  4
_bna_icon16x16_size:
    .int    _bna_icon16x16_end - _bna_icon16x16


#include 64x64 icon into output
    .global _bna_icon64x64
    .type   _bna_icon64x64, @object
    .align  4
_bna_icon64x64:
    .incbin "icon64x64.bmp"
_bna_icon64x64_end:
    .global _bna_icon64x64_size
    .type   _bna_icon64x64_size, @object
    .align  4
_bna_icon64x64_size:
    .int    _bna_icon64x64_end - _bna_icon64x64
